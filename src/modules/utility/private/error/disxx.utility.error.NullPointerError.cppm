module;

#include <disconf.hpp>

export module disxx.utility.error.NullPointerError;

export import std;

export namespace disxx::utility::error
{
	class [[clang::type_visibility("default")]] [[nodiscard]] NullPointerError : public std::runtime_error
	{
	  public:
		explicit NullPointerError(const char *) noexcept;
		explicit NullPointerError(const std::string &) noexcept;

		virtual ~NullPointerError(void) noexcept override = default;
	};
} /* disxx::disasm::util */
