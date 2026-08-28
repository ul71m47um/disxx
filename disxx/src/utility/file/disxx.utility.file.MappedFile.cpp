module;

#include "../../modules/utility/public/file/mapped.h"

module disxx.utility.file.MappedFile;

namespace disxx::utility::file
{
	MappedFile::MappedFile(void) noexcept
		: mapped_t{nullptr, 0ull}
		, m_Path{}
	{}

	MappedFile::MappedFile(const std::filesystem::path &path) noexcept
		: mapped_t{nullptr, 0ull}
		, m_Path{path}
	{ this->Open(); }

	MappedFile::MappedFile(const MappedFile &other) noexcept
		: mapped_t{nullptr, 0ull}
		, m_Path{other.m_Path}
	{ this->Open(); }

	MappedFile &MappedFile::operator=(const MappedFile &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			this->m_Path = other.m_Path;
			this->Open();
		}
	
		return *this;
	}

	MappedFile::MappedFile(MappedFile &&other) noexcept
		: mapped_t{std::forward<MappedFile &&>(other)}
		, m_Path{std::move(other.m_Path)}
	{}

	MappedFile &MappedFile::operator=(MappedFile &&other) noexcept
	{
		mapped_t::operator=(std::forward<MappedFile &&>(other));
		this->m_Path = std::move(other.m_Path);

		return *this;
	}

	MappedFile::~MappedFile(void) noexcept
	{
		if (this->mptr)
			mclose(static_cast<mapped_t>(*this));
	}

	std::expected
	<
		std::monostate,
		std::variant
		<
			std::out_of_range,
			std::range_error
		>
	>	
	MappedFile::ValidateRange(std::uint64_t offset, std::size_t size) const noexcept
	{
		if (!size) [[unlikely]]
			return std::unexpected{std::range_error{"ZeroSizeError"}};
		else if (offset > this->msize || this->msize - offset < size) [[unlikely]]
			return std::unexpected{std::out_of_range{"OutOfBoundsError"}};
		return std::monostate{};
	}
	
	std::expected
	<
		std::monostate,
		std::variant
		<
			std::filesystem::filesystem_error,
			std::bad_alloc
		>
	>
	MappedFile::Open(const std::filesystem::path &path) noexcept
	{
		// Validating file path
		if (std::error_code errc{}; !std::filesystem::exists(path, errc)) [[unlikely]]
			return std::unexpected{std::filesystem::filesystem_error{"FileNotFoundError", errc}};
		else if (std::filesystem::is_directory(path, errc)) [[unlikely]]
			return std::unexpected{std::filesystem::filesystem_error{"DirectoryError", errc}};
	
		auto pMapped{mopen(path.c_str())};
		if (!pMapped.mptr) [[unlikely]]
			return std::unexpected{std::bad_alloc{}};
		this->mptr = pMapped.mptr;
		this->msize = pMapped.msize;

		return std::monostate{};
	}

	std::expected
	<
		std::monostate,
		std::variant
		<
			std::filesystem::filesystem_error,
			std::bad_alloc
		>
	>
	MappedFile::Open(void) noexcept
	{
		// Validating file path
		if (std::error_code errc{}; !std::filesystem::exists(this->m_Path, errc)) [[unlikely]]
			return std::unexpected{std::filesystem::filesystem_error{"FileNotFoundError", errc}};
		else if (std::filesystem::is_directory(this->m_Path, errc)) [[unlikely]]
			return std::unexpected{std::filesystem::filesystem_error{"DirectoryError", errc}};
	
		auto pMapped{mopen(this->m_Path.c_str())};
		if (!pMapped.mptr) [[unlikely]]
			return std::unexpected{std::bad_alloc{}};
		this->mptr = pMapped.mptr;
		this->msize = pMapped.msize;

		return std::monostate{};
	}
} /* disxx::utility::file */
