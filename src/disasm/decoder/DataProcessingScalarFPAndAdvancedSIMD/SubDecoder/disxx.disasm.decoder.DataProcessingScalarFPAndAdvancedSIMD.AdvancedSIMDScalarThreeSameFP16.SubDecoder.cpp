module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameFP16.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDScalarThreeSameFP16
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
        // +--+-+-----+-+--+--+--+------+-+--+--+
        // |01|U|11110|a|10|Rm|00|opcode|1|Rn|Rd|
        // +--+-+-----+-+--+--+--+------+-+--+--+

        unsigned short int U, a, Rm, opcode, Rn, Rd;
        U = utility::bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        a = utility::bits::extract<unsigned short int, std::uint32_t, 23, 23>(this->m_Insn);
        Rm = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = utility::bits::extract<unsigned short int, std::uint32_t, 11, 13>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b00011, InstructionIdentifier::ID_FMULX},
            {0b00100, InstructionIdentifier::ID_FCMEQ},
            {0b00111, InstructionIdentifier::ID_FRECPS},
            {0b01111, InstructionIdentifier::ID_FRSQRTS},
            {0b10100, InstructionIdentifier::ID_FCMGE},
            {0b10101, InstructionIdentifier::ID_FACGE},
            {0b11010, InstructionIdentifier::ID_FABD},
            {0b11100, InstructionIdentifier::ID_FCMGT},
            {0b11101, InstructionIdentifier::ID_FACGT}
        };

        const auto encoding{static_cast<unsigned short int>((U << 4) | (a << 3) | opcode)};
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_H,
				Rd
			)
		);
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_H,
				Rn
			)
		);
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_H,
				Rm
			)
		);
        
        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDScalarThreeSameFP16 */
