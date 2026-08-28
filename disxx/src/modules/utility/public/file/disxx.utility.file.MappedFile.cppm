module;

#include "mapped.h"

export module disxx.utility.file.MappedFile;

export import std;

export namespace disxx::utility::file
{
	class __attribute__((visibility("default"))) [[nodiscard]] MappedFile final : private mapped_t
	{
	  private:
		std::filesystem::path m_Path{};

  	  private:
		std::expected
		<
			std::monostate,
			std::variant
			<
				std::out_of_range,
				std::range_error
			>
		>
		ValidateRange(std::uint64_t, std::size_t) const noexcept;

  	  public:
		explicit MappedFile(void) noexcept;
		explicit MappedFile(const std::filesystem::path &) noexcept;

		MappedFile(const MappedFile &) noexcept;
		MappedFile &operator=(const MappedFile &) noexcept;

		MappedFile(MappedFile &&) noexcept;
		MappedFile &operator=(MappedFile &&) noexcept;

		~MappedFile(void) noexcept;
		
		std::expected
		<
			std::monostate,
			std::variant
			<
				std::filesystem::filesystem_error,
				std::bad_alloc
			>
		>
		Open(const std::filesystem::path &) noexcept;
		std::expected
		<
			std::monostate,
			std::variant
			<
				std::filesystem::filesystem_error,
				std::bad_alloc
			>
		>
		Open(void) noexcept;

		template <typename T>
		std::expected
		<
			std::reference_wrapper<const T>,
			std::variant
			<
				std::out_of_range,
				std::range_error
			>
		>	
		Read(std::uint64_t offset) const noexcept;
	};

	template <typename T>
	std::expected
	<
		std::reference_wrapper<const T>,
		std::variant
		<
			std::out_of_range,
			std::range_error
		>
	>
	MappedFile::Read(std::uint64_t offset) const noexcept
	{
	    if (const auto result{this->ValidateRange(offset, sizeof(T))}; !result) [[unlikely]]
			return std::unexpected{result.error()};
		return std::cref
		(
			*std::bit_cast<const T *>
			(
				std::add_sat
				(
					std::bit_cast<std::uint64_t>(this->mptr),
					offset
				)
			)
		);
	}
} /* disxx::utility::file */
