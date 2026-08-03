









module disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchRegister.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::BranchesExceptionsAndSystemInstructions::UnconditionalBranchRegister
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
        // +-------+---+---+---+--+---+
        // |1101011|opc|op2|op3|Rn|op4|
        // +-------+---+---+---+--+---+

        unsigned short int opc, op2, op3, Rn, op4;
        opc = bits::extract<unsigned short int, std::uint32_t, 21, 24>(this->m_Insn);
        op2 = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        op3 = bits::extract<unsigned short int, std::uint32_t, 10, 15>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        op4 = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

		const auto mknull
		{
			[] -> std::vector<disxx::disasm::operand::Register>
			{ return std::vector<disxx::disasm::operand::Register>{}; }
		};

        const auto mkRn
		{
			[Rn] -> std::vector<disxx::disasm::operand::Register>
        	{
				return std::vector<disxx::disasm::operand::Register>
				{
					disxx::disasm::operand::Register
					{
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rn
					}
				};
			}
		};

        const auto mkRm
		{
			[op4] -> std::vector<disxx::disasm::operand::Register>
        	{
				return std::vector<disxx::disasm::operand::Register>
				{
					disxx::disasm::operand::Register
					{
						disxx::disasm::operand::Register::Type::TYPE_X,
						op4
					}
				};
			}
		};

        const auto mkall
		{
			[Rn, op4] -> std::vector<disxx::disasm::operand::Register>
        	{
        	    return std::vector<disxx::disasm::operand::Register>
        	    {
        	        disxx::disasm::operand::Register
					{
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rn
					},
        	        disxx::disasm::operand::Register
					{
						disxx::disasm::operand::Register::Type::TYPE_X,
						op4
					}
        	    };
			}
        };

        const std::unordered_map<unsigned short int, std::tuple<InstructionIdentifier, bool, std::function<std::vector<disxx::disasm::operand::Register>(void)>>> insnTable = {
            {0b000011111000000, {InstructionIdentifier::ID_BR, op4 == 0b00000, mkRn}},
            {0b000011111000010, {InstructionIdentifier::ID_BRAAZ, op4 == 0b11111, mkRn}},
            {0b000011111000011, {InstructionIdentifier::ID_BRABZ, op4 == 0b11111, mkRn}},
            {0b000111111000000, {InstructionIdentifier::ID_BLR, op4 == 0b00000, mkRn}},
            {0b000111111000010, {InstructionIdentifier::ID_BLRAAZ, op4 == 0b11111, mkRn}},
            {0b000111111000011, {InstructionIdentifier::ID_BLRABZ, op4 == 0b11111, mkRn}},
            {0b001011111000000, {InstructionIdentifier::ID_RET, op4 == 0b00000, mkRn}},
            {0b001011111000010, {InstructionIdentifier::ID_RETAA, Rn == 0b11111 && op4 == 0b11111, mknull}},
            {0b001011111000010, {InstructionIdentifier::ID_RETAASPPCR, Rn == 0b11111 && op4 != 0b11111, mkRm}},
            {0b001011111000011, {InstructionIdentifier::ID_RETAB, Rn == 0b11111 && op4 == 0b11111, mknull}},
            {0b001011111000011, {InstructionIdentifier::ID_RETABSPPCR, Rn == 0b11111 && op4 != 0b11111, mkRm}},
            {0b010011111000000, {InstructionIdentifier::ID_ERET, Rn == 0b11111 && op4 == 0b00000, mknull}},
            {0b010011111000010, {InstructionIdentifier::ID_ERETAA, Rn == 0b11111 && op4 == 0b11111, mknull}},
            {0b010011111000011, {InstructionIdentifier::ID_ERETAB, Rn == 0b11111 && op4 == 0b11111, mknull}},
            {0b010111111000000, {InstructionIdentifier::ID_DRPS, Rn == 0b11111 && op4 == 0b00000, mknull}},
            {0b100011111000010, {InstructionIdentifier::ID_BRAA, true, mkall}},
            {0b100011111000011, {InstructionIdentifier::ID_BRAB, true, mkall}},
            {0b100111111000010, {InstructionIdentifier::ID_BLRAA, true, mkall}},
            {0b100111111000011, {InstructionIdentifier::ID_BLRAB, true, mkall}}
        };

        const unsigned short int encoding = (opc << 11) | (op2 << 6) | op3;
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        const auto &[insn, cond, func]{it->second};
        if (!cond) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        for (const auto &reg : func())
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(std::move(reg)));

        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::BranchesExceptionsAndSystemInstructions::UnconditionalBranchRegister */
