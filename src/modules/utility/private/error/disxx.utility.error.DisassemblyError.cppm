module;

#include <disconf.hpp>

export module disxx.utility.error.DisassemblyError;

export import std;

export namespace disxx::utility::error
{
	class [[clang::type_visibility("default")]] [[nodiscard]] DisassemblyError : public std::exception
	{
	  private:
		std::string m_Error{};

	  public:
		explicit DisassemblyError(void) noexcept;
		// TODO: use disxx::disasm::Bytes instead
		explicit DisassemblyError(std::uint32_t) noexcept;

		bool operator==(const DisassemblyError &) noexcept;
		bool operator!=(const DisassemblyError &) noexcept;

		//virtual ~DisassemblyError(void) noexcept override = default;
		virtual const char *what(void) const noexcept override;
	};
} /* disxx::util::error */
