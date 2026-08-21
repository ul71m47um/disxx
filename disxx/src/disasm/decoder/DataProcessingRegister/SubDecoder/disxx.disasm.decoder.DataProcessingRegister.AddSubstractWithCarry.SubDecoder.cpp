module disxx.disasm.decoder.DataProcessingRegister.AddSubstractWithCarry.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::DataProcessingRegister::AddSubstractWithCarry
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
	{ return std::make_unique<std::decay_t<decltype(*this)>>(*this); }

	DisassemblyResult SubDecoder::Decode(void) const noexcept
	{
        // +--+--+-+--------+--+------+--+--+
        // |sf|op|S|11010000|Rm|000000|Rn|Rd|
        // +--+--+-+--------+--+------+--+--+

        unsigned short int sf, op, S, Rm, Rn, Rd;
        sf = utility::bits::extract<unsigned short int, std::uint32_t, 31, 31>(this->m_Insn);
        op = utility::bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        S = utility::bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        Rm = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, std::pair<InstructionIdentifier, std::optional<InstructionIdentifier>>> insnTable = {
            {0b000, {InstructionIdentifier::ID_ADC, std::nullopt}},
            {0b001, {InstructionIdentifier::ID_ADCS, std::nullopt}},
            {0b010, {InstructionIdentifier::ID_SBC, InstructionIdentifier::ID_NGC}},
            {0b011, {InstructionIdentifier::ID_SBCS, InstructionIdentifier::ID_NGCS}},
            {0b100, {InstructionIdentifier::ID_ADC, std::nullopt}},
            {0b101, {InstructionIdentifier::ID_ADCS, std::nullopt}},
            {0b110, {InstructionIdentifier::ID_SBC, std::nullopt}},
            {0b111, {InstructionIdentifier::ID_SBCS, std::nullopt}}
        };

        const auto encoding{static_cast<unsigned short int>((sf << 2) | (op << 1) | S)};
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        const auto &[insn, alias]{it->second};

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
        if (alias && Rn == 0b11111)
        {
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

            return std::make_pair(*alias, std::move(this->m_Operands));
        }
         
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

        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingRegister::AddSubstractWithCarry */
