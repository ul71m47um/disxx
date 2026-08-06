module disxx.disasm.decoder.LoadsAndStores.Ordered.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::Ordered
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
        // |size|0010001|L|0|Rs|o0|Rt2|Rn|Rt|
        // +----+-------+-+-+--+--+---+--+--+

        unsigned short int size, L, o0, Rn, Rt;
        size = utility::bits::extract<unsigned short int, std::uint32_t, 30, 31>(this->m_Insn);
        L = utility::bits::extract<unsigned short int, std::uint32_t, 22, 22>(this->m_Insn);
        // Rs = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        o0 = utility::bits::extract<unsigned short int, std::uint32_t, 15, 15>(this->m_Insn);
        // Rt2 = utility::bits::extract<unsigned short int, std::uint32_t, 10, 14>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);
 
        static constexpr std::array<InstructionIdentifier, 12> insnTable
		{
            InstructionIdentifier::ID_STLLRB, InstructionIdentifier::ID_STLRB,
            InstructionIdentifier::ID_LDLARB, InstructionIdentifier::ID_LDARB,
            InstructionIdentifier::ID_STLLRH, InstructionIdentifier::ID_STLRH,
            InstructionIdentifier::ID_LDLARH, InstructionIdentifier::ID_LDARH,
            InstructionIdentifier::ID_STLLR, InstructionIdentifier::ID_STLR,
            InstructionIdentifier::ID_LDLAR, InstructionIdentifier::ID_LDAR
        };

        const auto insn
        {
            [size, L, o0] -> InstructionIdentifier
            {
                const unsigned short int encoding = (L << 1) | o0;
                if (size == 0b00)
                    return insnTable.at(encoding);
                else if (size == 0b00)
                    return insnTable.at(encoding + 4);
                return insnTable.at(encoding + 8);
            }()
        };

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
					Rn
				}
			)
		);

        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::LoadsAndStores::Ordered */
