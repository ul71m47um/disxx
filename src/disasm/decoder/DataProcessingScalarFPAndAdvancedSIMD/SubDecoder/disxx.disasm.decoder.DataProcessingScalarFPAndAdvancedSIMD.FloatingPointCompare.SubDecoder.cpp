module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointCompare.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace
{
	inline disxx::disasm::operand::Register::Type mktp(unsigned short int ftype) noexcept
	{
		switch (ftype)
		{
		  case 0b11:
			return disxx::disasm::operand::Register::Type::TYPE_H;

		  case 0b10:
			[[fallthrough]];
		  case 0b00:
			return disxx::disasm::operand::Register::Type::TYPE_S;
		
		  default:
			return disxx::disasm::operand::Register::Type::TYPE_D;
		}
	}
} /* */

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::FloatingPointCompare
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
		if (this != &other) [[likely]]
			disxx::disasm::decoder::abstract::SubDecoder::operator=(other);
		return *this;
	}

	SubDecoder::SubDecoder(SubDecoder &&other) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{std::forward<SubDecoder &&>(other)}
	{}

	SubDecoder &SubDecoder::operator=(SubDecoder &&other) noexcept
	{
		if (this != &other) [[likely]]
			disxx::disasm::decoder::abstract::SubDecoder::operator=(std::forward<SubDecoder &&>(other));
		return *this;
	}

	std::unique_ptr<disxx::disasm::decoder::abstract::SubDecoder> SubDecoder::Clone(void) const noexcept
	{ return std::make_unique<std::decay_t<decltype(*this)>>(*this); }

	DisassemblyResult SubDecoder::Decode(void) const noexcept
	{
        // +-+-+-+-----+-----+-+--+--+----+--+-------+
        // |M|0|S|11110|ftype|1|Rm|op|1000|Rn|opcode2|
        // +-+-+-+-----+-----+-+--+--+----+--+-------+

        unsigned short int M, S, ftype, Rm, op, Rn, opcode2;
        M = utility::bits::extract<unsigned short int, std::uint32_t, 31, 31>(this->m_Insn);
        S = utility::bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        ftype = utility::bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        Rm = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        op = utility::bits::extract<unsigned short int, std::uint32_t, 14, 15>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        opcode2 = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b00000000000, InstructionIdentifier::ID_FCMP},
            {0b00000001000, InstructionIdentifier::ID_FCMP},
            {0b00000010000, InstructionIdentifier::ID_FCMPE},
            {0b00000011000, InstructionIdentifier::ID_FCMPE},
            {0b00010000000, InstructionIdentifier::ID_FCMP},
            {0b00010001000, InstructionIdentifier::ID_FCMP},
            {0b00010010000, InstructionIdentifier::ID_FCMPE},
            {0b00010011000, InstructionIdentifier::ID_FCMPE},
            {0b00110000000, InstructionIdentifier::ID_FCMP},
            {0b00110001000, InstructionIdentifier::ID_FCMP},
            {0b00110010000, InstructionIdentifier::ID_FCMPE},
            {0b00110011000, InstructionIdentifier::ID_FCMPE}
        };

        const auto encoding{static_cast<unsigned short int>((M << 10) | (S << 9) | (ftype << 7) | (op << 5) | opcode2)};
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(mktp(ftype), Rn));
        if ((Rm == 0b00000 && opcode2 == 0b00000) || (opcode2 == 0b01000 ? op == 0b01 : op == 0b11))
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<float, 32>>(0.0f));
        else
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(mktp(ftype), Rm));

        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::FloatingPointCompare */
