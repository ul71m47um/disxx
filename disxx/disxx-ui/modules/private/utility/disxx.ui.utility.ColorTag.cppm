export module disxx.ui.utility.ColorTag;

export import std;

export namespace disxx::ui::utility
{
	class __attribute__((visibility("default"))) [[nodiscard]] ColorTag
	{
	  public:
		using Result = std::expected
		<
			std::vector
			<
				std::pair
				<
					std::string,
					std::array
					<
						float,
						4
					>
				>
			>,
			std::runtime_error
		>;

	  public:
		explicit ColorTag(void) noexcept;

		explicit ColorTag(const ColorTag &) noexcept;
		ColorTag &operator=(const ColorTag &) noexcept;

		~ColorTag(void) noexcept;

		std::string RemoveTags(const std::string &) const noexcept;
		Result Parse(const std::string &) const noexcept;
	};
} /* disxx::ui::utility */
