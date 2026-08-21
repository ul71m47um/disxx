module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSameFP16.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeSameFP16
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
        // +-+-+-+-----+-+--+--+--+------+-+--+--+
        // |0|Q|U|01110|a|10|Rm|00|opcode|1|Rn|Rd|
        // +-+-+-+-----+-+--+--+--+------+-+--+--+

        unsigned short int Q, U, a, Rm, opcode, Rn, Rd;
        Q = utility::bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        U = utility::bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        a = utility::bits::extract<unsigned short int, std::uint32_t, 23, 23>(this->m_Insn);
        Rm = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = utility::bits::extract<unsigned short int, std::uint32_t, 11, 13>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b00000, InstructionIdentifier::ID_FMAXNM},
            {0b00001, InstructionIdentifier::ID_FMLA},
            {0b00010, InstructionIdentifier::ID_FADD},
            {0b00011, InstructionIdentifier::ID_FMULX},
            {0b00100, InstructionIdentifier::ID_FCMEQ},
            {0b00110, InstructionIdentifier::ID_FMAX},
            {0b00111, InstructionIdentifier::ID_FRECPS},
            {0b01000, InstructionIdentifier::ID_FMINNM},
            {0b01001, InstructionIdentifier::ID_FMLS},
            {0b01010, InstructionIdentifier::ID_FSUB},
            {0b01011, InstructionIdentifier::ID_FAMAX},
            {0b01110, InstructionIdentifier::ID_FMIN},
            {0b01111, InstructionIdentifier::ID_FRSQRTS},
            {0b10000, InstructionIdentifier::ID_FMAXNMP},
            {0b10010, InstructionIdentifier::ID_FADDP},
            {0b10011, InstructionIdentifier::ID_FMUL},
            {0b10100, InstructionIdentifier::ID_FCMGE},
            {0b10101, InstructionIdentifier::ID_FACGE},
            {0b10110, InstructionIdentifier::ID_FMAXP},
            {0b10111, InstructionIdentifier::ID_FDIV},
            {0b11000, InstructionIdentifier::ID_FMINNMP},
            {0b11010, InstructionIdentifier::ID_FABD},
            {0b11011, InstructionIdentifier::ID_FAMIN},
            {0b11100, InstructionIdentifier::ID_FCMGT},
            {0b11101, InstructionIdentifier::ID_FACGT},
            {0b11110, InstructionIdentifier::ID_FMINP},
            {0b11111, InstructionIdentifier::ID_FSCALE}
        };

        const auto encoding{static_cast<unsigned short int>((U << 4) | (a << 3) | opcode)};
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(disxx::disasm::operand::Register::Type::TYPE_V, Rd));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(disxx::disasm::operand::Register::Type::TYPE_V, Rn));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(disxx::disasm::operand::Register::Type::TYPE_V, Rm));
        for (const disxx::disasm::operand::VectorArrangementSpecifier spec{static_cast<unsigned short int>(0b010 | Q)}; auto &pReg : this->m_Operands)
            static_cast<disxx::disasm::operand::Register *>(pReg.get())->SetVectorArrangementSpecifier(spec);

        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeSameFP16 */
