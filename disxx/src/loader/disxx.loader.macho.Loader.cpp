module;

#if !__has_include(<mach/machine.h>)
#	define CPU_TYPE_ARM64 0x0000000100000c
#endif

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>

#include <arpa/inet.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpedantic"
#define MKARGS(...) this, __VA_ARGS__
#pragma clang diagnostic pop

module disxx.loader.macho.Loader;

import disxx.loader.executable.ExecutableFile;

import std;

namespace
{
	template <auto F, typename T, typename ...Args>
	inline auto mkerr(T &&var, Args &&..._) noexcept
	{
		if constexpr (std::is_base_of<std::exception, T>::value)
			return std::unexpected{var};
		else
		{
			return std::unexpected
			{
				std::visit
				(
					[](auto &&err) -> std::invoke_result<decltype(F), Args...>::type::error_type
					{ return err; },
					var
				)
			};
		}
	}
} /* */

namespace disxx::loader::macho
{
	Loader::Loader(void) noexcept
		: m_Mapper{}
		, m_pHeader{new mach_header_64{}}
		, m_Offset{0ull}
	{}

	Loader::Loader(const Loader &other) noexcept
		: m_Mapper{other.m_Mapper}
		, m_pHeader{new mach_header_64{*other.m_pHeader}}
		, m_Offset{other.m_Offset}
	{}

	Loader &Loader::operator=(const Loader &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			this->m_Mapper = other.m_Mapper;
			*this->m_pHeader = *other.m_pHeader;
			this->m_Offset = other.m_Offset;
		}

		return *this;
	}

	Loader::Loader(Loader &&other) noexcept
		: m_Mapper{std::move(other.m_Mapper)}
		, m_pHeader{std::move(other.m_pHeader)}
		, m_Offset{std::move(other.m_Offset)}
	{}

	Loader &Loader::operator=(Loader &&other) noexcept
	{
		this->m_Mapper = std::move(other.m_Mapper);
		this->m_pHeader = std::move(other.m_pHeader);
		this->m_Offset = std::move(other.m_Offset);

		return *this;
	}

	Loader::~Loader(void) noexcept
	{
		if (this->m_pHeader) [[likely]]
			delete this->m_pHeader;
	}

	std::expected
	<
		std::monostate,
		std::variant
		<
			std::filesystem::filesystem_error,
			std::invalid_argument,
			std::out_of_range,
			std::range_error,
			std::bad_alloc
		>
	>
	Loader::LoadFile(const std::filesystem::path &path) noexcept
	{
		this->m_Mapper.Open(path);
		// I really like that 0xCAFEBABE magic number :D
		if (const auto magicResult{this->m_Mapper.Read<std::uint32_t>(0)})
		{
			if (magicResult->get() == FAT_CIGAM)
			{
				const auto hdrResult{this->m_Mapper.Read<fat_header>(0)};
				if (!hdrResult) [[unlikely]]
					return mkerr<&Loader::LoadFile>(hdrResult.error(), MKARGS(path));

				std::vector<fat_arch> vec{ntohl(hdrResult->get().nfat_arch)};
				for (auto i{sizeof(fat_header)}; i < ntohl(hdrResult->get().nfat_arch) * sizeof(fat_arch) + sizeof(fat_header); i += sizeof(fat_arch))
				{
					const auto archResult{this->m_Mapper.Read<fat_arch>(i)};
					if (!archResult) [[unlikely]]
						return mkerr<&Loader::LoadFile>(archResult.error(), MKARGS(path));

					vec.emplace_back
					(
						[](const auto &arch) -> fat_arch
						{
							// Translating integers to little endian byte order
							return fat_arch
							{
								static_cast<std::int32_t>(ntohl(arch.cputype)),
								static_cast<std::int32_t>(ntohl(arch.cpusubtype)),
								ntohl(arch.offset),
								ntohl(arch.size),
								ntohl(arch.align)
							};
						}(archResult->get())
					);
				}
	
				const auto it 
				{
					std::ranges::find_if
					(
						vec,
						[](const auto &arch) -> bool
						{ return arch.cputype == CPU_TYPE_ARM64; }
					)
				};
			
				if (it == vec.end()) [[unlikely]]
					return mkerr<&Loader::LoadFile>(std::invalid_argument{"ProcessorArchitecureError"}, MKARGS(path));
				this->m_Offset = it->offset;
			}
		}
		else
			return mkerr<&Loader::LoadFile>(magicResult.error(), MKARGS(path));
	
		const auto headerResult{this->m_Mapper.Read<mach_header_64>(this->m_Offset)};
		if (!headerResult) [[unlikely]]	
			return mkerr<&Loader::LoadFile>(headerResult.error(), MKARGS(path));

		*(this->m_pHeader) = headerResult->get();
		if (this->m_pHeader->magic != MH_MAGIC_64) [[unlikely]]
			return mkerr<&Loader::LoadFile>(std::invalid_argument{"FileFormatError"}, MKARGS(path)); // 64-bit mach objects only!
		else if (this->m_pHeader->cputype != CPU_TYPE_ARM64) [[unlikely]]
			return mkerr<&Loader::LoadFile>(std::invalid_argument{"ProcessorArchitecureError"}, MKARGS(path)); // Can dissasemble only aarch64 instructions!
		return std::monostate{};
	}

	std::expected
	<
		disxx::loader::executable::ExecutableFile,
		std::variant
		<
			std::out_of_range,
			std::range_error
		>
	>
	Loader::LoadData(void) const noexcept
	{
		disxx::loader::executable::ExecutableFile exec{};
		exec.SetMagic(this->m_pHeader->magic);

		unsigned short int sectionIndex{1};

		std::expected
		<
			std::reference_wrapper<const load_command>,
			std::variant
			<
				std::out_of_range,
				std::range_error
			>
		> loadCommandResult{std::cref(*std::make_unique<load_command>())};
		auto offset{this->m_Offset + sizeof(mach_header_64)};
		for (const auto _ : std::views::iota(0u, this->m_pHeader->ncmds))
		{
			loadCommandResult = this->m_Mapper.Read<load_command>(offset);
			if (!loadCommandResult) [[unlikely]]
				return mkerr<&Loader::LoadData>(loadCommandResult.error(), this);

			if (loadCommandResult->get().cmd == LC_SEGMENT_64)
			{
				const auto segmentCommandResult{this->m_Mapper.Read<segment_command_64>(offset)};
				if (!segmentCommandResult) [[unlikely]]
					return mkerr<&Loader::LoadData>(segmentCommandResult.error(), this);

				auto pSects{std::make_unique<section_64[]>(segmentCommandResult->get().nsects)};
				for (const auto j : std::views::iota(0u, segmentCommandResult->get().nsects))
				{
					auto nSectionResult{this->m_Mapper.Read<section_64>((offset + sizeof(segmentCommandResult->get())) + (j * sizeof(section_64)))};
					if (!nSectionResult) [[unlikely]]
						return mkerr<&Loader::LoadData>(nSectionResult.error(), this);

					if (!nSectionResult->get().offset) [[unlikely]]
					{
						sectionIndex++;
						continue;
					}

					disxx::loader::executable::Section section{};
					section.SetName
					(
						std::format
						(
							"{},{}",
							// Cut null-terminators by wrapping ptr into str
							std::string{nSectionResult->get().segname},
							// The same thing here
							std::string{nSectionResult->get().sectname}
						)
					);
					section.SetAddress(nSectionResult->get().addr);
					section.SetOffset(this->m_Offset + nSectionResult->get().offset);
					section.SetSize(nSectionResult->get().size);
					section.SetIndex(sectionIndex++);
				
					exec.AddSection(std::move(section));
				}
			}
			else if (loadCommandResult->get().cmd == LC_SYMTAB)
			{
				const auto symtabCommandResult{this->m_Mapper.Read<symtab_command>(offset)};
				if (!symtabCommandResult) [[unlikely]]
					return mkerr<&Loader::LoadData>(symtabCommandResult.error(), this);

				std::vector<nlist_64> symbols{};
				symbols.reserve(symtabCommandResult->get().nsyms);
				for (const auto j : std::views::iota(0u, symtabCommandResult->get().nsyms))
				{
					const auto nlistResult{this->m_Mapper.Read<nlist_64>(symtabCommandResult->get().symoff + j * sizeof(nlist_64) + this->m_Offset)};
					if (!nlistResult) [[unlikely]]
						return mkerr<&Loader::LoadData>(nlistResult.error(), this);
					
					symbols.push_back(nlistResult->get());
				}

				std::vector<char> strtab{};
				strtab.reserve(symtabCommandResult->get().strsize);
				for (const auto j : std::views::iota(0u, symtabCommandResult->get().strsize))
				{
					const auto byteResult{this->m_Mapper.Read<char>(symtabCommandResult->get().stroff + j + this->m_Offset)};
					if (!byteResult) [[unlikely]]
						return mkerr<&Loader::LoadData>(byteResult.error(), this);

					strtab.push_back(*byteResult);
				}

				for (const auto j : std::views::iota(0u, symtabCommandResult->get().nsyms))
				{
					if (!symbols[j].n_un.n_strx)
						continue;
					else if ((symbols[j].n_type & N_TYPE) != N_SECT || (symbols[j].n_type & N_STAB))
						continue;
					
					const auto it
					{
						// Find the section with the same number as an argument
						std::ranges::find_if
						(
							exec.GetSections(),
							[&symbols, j](const auto &section) -> bool
							{ return section.GetIndex() == symbols[j].n_sect; }
						)
					};
				
					// If not found, just pass it
					if (it == exec.GetSections().end()) [[unlikely]]
						continue;
	
					auto start{0ull};
					if (const auto addr{it->GetAddress()}; symbols[j].n_value >= addr && symbols[j].n_value < addr + it->GetSize())
						start = it->GetOffset() + (symbols[j].n_value - addr);
				
					disxx::loader::executable::Label label{};
					label.SetName(&strtab.at(symbols[j].n_un.n_strx));
					label.SetAddress(symbols.at(j).n_value);
					label.SetOffset(start);
					it->AddLabel(std::move(label));
				}

				break;
			}
			
			offset += loadCommandResult->get().cmdsize;
		}

		for (auto &sect : exec.GetSections())
		{
			for (auto it{sect.GetLabels().begin()}; it != sect.GetLabels().end(); ++it)
			{
				std::vector<uint8_t> data{};
				for (const auto i : std::views::iota(it->GetOffset(), std::next(it) != sect.GetLabels().end() ? std::next(it)->GetOffset() : sect.GetSize() + sect.GetOffset()))
				{
					const auto byteResult{this->m_Mapper.Read<std::uint8_t>(i)};
					if (!byteResult) [[unlikely]]
						return mkerr<&Loader::LoadData>(byteResult.error(), this);

					data.push_back(*byteResult);
				}

				it->SetData(std::move(data));
			}
		}

		return std::move(exec);
	}

	std::expected
	<
		disxx::loader::utility::BinaryInfo,
		std::variant
		<
			std::out_of_range,
			std::range_error
		>
	>
	Loader::LoadMetadata(void) const noexcept
	{
		disxx::loader::utility::BinaryInfo metadata{};

		std::expected
		<
			std::reference_wrapper<const load_command>,
			std::variant
			<
				std::out_of_range,
				std::range_error
			>
		> loadCommandResult{std::cref(*std::make_unique<load_command>())};
		std::uint64_t offset{this->m_Offset + sizeof(mach_header_64)};
		for (const auto _ : std::views::iota(0u, this->m_pHeader->ncmds))
		{
			if (loadCommandResult = this->m_Mapper.Read<load_command>(offset); !loadCommandResult) [[unlikely]]
				return mkerr<&Loader::LoadMetadata>(loadCommandResult.error(), this);

			if (loadCommandResult->get().cmd == LC_BUILD_VERSION)
			{
				const auto buildVersionCommandResult{this->m_Mapper.Read<build_version_command>(offset)};
				if (!buildVersionCommandResult) [[unlikely]]
					mkerr<&Loader::LoadMetadata>(buildVersionCommandResult.error(), this);
				metadata.SetBuildVersion(buildVersionCommandResult->get());
				
				for (auto index{offset + sizeof(build_version_command)}; index < offset + buildVersionCommandResult->get().cmdsize; index += sizeof(build_tool_version))
				{
					const auto buildToolVersionResult{this->m_Mapper.Read<build_tool_version>(index)};
					if (!buildToolVersionResult) [[unlikely]]
						mkerr<&Loader::LoadMetadata>(buildToolVersionResult.error(), this);
					metadata.SetBuildTool(*buildToolVersionResult);
				}

				return metadata;
			}

			offset += loadCommandResult->get().cmdsize;
		}

		return metadata;
	}

	std::optional<std::uint64_t> Loader::LoadImageBase(void) const noexcept
	{
		std::expected
		<
			std::reference_wrapper<const load_command>,
			std::variant
			<
				std::out_of_range,
				std::range_error
			>
		> loadCommandResult{std::cref(*std::make_unique<load_command>())};
		std::uint64_t offset{this->m_Offset + sizeof(mach_header_64)};
		for (const auto _ : std::views::iota(0u, this->m_pHeader->ncmds))
		{
			if (loadCommandResult = this->m_Mapper.Read<load_command>(offset); !loadCommandResult) [[unlikely]]
				return std::nullopt;
			if (loadCommandResult->get().cmd == LC_SEGMENT_64)
				if (const auto segmentCommandResult{this->m_Mapper.Read<segment_command_64>(offset)}; segmentCommandResult && std::string{segmentCommandResult->get().segname} == "__TEXT")
					return segmentCommandResult->get().vmaddr - segmentCommandResult->get().fileoff;
			offset += loadCommandResult->get().cmdsize;
		}

		return std::nullopt;
	}

	std::string_view Loader::GetFileType(void) const noexcept
	{
		const static std::unordered_map<std::uint32_t, std::string_view> fileTypeTable
		{
			{MH_OBJECT,		"relocatable object file"},
			{MH_EXECUTE,	"demand paged executable file"},
			{MH_CORE,		"core file"},
			{MH_DYLIB,		"dynamically bound shared library"}
		};

		if (!this->m_pHeader) [[unlikely]]
			return "unknown";
		else if (!fileTypeTable.contains(this->m_pHeader->filetype)) [[unlikely]]
			return "unknown";
		else [[likely]]
			return fileTypeTable.at(this->m_pHeader->filetype);
	}
} /* disxx::loader::macho */
