export module disxx.disasm.Address;

export import std;

export namespace disxx::disasm
{
	enum class [[clang::type_visibility("default")]] Address : std::uint64_t {};

	[[nodiscard]] constexpr inline std::uint64_t integer(Address addr) noexcept
	{ return static_cast<std::uint64_t>(addr); }

	Address operator++(Address &, int) noexcept;
} /* disxx::disasm */

export template <> struct std::formatter<disxx::disasm::Address> : public std::formatter<std::string>
{
  public:
	auto format(const disxx::disasm::Address &addr, std::format_context &ctx) const
	{
		return std::format_to
		(
			ctx.out(),
			"{:#016x}",
			integer(addr)
		);
	}
};
