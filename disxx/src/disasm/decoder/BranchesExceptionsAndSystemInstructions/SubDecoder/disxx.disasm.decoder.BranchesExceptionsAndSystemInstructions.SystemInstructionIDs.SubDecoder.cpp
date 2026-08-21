module disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDs.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.SystemOperand;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::BranchesExceptionsAndSystemInstructions::SystemInstructionIDs
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
        // +----------+-+--+---+---+---+---+--+
        // |1101010100|L|01|op1|CRn|CRm|op2|Rt|
        // +----------+-+--+---+---+---+---+--+

        unsigned short int L, op1, CRn, CRm, op2, Rt;
        L = utility::bits::extract<unsigned short int, std::uint32_t, 21, 21>(this->m_Insn);
        op1 = utility::bits::extract<unsigned short int, std::uint32_t, 16, 18>(this->m_Insn);
        CRn = utility::bits::extract<unsigned short int, std::uint32_t, 12, 15>(this->m_Insn);
        CRm = utility::bits::extract<unsigned short int, std::uint32_t, 8, 11>(this->m_Insn);
        op2 = utility::bits::extract<unsigned short int, std::uint32_t, 5, 7>(this->m_Insn);
        Rt = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        const auto encoding{static_cast<unsigned short int>((op1 << 11) | (CRn << 7) | (CRm << 3) | op2)};
        if (L == 0b1)
        {
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rt
				)
			);

            const std::unordered_map<unsigned short int, InstructionIdentifier> aliasTable = {
                {0b01101110111001, InstructionIdentifier::ID_GCSPOPM},
                {0b01101110111011, InstructionIdentifier::ID_GCSSS2}
            };

            if (auto it{aliasTable.find(encoding)}; it != aliasTable.end())
                return std::make_pair(it->second, std::move(this->m_Operands));
            
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 3>>(op1));
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 4>>(CRn));
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 4>>(CRm));
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 3>>(op2));

            return std::make_pair(InstructionIdentifier::ID_SYSL, std::move(this->m_Operands));
        }
        
        const std::unordered_map<unsigned short int, InstructionIdentifier> aliasTable = {
            {0b11001110000000, InstructionIdentifier::ID_APAS},
            {0b01101110011100, InstructionIdentifier::ID_CFP},
            {0b01101110011110, InstructionIdentifier::ID_COSP},
            {0b01101110011111, InstructionIdentifier::ID_CPP},
            {0b01101110011101, InstructionIdentifier::ID_DVP},
            {0b00001110111101, InstructionIdentifier::ID_GCSPOPCX},
            {0b00001110111110, InstructionIdentifier::ID_GCSPOPX},
            {0b01101110111000, InstructionIdentifier::ID_GCSPUSHM},
            {0b00001110111100, InstructionIdentifier::ID_GCSPUSHX},
            {0b01101110111010, InstructionIdentifier::ID_GCSSS1},
            {0b01101110010111, InstructionIdentifier::ID_TRCIT}
        };

        if (auto it{aliasTable.find(encoding)}; it != aliasTable.end())
        {
            if (op2 == 0b000 || op2 == 0b010 || (CRm == 0b0010 && op2 == 0b111))
			{
                this->m_Operands.emplace_back
				(
					std::make_unique<disxx::disasm::operand::Register>
					(
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rt
					)
				);
            }
			else if (CRm == 0b0011)
            {
                this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::SystemOperand>(CRm));
                this->m_Operands.emplace_back
				(
					std::make_unique<disxx::disasm::operand::Register>
					(
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rt
					)
				);
            }

            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (CRn == 0b0111 && (CRm & ~1) == 0b1000 && utility::bits::SysOp(op1, 0b0111, CRm, op2) == 1)
        {
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::SystemOperand>(encoding));
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rt
				)
			);
        
            return std::make_pair(InstructionIdentifier::ID_AT, std::move(this->m_Operands));
        }
        else if (op1 == 0b001 && CRn == 0b0111 && CRm == 0b0010 && utility::bits::SysOp(0b001, 0b0111, 0b0010, op2) == 2)
        {
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::SystemOperand>(op2));
        
            return std::make_pair(InstructionIdentifier::ID_BRB, std::move(this->m_Operands));
        }
        else if (CRn == 0b0111 && utility::bits::SysOp(op1, 0b0111, CRm, op2) == 3)
        {
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::SystemOperand>(encoding));
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rt
				)
			);

            return std::make_pair(InstructionIdentifier::ID_DC, std::move(this->m_Operands));
        }
        else if (CRn == 0b0111 && utility::bits::SysOp(op1, 0b0111, CRm, op2) == 4)
        {
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::SystemOperand>(encoding));
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rt
				)
			);
        
            return std::make_pair(InstructionIdentifier::ID_IC, std::move(this->m_Operands));
        }
        else if ((CRn & ~1) == 0b1000 && utility::bits::SysOp(op1, CRn, CRm, op2) == 5)
        {
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::SystemOperand>(encoding));
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rt
				)
			);
        
            return std::make_pair(InstructionIdentifier::ID_TLBI, std::move(this->m_Operands));
        }
        
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 3>>(op1));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 4>>(CRn));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 4>>(CRm));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 3>>(op2));
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_X,
				Rt
			)
		);

        return std::make_pair(InstructionIdentifier::ID_SYSL, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::BranchesExceptionsAndSystemInstructions::SystemInstructionIDs */
