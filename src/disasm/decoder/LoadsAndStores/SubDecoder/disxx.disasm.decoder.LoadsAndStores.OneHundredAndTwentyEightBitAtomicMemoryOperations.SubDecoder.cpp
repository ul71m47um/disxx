module disxx.disasm.decoder.LoadsAndStores.OneHundredAndTwentyEightBitAtomicMemoryOperations.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::OneHundredAndTwentyEightBitAtomicMemoryOperations
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
        // +-+-+------+-+-+-+---+--+---+--+--+--+
        // |0|S|011001|A|R|1|Rt2|o3|opc|00|Rn|Rt|
        // +-+-+------+-+-+-+---+--+---+--+--+--+

        unsigned short int S, A, R, Rt2, o3, opc, Rn, Rt;
        S = bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        A = bits::extract<unsigned short int, std::uint32_t, 23, 23>(this->m_Insn);
        R = bits::extract<unsigned short int, std::uint32_t, 22, 22>(this->m_Insn);
        Rt2 = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        o3 = bits::extract<unsigned short int, std::uint32_t, 15, 15>(this->m_Insn);
        opc = bits::extract<unsigned short int, std::uint32_t, 12, 14>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b0000001, InstructionIdentifier::ID_LDCLRP},
            {0b0000011, InstructionIdentifier::ID_LDSETP},
            {0b0001000, InstructionIdentifier::ID_SWPP},
            {0b0001001, InstructionIdentifier::ID_RCWCLRP},
            {0b0001010, InstructionIdentifier::ID_RCWSWPP},
            {0b0001011, InstructionIdentifier::ID_RCWSETP},
            {0b0010001, InstructionIdentifier::ID_LDCLRPL},
            {0b0010011, InstructionIdentifier::ID_LDSETPL},
            {0b0011000, InstructionIdentifier::ID_SWPPL},
            {0b0011001, InstructionIdentifier::ID_RCWCLRPL},
            {0b0011010, InstructionIdentifier::ID_RCWSWPPL},
            {0b0011011, InstructionIdentifier::ID_RCWSETPL},
            {0b0100001, InstructionIdentifier::ID_LDCLRPA},
            {0b0100011, InstructionIdentifier::ID_LDSETPA},
            {0b0101000, InstructionIdentifier::ID_SWPPA},
            {0b0101001, InstructionIdentifier::ID_RCWCLRPA},
            {0b0101010, InstructionIdentifier::ID_RCWSWPPA},
            {0b0101011, InstructionIdentifier::ID_RCWSETPA},
            {0b0110001, InstructionIdentifier::ID_LDCLRPAL},
            {0b0110011, InstructionIdentifier::ID_LDSETPAL},
            {0b0111000, InstructionIdentifier::ID_SWPPAL},
            {0b0111001, InstructionIdentifier::ID_RCWCLRPAL},
            {0b0111010, InstructionIdentifier::ID_RCWSWPPAL},
            {0b0111011, InstructionIdentifier::ID_RCWSETPAL},
            {0b1001001, InstructionIdentifier::ID_RCWSCLRP},
            {0b1001010, InstructionIdentifier::ID_RCWSSWPP},
            {0b1001011, InstructionIdentifier::ID_RCWSSETP},
            {0b1011001, InstructionIdentifier::ID_RCWSCLRPL},
            {0b1011010, InstructionIdentifier::ID_RCWSSWPPL},
            {0b1011011, InstructionIdentifier::ID_RCWSSETPL},
            {0b1101001, InstructionIdentifier::ID_RCWSCLRPA},
            {0b1101010, InstructionIdentifier::ID_RCWSSWPPA},
            {0b1101011, InstructionIdentifier::ID_RCWSSETPA},
            {0b1111001, InstructionIdentifier::ID_RCWSCLRPAL},
            {0b1111010, InstructionIdentifier::ID_RCWSSWPPAL},
            {0b1111011, InstructionIdentifier::ID_RCWSSETPAL}
        };

        const unsigned short int encoding = (S << 6) | (A << 5) | (R << 4) | (o3 << 3) | opc;
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
    
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_X,
				Rt
			)
		);
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_X,
				Rt2
			)
		);
		this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
			(
				disxx::disasm::operand::Register
				{
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rn,
					true
				}
			)
		);

        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::LoadsAndStores::128BitAtomicMemoryOperations */
