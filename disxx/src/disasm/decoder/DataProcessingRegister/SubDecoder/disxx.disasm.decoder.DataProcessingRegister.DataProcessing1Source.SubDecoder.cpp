module disxx.disasm.decoder.DataProcessingRegister.DataProcessing1Source.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::DataProcessingRegister::DataProcessing1Source
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
		: disxx::disasm::decoder::abstract::SubDecoder{std::move(other)}
	{}

	SubDecoder &SubDecoder::operator=(SubDecoder &&other) noexcept
	{
		if (this != &other) [[likely]]
			disxx::disasm::decoder::abstract::SubDecoder::operator=(std::forward<SubDecoder &&>(other));
		return *this;
	}

	std::unique_ptr<disxx::disasm::decoder::abstract::SubDecoder> SubDecoder::Clone(void) const noexcept
	{ return std::make_unique<std::decay_t<std::decay_t<decltype(*this)>>>(*this); }

	DisassemblyResult SubDecoder::Decode(void) const noexcept
	{
        // +--+-+-+--------+-------+------+--+--+
        // |sf|1|S|11010110|opcode2|opcode|Rn|Rd|
        // +--+-+-+--------+-------+------+--+--+

        unsigned short int sf, S, opcode2, opcode, Rn, Rd;
        sf = utility::bits::extract<unsigned short int, std::uint32_t, 31, 31>(this->m_Insn);
        S = utility::bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        opcode2 = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = utility::bits::extract<unsigned short int, std::uint32_t, 10, 15>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b0000000000000, InstructionIdentifier::ID_RBIT},
            {0b0000000000001, InstructionIdentifier::ID_REV16},
            {0b0000000000010, InstructionIdentifier::ID_REV},
            {0b0000000000100, InstructionIdentifier::ID_CLZ},
            {0b0000000000101, InstructionIdentifier::ID_CLS},
            {0b0000000000110, InstructionIdentifier::ID_CTZ},
            {0b0000000000111, InstructionIdentifier::ID_CNT},
            {0b0000000001000, InstructionIdentifier::ID_ABS},
            {0b1000000000000, InstructionIdentifier::ID_RBIT},
            {0b1000000000001, InstructionIdentifier::ID_REV16},
            {0b1000000000010, InstructionIdentifier::ID_REV32},
            {0b1000000000011, InstructionIdentifier::ID_REV},
            {0b1000000000100, InstructionIdentifier::ID_CLZ},
            {0b1000000000101, InstructionIdentifier::ID_CLS},
            {0b1000000000110, InstructionIdentifier::ID_CTZ},
            {0b1000000000111, InstructionIdentifier::ID_CNT},
            {0b1000000001000, InstructionIdentifier::ID_ABS},
            {0b1000001000000, InstructionIdentifier::ID_PACIA},
            {0b1000001000001, InstructionIdentifier::ID_PACIB},
            {0b1000001000010, InstructionIdentifier::ID_PACDA},
            {0b1000001000011, InstructionIdentifier::ID_PACDB},
            {0b1000001000100, InstructionIdentifier::ID_AUTIA},
            {0b1000001000101, InstructionIdentifier::ID_AUTIB},
            {0b1000001000110, InstructionIdentifier::ID_AUTDA},
            {0b1000001000111, InstructionIdentifier::ID_AUTDB}
        };

        const auto encoding{static_cast<unsigned short int>((sf << 12) | (S << 11) | (opcode2 << 6) | opcode)};
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end())
        {
            static const std::unordered_map<unsigned int, InstructionIdentifier> insnTable2 = {
                {0b10000010010001111100000, InstructionIdentifier::ID_PACIZA},
                {0b10000010010011111100000, InstructionIdentifier::ID_PACIZB},
                {0b10000010010101111100000, InstructionIdentifier::ID_PACDZA},
                {0b10000010010111111100000, InstructionIdentifier::ID_PACDZB},
                {0b10000010011001111100000, InstructionIdentifier::ID_AUTIZA},
                {0b10000010011011111100000, InstructionIdentifier::ID_AUTIZB},
                {0b10000010011101111100000, InstructionIdentifier::ID_AUTDZA},
                {0b10000010011111111100000, InstructionIdentifier::ID_AUTDZB},
                {0b10000010100001111100000, InstructionIdentifier::ID_XPACI},
                {0b10000010100011111100000, InstructionIdentifier::ID_XPACD},
                {0b10000011000001111111110, InstructionIdentifier::ID_PACNBIASPPC},
                {0b10000011000011111111110, InstructionIdentifier::ID_PACNBIBSPPC},
                {0b10000011000101111111110, InstructionIdentifier::ID_PACIA171615},
                {0b10000011000111111111110, InstructionIdentifier::ID_PACIB171615},
                {0b10000011001000000011110, InstructionIdentifier::ID_AUTIASPPCR},
                {0b10000011001010000011110, InstructionIdentifier::ID_AUTIBSPPCR},
                {0b10000011010001111111110, InstructionIdentifier::ID_PACIASPPC},
                {0b10000011010011111111110, InstructionIdentifier::ID_PACIBSPPC},
                {0b10000011011101111111110, InstructionIdentifier::ID_AUTIA171615},
                {0b10000011011111111111110, InstructionIdentifier::ID_AUTIB171615}
            };

            const auto encoding2
			{
				static_cast<unsigned short int>
				(
					(encoding << 5)
						| (((opcode >> 2) == 0b1001 ? 0b00000 : Rn) << 5)
						| ((opcode >> 4) <= 0b01 ? 0b00000 : Rd)
				)
			};
            const auto it2 = insnTable2.find(opcode2);
            if (it2 == insnTable2.end()) [[unlikely]]
                return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

            if ((encoding2 & 0x3FF) == 0b1111111110 && (opcode >> 4) == 0b00)
			{
                this->m_Operands.emplace_back
				(
					std::make_unique<disxx::disasm::operand::Register>
					(
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rd,
						true
					)
				);
            }
			else if ((encoding2 & 0x3FF) == 0b1111111110 && (opcode >> 4) == 0b01)
            {
				this->m_Operands.emplace_back
				(
					std::make_unique<disxx::disasm::operand::Register>
					(
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rd
					)
				);
            }
			else if ((encoding2 & 0x3FF) == 0b0000011110)
            {
				this->m_Operands.emplace_back
				(
					std::make_unique<disxx::disasm::operand::Register>
					(
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rd
					)
				);
            }
			else if ((opcode >> 1) == 0b10111)
			{
                this->m_Operands.emplace_back
				(
					std::make_unique<disxx::disasm::operand::Register>
					(
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rn
					)
				);
   			}

            return std::make_pair(it2->second, std::move(this->m_Operands));
        }
            
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				sf
					? disxx::disasm::operand::Register::Type::TYPE_X
					: disxx::disasm::operand::Register::Type::TYPE_W,
				Rd
			)
		);
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				sf
					? disxx::disasm::operand::Register::Type::TYPE_X
					: disxx::disasm::operand::Register::Type::TYPE_W,
				Rn,
				opcode2 == 0b00001
			)
		);
    
        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingRegister::DataProcessing1Source */
