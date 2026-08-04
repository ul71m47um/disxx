module disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Hints.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::BranchesExceptionsAndSystemInstructions::Hints
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
        // +--------------------+---+---+-----+
        // |11010101000000110010|CRm|op2|11111|
        // +--------------------+---+---+-----+

        unsigned short int CRm, op2;
        CRm = bits::extract<unsigned short int, std::uint32_t, 8, 11>(this->m_Insn);
        op2 = bits::extract<unsigned short int, std::uint32_t, 5, 7>(this->m_Insn);

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b0000000, InstructionIdentifier::ID_NOP},
            {0b0000001, InstructionIdentifier::ID_YIELD},
            {0b0000010, InstructionIdentifier::ID_WFE},
            {0b0000011, InstructionIdentifier::ID_WFI},
            {0b0000100, InstructionIdentifier::ID_SEV},
            {0b0000101, InstructionIdentifier::ID_SEVL},
            {0b0000110, InstructionIdentifier::ID_DGH},
            {0b0000111, InstructionIdentifier::ID_XPACLRI},
            {0b0001000, InstructionIdentifier::ID_PACIA1716},
            {0b0001010, InstructionIdentifier::ID_PACIB1716},
            {0b0001100, InstructionIdentifier::ID_AUTIA1716},
            {0b0001110, InstructionIdentifier::ID_AUTIB1716},
            {0b0010000, InstructionIdentifier::ID_ESB},
            {0b0010001, InstructionIdentifier::ID_PSB},
            {0b0010010, InstructionIdentifier::ID_TSB},
            {0b0010011, InstructionIdentifier::ID_GCSB},
            {0b0010100, InstructionIdentifier::ID_CSDB},
            {0b0010110, InstructionIdentifier::ID_CLRBHB},
            {0b0011000, InstructionIdentifier::ID_PACIAZ},
            {0b0011001, InstructionIdentifier::ID_PACIASP},
            {0b0011010, InstructionIdentifier::ID_PACIBZ},
            {0b0011011, InstructionIdentifier::ID_PACIBSP},
            {0b0011100, InstructionIdentifier::ID_AUTIAZ},
            {0b0011101, InstructionIdentifier::ID_AUTIASP},
            {0b0011110, InstructionIdentifier::ID_AUTIBZ},
            {0b0011111, InstructionIdentifier::ID_AUTIBSP},
            {0b0100000, InstructionIdentifier::ID_BTI},
            {0b0100010, InstructionIdentifier::ID_BTI},
            {0b0100100, InstructionIdentifier::ID_BTI},
            {0b0100110, InstructionIdentifier::ID_BTI},
            {0b0100111, InstructionIdentifier::ID_PACM},
            {0b0101000, InstructionIdentifier::ID_CHKFEAT},
            {0b0110000, InstructionIdentifier::ID_STSHH},
            {0b0110001, InstructionIdentifier::ID_STSHH}
        };

        const unsigned short int encoding = (CRm << 3) | op2;
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end())
        {
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 7>>(encoding));
            return std::make_pair(InstructionIdentifier::ID_HINT, std::move(this->m_Operands));
        }
    
        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::BranchesExceptionsAndSystemInstructions::Hints */
