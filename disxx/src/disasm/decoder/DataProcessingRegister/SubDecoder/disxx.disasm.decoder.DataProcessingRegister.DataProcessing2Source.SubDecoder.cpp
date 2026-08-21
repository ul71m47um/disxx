module disxx.disasm.decoder.DataProcessingRegister.DataProcessing2Source.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::DataProcessingRegister::DataProcessing2Source
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
        // +--+-+-+--------+--+------+--+--+
        // |sf|0|S|11010110|Rm|opcode|Rn|Rd|
        // +--+-+-+--------+--+------+--+--+

        unsigned short int sf, S, Rm, opcode, Rn, Rd;
        sf = utility::bits::extract<unsigned short int, std::uint32_t, 31, 31>(this->m_Insn);
        S = utility::bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        Rm = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = utility::bits::extract<unsigned short int, std::uint32_t, 10, 15>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b00000010, InstructionIdentifier::ID_UDIV},
            {0b00000011, InstructionIdentifier::ID_SDIV},
            {0b00001000, InstructionIdentifier::ID_LSLV},
            {0b00001001, InstructionIdentifier::ID_LSRV},
            {0b00001010, InstructionIdentifier::ID_ASRV},
            {0b00001011, InstructionIdentifier::ID_RORV},
            {0b00010000, InstructionIdentifier::ID_CRC32B},
            {0b00010001, InstructionIdentifier::ID_CRC32H},
            {0b00010010, InstructionIdentifier::ID_CRC32W},
            {0b00010100, InstructionIdentifier::ID_CRC32CB},
            {0b00010101, InstructionIdentifier::ID_CRC32CH},
            {0b00010110, InstructionIdentifier::ID_CRC32CW},
            {0b00011000, InstructionIdentifier::ID_SMAX},
            {0b00011001, InstructionIdentifier::ID_UMAX},
            {0b00011010, InstructionIdentifier::ID_SMIN},
            {0b00011011, InstructionIdentifier::ID_UMIN},
            {0b10000000, InstructionIdentifier::ID_SUBP},
            {0b10000010, InstructionIdentifier::ID_UDIV},
            {0b10000011, InstructionIdentifier::ID_SDIV},
            {0b10000100, InstructionIdentifier::ID_IRG},
            {0b10000101, InstructionIdentifier::ID_GMI},
            {0b10001000, InstructionIdentifier::ID_LSLV},
            {0b10001001, InstructionIdentifier::ID_LSRV},
            {0b10001010, InstructionIdentifier::ID_ASRV},
            {0b10001011, InstructionIdentifier::ID_RORV},
            {0b10001100, InstructionIdentifier::ID_PACGA},
            {0b10010011, InstructionIdentifier::ID_CRC32X},
            {0b10010111, InstructionIdentifier::ID_CRC32CX},
            {0b10011000, InstructionIdentifier::ID_SMAX},
            {0b10011001, InstructionIdentifier::ID_UMAX},
            {0b10011010, InstructionIdentifier::ID_SMIN},
            {0b10011011, InstructionIdentifier::ID_UMIN},
            {0b11000000, InstructionIdentifier::ID_SUBPS}
        };

        const auto encoding{static_cast<unsigned short int>((sf << 7) | (S << 6) | opcode)};
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        if (opcode == 0b000100)
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
			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rn,
					true
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

            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (opcode == 0b001100)
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
					Rm
				)
			);
			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rn,
					true
				)
			);

            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (opcode == 0b000101)
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
					Rn,
					true
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

            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (opcode == 0b000000)
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
					Rn,
					true
				)
			);
			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rm,
					true
				)
			);
        
            return std::make_pair(it->second, std::move(this->m_Operands));
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
				encoding == 0b1001001 || encoding == 0b10010111
					? disxx::disasm::operand::Register::Type::TYPE_X
					: (
						sf
							? disxx::disasm::operand::Register::Type::TYPE_X
							: disxx::disasm::operand::Register::Type::TYPE_W
					),
				Rm
			)
		);

        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingRegister::DataProcessing2Source */
