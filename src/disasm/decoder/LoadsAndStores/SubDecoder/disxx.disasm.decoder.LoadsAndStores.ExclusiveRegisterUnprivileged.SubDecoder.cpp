module;

#include <utility>
#include <cstdint>
#include <memory>
#include <vector>
#include <array>

module disxx.disasm.decoder.LoadsAndStores.ExclusiveRegisterUnprivileged.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::ExclusiveRegisterUnprivileged
{
	SubDecoder::SubDecoder(void) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{}
	{}

	SubDecoder::SubDecoder(std::uint32_t insn, std::uint64_t addr) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{insn, addr}
	{}

	SubDecoder::SubDecoder(const SubDecoder &other) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{other}
	{}

	SubDecoder &SubDecoder::operator=(const SubDecoder &other) noexcept
	{
		if (this != &other)
			[[maybe_unused]] const auto &_{disxx::disasm::decoder::abstract::SubDecoder::operator=(other)};
		return *this;
	}

	SubDecoder::SubDecoder(SubDecoder &&other) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{std::move(other)}
	{}

	SubDecoder &SubDecoder::operator=(SubDecoder &&other) noexcept
	{
		[[maybe_unused]] const auto &_{disxx::disasm::decoder::abstract::SubDecoder::operator=(std::move(other))};
		return *this;
	}

	std::unique_ptr<disxx::disasm::decoder::abstract::SubDecoder> SubDecoder::Clone(void) const noexcept
	{ return std::make_unique<std::decay_t<decltype(*this)>>(*this); }

	DisassemblyResult SubDecoder::Decode(void) const noexcept
	{
        // +----+-------+-+-+--+--+---+--+--+
        // |size|0010000|L|0|Rs|o0|Rt2|Rn|Rt|
        // +----+-------+-+-+--+--+---+--+--+
    
        unsigned short int size, L, Rs, o0, Rn, Rt;
        size = bits::extract<unsigned short int, std::uint32_t, 30, 31>(this->m_Insn);
        L = bits::extract<unsigned short int, std::uint32_t, 22, 22>(this->m_Insn);
        Rs = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        o0 = bits::extract<unsigned short int, std::uint32_t, 15, 15>(this->m_Insn);
        //Rt2 = bits::extract<unsigned short int, std::uint32_t, 10, 14>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);
        
        static constexpr std::array<InstructionIdentifier, 12> insnTable = {
            InstructionIdentifier::ID_STXRB, InstructionIdentifier::ID_STLXRB,
            InstructionIdentifier::ID_LDXRB, InstructionIdentifier::ID_LDAXRB,
            InstructionIdentifier::ID_STXRH, InstructionIdentifier::ID_STLXRH,
            InstructionIdentifier::ID_LDXRH, InstructionIdentifier::ID_LDAXRH,
            InstructionIdentifier::ID_STXR, InstructionIdentifier::ID_STLXR,
            InstructionIdentifier::ID_LDXR, InstructionIdentifier::ID_LDAXR
        };

        const auto insn
        {
            [size, L, o0] -> InstructionIdentifier
            {
                const unsigned short int encoding = (L << 1) | o0;
                if (size == 0b00)
                    return insnTable[encoding];
                else if (size == 0b01)
                    return insnTable[encoding + 4];
                return insnTable[encoding + 8];
            }()
        };

        if (L == 0b0)
		{
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_W,
					Rs
				)
			);
        }
		this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				size == 0b11
					? disxx::disasm::operand::Register::Type::TYPE_X
					: disxx::disasm::operand::Register::Type::TYPE_W,
				Rt
			)
		);
		this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
			(
				disxx::disasm::operand::Register
				{
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rn,
					true
				}
			)
		);

        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::LoadsAndStores::ExclusiveRegisterUnprivileged */
