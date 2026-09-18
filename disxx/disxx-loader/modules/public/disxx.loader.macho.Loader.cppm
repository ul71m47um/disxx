module;

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

export module disxx.loader.macho.Loader;

export import disxx.loader.executable.ExecutableFile;
export import disxx.loader.utility.BinaryInfo;
import disxx.utility.file.MappedFile;

export import std;

export namespace disxx::loader::macho
{
	class __attribute__((visibility("default"))) [[nodiscard]] Loader
	{
	  private:
		disxx::utility::file::MappedFile m_Mapper{};
		mach_header_64 *m_pHeader{};
		std::uint64_t m_Offset{};

	  public:
		explicit Loader(void) noexcept;
		
		Loader(const Loader &) noexcept;
		Loader &operator=(const Loader &) noexcept;

		Loader(Loader &&) noexcept;
		Loader &operator=(Loader &&) noexcept;

		~Loader(void) noexcept;
		
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
		LoadFile(const std::filesystem::path &) noexcept;
		
		std::expected
		<
			disxx::loader::executable::ExecutableFile,
			std::variant
			<
				std::out_of_range,
				std::range_error
			>
		>
		LoadData(void) const noexcept;
		
		std::expected
		<
			disxx::loader::utility::BinaryInfo,
			std::variant
			<
				std::out_of_range,
				std::range_error
			>
		>
		LoadMetadata(void) const noexcept;
		
		std::optional<std::uint64_t> LoadImageBase(void) const noexcept;

		std::string_view GetFileType(void) const noexcept;
	};
} /* disxx::loader::macho */
