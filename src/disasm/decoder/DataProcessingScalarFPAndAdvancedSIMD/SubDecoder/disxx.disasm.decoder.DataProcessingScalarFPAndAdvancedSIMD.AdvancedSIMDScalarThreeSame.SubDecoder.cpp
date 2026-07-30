module;

#include <unordered_map>
#include <utility>
#include <cstdint>
#include <vector>
#include <array>

module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSame.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDScalarThreeSame
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
        // +--+-+-----+----+-+--+------+-+--+--+
        // |01|U|11110|size|1|Rm|opcode|1|Rn|Rd|
        // +--+-+-----+----+-+--+------+-+--+--+
    
        unsigned short int U, size, Rm, opcode, Rn, Rd;
        U = bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        size = bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        Rm = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = bits::extract<unsigned short int, std::uint32_t, 11, 15>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b000001, InstructionIdentifier::ID_SQADD},
            {0b000101, InstructionIdentifier::ID_SQSUB},
            {0b001001, InstructionIdentifier::ID_SQSHL},
            {0b001011, InstructionIdentifier::ID_SQRSHL},
            {0b010110, InstructionIdentifier::ID_SQDMULH},
            {0b100001, InstructionIdentifier::ID_UQADD},
            {0b100101, InstructionIdentifier::ID_UQSUB},
            {0b101001, InstructionIdentifier::ID_UQSHL},
            {0b101011, InstructionIdentifier::ID_UQRSHL},
            {0b110110, InstructionIdentifier::ID_SQRDMULH}
        };

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTableWithSize = {
            {0b00011011, InstructionIdentifier::ID_FMULX},
            {0b00111011, InstructionIdentifier::ID_FMULX},
            {0b00011100, InstructionIdentifier::ID_FCMEQ},
            {0b00111100, InstructionIdentifier::ID_FCMEQ},
            {0b00011111, InstructionIdentifier::ID_FRECPS},
            {0b00111111, InstructionIdentifier::ID_FRECPS},
            {0b01011111, InstructionIdentifier::ID_FRSQRTS},
            {0b01111111, InstructionIdentifier::ID_FRSQRTS},
            {0b01100110, InstructionIdentifier::ID_CMGT},
            {0b01100111, InstructionIdentifier::ID_CMGE},
            {0b01101000, InstructionIdentifier::ID_SSHL},
            {0b01101010, InstructionIdentifier::ID_SRSHL},
            {0b01110000, InstructionIdentifier::ID_ADD},
            {0b01110001, InstructionIdentifier::ID_CMTST},
            {0b10011100, InstructionIdentifier::ID_FCMGE},
            {0b10111100, InstructionIdentifier::ID_FCMGE},
            {0b10011101, InstructionIdentifier::ID_FACGE},
            {0b10111101, InstructionIdentifier::ID_FACGE},
            {0b11011010, InstructionIdentifier::ID_FABD},
            {0b11111010, InstructionIdentifier::ID_FABD},
            {0b11011100, InstructionIdentifier::ID_FCMGT},
            {0b11111100, InstructionIdentifier::ID_FCMGT},
            {0b11011101, InstructionIdentifier::ID_FACGT},
            {0b11111101, InstructionIdentifier::ID_FACGT},
            {0b11100110, InstructionIdentifier::ID_CMHI},
            {0b11100111, InstructionIdentifier::ID_CMHS},
            {0b11101000, InstructionIdentifier::ID_USHL},
            {0b11101010, InstructionIdentifier::ID_URSHL},
            {0b11110000, InstructionIdentifier::ID_SUB},
            {0b11110001, InstructionIdentifier::ID_CMEQ}
        };

		static constexpr std::array<disxx::disasm::operand::Register::Type, 4> types
		{
			disxx::disasm::operand::Register::Type::TYPE_B,
			disxx::disasm::operand::Register::Type::TYPE_H,
			disxx::disasm::operand::Register::Type::TYPE_S,
			disxx::disasm::operand::Register::Type::TYPE_D
		};

        unsigned short int encoding = (U << 5) | opcode;
        auto it{insnTable.find(encoding)};
		disxx::disasm::operand::Register::Type rsize{};
        if (it != insnTable.end()) [[unlikely]]
        {
            // Extra check if it's sqdmulh
            if (opcode == 0b10110 && size != 0b01 && size != 0b10) [[unlikely]]
                return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
            
            rsize = types[size];
        }
        else
        {
            encoding = (U << 7) | (size << 5) | opcode;
            it = insnTableWithSize.find(encoding);
            if (it == insnTable.end()) [[unlikely]]
                return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

            rsize = types[size | 0b10];
        }

        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(rsize, Rd));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(rsize, Rn));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(rsize, Rm));

        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDScalarThreeSame */
