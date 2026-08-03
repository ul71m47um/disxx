module;

#include <disconf.hpp>

export module disxx.disasm.Disassembler;

export import disxx.utility.error.DisassemblyError;
export import disxx.disasm.Instruction;
export import disxx.disasm.Address;
export import disxx.disasm.Bytes;

export import std;

export namespace disxx::disasm
{
	class [[nodiscard]] [[clang::type_visibility("default")]] Disassembler
	{
	  public:
		using Result = std::expected
		<
			Instruction,
			disxx::utility::error::DisassemblyError
		>;

	  public:
		explicit Disassembler(void) noexcept = default;

		explicit Disassembler(const Disassembler &) noexcept = default;
		Disassembler &operator=(const Disassembler &) noexcept = default;

		~Disassembler(void) noexcept = default;

		Result Disassemble(const Bytes, const Address) const noexcept;
	};
} /* disxx::disasm */
