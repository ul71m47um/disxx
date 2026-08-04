module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneousFP16.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDScalarTwoRegisterMiscellaneousFP16
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
        // +--+-+-----+-+------+------+--+--+--+
        // |01|U|11110|a|111100|opcode|10|Rn|Rd|
        // +--+-+-----+-+------+------+--+--+--+

        unsigned short int U, a, opcode, Rn, Rd;
        U = bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        a = bits::extract<unsigned short int, std::uint32_t, 23, 23>(this->m_Insn);
        opcode = bits::extract<unsigned short int, std::uint32_t, 12, 16>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b0011010, InstructionIdentifier::ID_FCVTNS},
            {0b0011011, InstructionIdentifier::ID_FCVTMS},
            {0b0011100, InstructionIdentifier::ID_FCVTAS},
            {0b0011101, InstructionIdentifier::ID_SCVTF},
            {0b0101100, InstructionIdentifier::ID_FCMGT},
            {0b0101101, InstructionIdentifier::ID_FCMEQ},
            {0b0101110, InstructionIdentifier::ID_FCMLT},
            {0b0111010, InstructionIdentifier::ID_FCVTPS},
            {0b0111011, InstructionIdentifier::ID_FCVTZS},
            {0b0111101, InstructionIdentifier::ID_FRECPE},
            {0b0111111, InstructionIdentifier::ID_FRECPX},
            {0b1011010, InstructionIdentifier::ID_FCVTNU},
            {0b1011011, InstructionIdentifier::ID_FCVTMU},
            {0b1011100, InstructionIdentifier::ID_FCVTAU},
            {0b1011101, InstructionIdentifier::ID_UCVTF},
            {0b1101100, InstructionIdentifier::ID_FCMGE},
            {0b1101101, InstructionIdentifier::ID_FCMLE},
            {0b1111010, InstructionIdentifier::ID_FCVTPU},
            {0b1111011, InstructionIdentifier::ID_FCVTZU},
            {0b1111101, InstructionIdentifier::ID_FRSQRTE}
        };

        const unsigned short int encoding = (U << 6) | (a << 5) | opcode;
        const auto it = insnTable.find(encoding);
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

        if (constexpr std::array<unsigned short int, 3> vals{0b01100, 0b01101, 0b01110}; std::ranges::find(vals, opcode) != vals.end())
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<float, 1>>(0.f));

        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDScalarTwoRegisterMiscellaneousFP16 */
