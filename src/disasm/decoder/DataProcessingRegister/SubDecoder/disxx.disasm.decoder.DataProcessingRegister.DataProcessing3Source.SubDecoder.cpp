module disxx.disasm.decoder.DataProcessingRegister.DataProcessing3Source.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::DataProcessingRegister::DataProcessing3Source
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
        // +--+----+-----+----+--+--+--+--+--+
        // |sf|op54|11011|op31|Rm|o0|Ra|Rn|Rd|
        // +--+----+-----+----+--+--+--+--+--+

        unsigned short int sf, op54, op31, Rm, o0, Ra, Rn, Rd;
        sf = utility::bits::extract<unsigned short int, std::uint32_t, 31, 31>(this->m_Insn);
        op54 = utility::bits::extract<unsigned short int, std::uint32_t, 29, 30>(this->m_Insn);
        op31 = utility::bits::extract<unsigned short int, std::uint32_t, 21, 23>(this->m_Insn);
        Rm = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        o0 = utility::bits::extract<unsigned short int, std::uint32_t, 15, 15>(this->m_Insn);
        Ra = utility::bits::extract<unsigned short int, std::uint32_t, 10, 14>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);
    
        static const std::unordered_map<unsigned short int, std::pair<InstructionIdentifier, std::optional<InstructionIdentifier>>> insnTable = {
            {0b0000000, {InstructionIdentifier::ID_MADD, InstructionIdentifier::ID_MUL}},
            {0b0000001, {InstructionIdentifier::ID_MSUB, InstructionIdentifier::ID_MNEG}},
            {0b1000000, {InstructionIdentifier::ID_MADD, InstructionIdentifier::ID_MUL}},
            {0b1000001, {InstructionIdentifier::ID_MSUB, InstructionIdentifier::ID_MNEG}},
            {0b1000010, {InstructionIdentifier::ID_SMADDL, InstructionIdentifier::ID_SMULL}},
            {0b1000011, {InstructionIdentifier::ID_SMSUBL, InstructionIdentifier::ID_SMNEGL}},
            {0b1000100, {InstructionIdentifier::ID_SMULH, std::nullopt}},
            {0b1000110, {InstructionIdentifier::ID_SMADDPT, std::nullopt}},
            {0b1000111, {InstructionIdentifier::ID_SMSUBPT, std::nullopt}},
            {0b1001010, {InstructionIdentifier::ID_UMADDL, InstructionIdentifier::ID_UMULL}},
            {0b1001011, {InstructionIdentifier::ID_UMSUBL, InstructionIdentifier::ID_UMNEGL}},
            {0b1001100, {InstructionIdentifier::ID_UMULH, std::nullopt}}
        };

        const unsigned short int encoding = (sf << 6) | (op54 << 4) | (op31 << 1) | o0;
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        const auto &[insn, alias]{it->second};

        // Alias here
        if (alias && Ra == 0b11111)
        {
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rd
				)
			);
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_W,
					Rn
				)
			);
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_W,
					Rm
				)
			);

            return std::make_pair(*alias, std::move(this->m_Operands));
        }
        else if (op31 == 0b001 || op31 == 0b101)
        {
			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rd
				)
			);
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_W,
					Rn
				)
			);
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_W,
					Rm
				)
			);
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Ra
				)
			);

            return std::make_pair(insn, std::move(this->m_Operands));
        }
        else if (op31 == 0b010 || op31 == 0b110)
        {
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rd
				)
			);
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rn
				)
			);
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rm
				)
			);

            return std::make_pair(insn, std::move(this->m_Operands));
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
				Rn
			)
		);
		this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				sf
					? disxx::disasm::operand::Register::Type::TYPE_X
					: disxx::disasm::operand::Register::Type::TYPE_W,
				Rm
			)
		);
		this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				sf
					? disxx::disasm::operand::Register::Type::TYPE_X
					: disxx::disasm::operand::Register::Type::TYPE_W,
				Ra
			)
		);

        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingRegister::DataProcessing3Source */
