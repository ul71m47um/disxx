










module disxx.disasm.Instruction;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.decoder.DecoderFactory;

namespace disxx::disasm
{
	Instruction::Instruction(void) noexcept
		: m_Operands{}
		, m_ProgramCounterRelevantAddress{std::nullopt}
		, m_Address{std::numeric_limits<Address>::min()}
		, m_Bytes{std::numeric_limits<Bytes>::min()}
		, m_Identifier{}
	{}

	Instruction::Instruction(const Instruction &other) noexcept
		: m_Operands{}
		, m_ProgramCounterRelevantAddress{other.m_ProgramCounterRelevantAddress}
		, m_Address{other.m_Address}
		, m_Bytes{other.m_Bytes}
		, m_Identifier{other.m_Identifier}
	{
		for (const auto &opr : other.m_Operands)
			this->m_Operands.emplace_back(opr->Clone());
	}

	Instruction &Instruction::operator=(const Instruction &other) noexcept
	{
		this->m_Identifier = other.m_Identifier;
		for (const auto &opr : other.m_Operands)
			this->m_Operands.emplace_back(opr->Clone());
		this->m_ProgramCounterRelevantAddress = other.m_ProgramCounterRelevantAddress;
		this->m_Address = other.m_Address;
		this->m_Bytes = other.m_Bytes;

		return *this;
	}

	Instruction::Instruction(Instruction &&other) noexcept
		: m_Operands{std::move(other.m_Operands)}
		, m_ProgramCounterRelevantAddress{std::move(other.m_ProgramCounterRelevantAddress)}
		, m_Address{std::move(other.m_Address)}
		, m_Bytes{std::move(other.m_Bytes)}
		, m_Identifier{std::move(other.m_Identifier)}
	{}

	Instruction &Instruction::operator=(Instruction &&other) noexcept
	{
		this->m_Identifier = std::move(other.m_Identifier);
		this->m_Operands = std::move(other.m_Operands);
		this->m_ProgramCounterRelevantAddress = std::move(other.m_ProgramCounterRelevantAddress);
		this->m_Address = std::move(other.m_Address);
		this->m_Bytes = std::move(other.m_Bytes);

		return *this;
	}

	bool Instruction::operator==(const Instruction &other) noexcept
	{ return this->m_Bytes == other.m_Bytes; }

	bool Instruction::operator!=(const Instruction &other) noexcept
	{ return this->m_Bytes != other.m_Bytes; }
} /* disxx::disasm */
