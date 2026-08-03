module;

#include <disconf.hpp>

export module disxx.disasm.Bytes;

export import std;

export namespace disxx::disasm
{
	enum class [[clang::type_visibility("default")]] Bytes : std::uint32_t {}; 

	[[nodiscard]] constexpr inline std::uint32_t integer(Bytes word) noexcept
	{ return static_cast<std::uint32_t>(word); }
} /* disxx::disasm */

export template <> struct std::formatter<disxx::disasm::Bytes> : public std::formatter<std::string>
{
  public:
	auto format(const disxx::disasm::Bytes &addr, std::format_context &ctx) const
	{
		return std::format_to
		(
			ctx.out(),
			"{:#08x}",
			integer(addr)
		);
	}
};
