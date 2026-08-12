export module disxx.disasm.Address;

export import std;

export namespace disxx::disasm
{
	enum class __attribute__((visibility("default"))) Address : std::uint64_t {};

	[[nodiscard]] constexpr inline std::uint64_t integer(Address addr) noexcept
	{ return static_cast<std::uint64_t>(addr); }

	__attribute__((visibility("default"))) Address operator++(Address &, int) noexcept;
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
