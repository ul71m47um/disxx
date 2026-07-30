module;

#include <algorithm>
#include <optional>
#include <charconv>
#include <utility>
#include <ranges>
#include <string>
#include <regex>

module disxx.disasm.Disassembler;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.decoder.DecoderFactory;
import disxx.disasm.operand.Immediate;
import disxx.disasm.Address;

namespace disxx::disasm
{
	Disassembler::Result Disassembler::Disassemble(Bytes word, Address addr) const noexcept
	{
		const auto &obj
		{
			decoder::DecoderFactory::GetDecoder
			(
				 integer(word),
                 integer(addr)
			)
		};

		auto &&result{obj->Decode()};
		if (!result) [[unlikely]]
			return std::unexpected{result.error()};
		auto &[id, oprs]{result.value()};

		auto programCounterRelevantAddress
		{
			[&obj, &oprs](void) -> std::optional<signed long long int>
			{
				if (!obj->HasProgramCounterRelevantAddress())
					return std::nullopt;

				const auto &it
            	{
					std::ranges::find_if
                	(
                	    oprs,
                	    [](const auto &ptr) -> bool
                	    { return dynamic_cast<operand::Immediate<signed long long int, 64> *>(ptr.get()) != nullptr; }
                	)
            	};

            	if (it == oprs.end()) [[unlikely]]
            		return std::nullopt;
				return static_cast<operand::Immediate<signed long long int, 64> *>(it->get())->GetValue();
			}()
		};

		Instruction insn{};
		insn.SetBytes(std::move(word));
		insn.SetAddress(std::move(addr));
		insn.SetInstructionIdentifier(std::move(id));
		insn.SetOperands(std::move(oprs));
		insn.SetProgramCounterRelevantAddress(std::move(programCounterRelevantAddress));
	
		return insn;
	}
} /* disxx::disasm */
