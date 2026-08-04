export module disxx.utility.error.ParserError;

export import std;

export namespace disxx::utility::error
{
	class [[clang::type_visibility("default")]] [[nodiscard]] ParserError final : public std::exception
	{
	  private:
		std::string m_Error{};

	  public:
		explicit ParserError(void) noexcept;
		explicit ParserError(std::string) noexcept;

		ParserError(const ParserError &) noexcept = default;
		ParserError &operator=(const ParserError &) noexcept = default;

		virtual ~ParserError(void) noexcept override = default;

		virtual const char *what(void) const noexcept override;
	};
} /* disxx::utility::error */
