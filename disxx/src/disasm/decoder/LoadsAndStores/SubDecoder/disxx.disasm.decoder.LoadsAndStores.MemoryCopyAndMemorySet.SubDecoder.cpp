module disxx.disasm.decoder.LoadsAndStores.MemoryCopyAndMemorySet.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::MemoryCopyAndMemorySet
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
        // +----+---+--+--+---+-+--+---+--+--+--+
        // |size|011|o0|01|op1|0|Rs|op2|01|Rn|Rd|
        // +----+---+--+--+---+-+--+---+--+--+--+

        unsigned short int o0, op1, Rs, op2, Rn, Rd;
        //size = utility::bits::extract<unsigned short int, std::uint32_t, 30, 31>(this->m_Insn);
        o0 = utility::bits::extract<unsigned short int, std::uint32_t, 26, 26>(this->m_Insn);
        op1 = utility::bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        Rs = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        op2 = utility::bits::extract<unsigned short int, std::uint32_t, 12, 15>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b0000000, InstructionIdentifier::ID_CPYFP},
            {0b0010000, InstructionIdentifier::ID_CPYFM},
            {0b0100000, InstructionIdentifier::ID_CPYFE},
            {0b0000001, InstructionIdentifier::ID_CPYFPWT},
            {0b0010001, InstructionIdentifier::ID_CPYFMWT},
            {0b0100001, InstructionIdentifier::ID_CPYFEWT},
            {0b0000010, InstructionIdentifier::ID_CPYFPRT},
            {0b0010010, InstructionIdentifier::ID_CPYFMRT},
            {0b0100010, InstructionIdentifier::ID_CPYFERT},
            {0b0000011, InstructionIdentifier::ID_CPYFPT},
            {0b0010011, InstructionIdentifier::ID_CPYFMT},
            {0b0100011, InstructionIdentifier::ID_CPYFET},
            {0b0000100, InstructionIdentifier::ID_CPYFPWN},
            {0b0010100, InstructionIdentifier::ID_CPYFMWN},
            {0b0100100, InstructionIdentifier::ID_CPYFEWN},
            {0b0000101, InstructionIdentifier::ID_CPYFPWTWN},
            {0b0010101, InstructionIdentifier::ID_CPYFMWTWN},
            {0b0100101, InstructionIdentifier::ID_CPYFEWTWN},
            {0b0000110, InstructionIdentifier::ID_CPYFPRTWN},
            {0b0010110, InstructionIdentifier::ID_CPYFMRTWN},
            {0b0100110, InstructionIdentifier::ID_CPYFERTWN},
            {0b0000111, InstructionIdentifier::ID_CPYFPTWN},
            {0b0010111, InstructionIdentifier::ID_CPYFMTWN},
            {0b0100111, InstructionIdentifier::ID_CPYFETWN},
            {0b0001000, InstructionIdentifier::ID_CPYFPRN},
            {0b0011000, InstructionIdentifier::ID_CPYFMRN},
            {0b0101000, InstructionIdentifier::ID_CPYFERN},
            {0b0001001, InstructionIdentifier::ID_CPYFPWTRN},
            {0b0011001, InstructionIdentifier::ID_CPYFMWTRN},
            {0b0101001, InstructionIdentifier::ID_CPYFEWTRN},
            {0b0001010, InstructionIdentifier::ID_CPYFPRTRN},
            {0b0011010, InstructionIdentifier::ID_CPYFMRTRN},
            {0b0101010, InstructionIdentifier::ID_CPYFERTRN},
            {0b0001011, InstructionIdentifier::ID_CPYFPTRN},
            {0b0011011, InstructionIdentifier::ID_CPYFMTRN},
            {0b0101011, InstructionIdentifier::ID_CPYFETRN},
            {0b0001100, InstructionIdentifier::ID_CPYFPN},
            {0b0011100, InstructionIdentifier::ID_CPYFMN},
            {0b0101100, InstructionIdentifier::ID_CPYFEN},
            {0b0001101, InstructionIdentifier::ID_CPYFPWTN},
            {0b0011101, InstructionIdentifier::ID_CPYFMWTN},
            {0b0101101, InstructionIdentifier::ID_CPYFEWTN},
            {0b0001110, InstructionIdentifier::ID_CPYFPRTN},
            {0b0011110, InstructionIdentifier::ID_CPYFMRTN},
            {0b0101110, InstructionIdentifier::ID_CPYFERTN},
            {0b0001111, InstructionIdentifier::ID_CPYFPTN},
            {0b0011111, InstructionIdentifier::ID_CPYFMTN},
            {0b0101111, InstructionIdentifier::ID_CPYFETN},
            {0b0110000, InstructionIdentifier::ID_SETP},
            {0b0110100, InstructionIdentifier::ID_SETM},
            {0b0111000, InstructionIdentifier::ID_SETE},
            {0b0110001, InstructionIdentifier::ID_SETPT},
            {0b0110101, InstructionIdentifier::ID_SETMT},
            {0b0111001, InstructionIdentifier::ID_SETET},
            {0b0110010, InstructionIdentifier::ID_SETPN},
            {0b0110110, InstructionIdentifier::ID_SETMN},
            {0b0111010, InstructionIdentifier::ID_SETEN},
            {0b0110011, InstructionIdentifier::ID_SETPTN},
            {0b0110111, InstructionIdentifier::ID_SETMTN},
            {0b0111011, InstructionIdentifier::ID_SETETN},
            {0b1000000, InstructionIdentifier::ID_CPYP},
            {0b1010000, InstructionIdentifier::ID_CPYM},
            {0b1100000, InstructionIdentifier::ID_CPYE},
            {0b1000001, InstructionIdentifier::ID_CPYPWT},
            {0b1010001, InstructionIdentifier::ID_CPYMWT},
            {0b1100001, InstructionIdentifier::ID_CPYEWT},
            {0b1000010, InstructionIdentifier::ID_CPYPRT},
            {0b1010010, InstructionIdentifier::ID_CPYMRT},
            {0b1100010, InstructionIdentifier::ID_CPYERT},
            {0b1000011, InstructionIdentifier::ID_CPYPT},
            {0b1010011, InstructionIdentifier::ID_CPYMT},
            {0b1100011, InstructionIdentifier::ID_CPYET},
            {0b1000100, InstructionIdentifier::ID_CPYPWN},
            {0b1010100, InstructionIdentifier::ID_CPYMWN},
            {0b1100100, InstructionIdentifier::ID_CPYEWN},
            {0b1000101, InstructionIdentifier::ID_CPYPWTWN},
            {0b1010101, InstructionIdentifier::ID_CPYMWTWN},
            {0b1100101, InstructionIdentifier::ID_CPYEWTWN},
            {0b1000110, InstructionIdentifier::ID_CPYPRTWN},
            {0b1010110, InstructionIdentifier::ID_CPYMRTWN},
            {0b1100110, InstructionIdentifier::ID_CPYERTWN},
            {0b1000111, InstructionIdentifier::ID_CPYPTWN},
            {0b1010111, InstructionIdentifier::ID_CPYMTWN},
            {0b1100111, InstructionIdentifier::ID_CPYETWN},
            {0b1001000, InstructionIdentifier::ID_CPYPRN},
            {0b1011000, InstructionIdentifier::ID_CPYMRN},
            {0b1101000, InstructionIdentifier::ID_CPYERN},
            {0b1001001, InstructionIdentifier::ID_CPYPWTRN},
            {0b1011001, InstructionIdentifier::ID_CPYMWTRN},
            {0b1101001, InstructionIdentifier::ID_CPYEWTRN},
            {0b1001010, InstructionIdentifier::ID_CPYPRTRN},
            {0b1011010, InstructionIdentifier::ID_CPYMRTRN},
            {0b1001011, InstructionIdentifier::ID_CPYPTRN},
            {0b1011011, InstructionIdentifier::ID_CPYMTRN},
            {0b1101011, InstructionIdentifier::ID_CPYETRN},
            {0b1001100, InstructionIdentifier::ID_CPYPN},
            {0b1011100, InstructionIdentifier::ID_CPYMN},
            {0b1101100, InstructionIdentifier::ID_CPYEN},
            {0b1001101, InstructionIdentifier::ID_CPYPWTN},
            {0b1011101, InstructionIdentifier::ID_CPYMWTN},
            {0b1101101, InstructionIdentifier::ID_CPYEWTN},
            {0b1001110, InstructionIdentifier::ID_CPYPRTN},
            {0b1011110, InstructionIdentifier::ID_CPYMRTN},
            {0b1101110, InstructionIdentifier::ID_CPYERTN},
            {0b1001111, InstructionIdentifier::ID_CPYPTN},
            {0b1011111, InstructionIdentifier::ID_CPYMTN},
            {0b1101111, InstructionIdentifier::ID_CPYETN},
            {0b1110000, InstructionIdentifier::ID_SETGP},
            {0b1110100, InstructionIdentifier::ID_SETGM},
            {0b1111000, InstructionIdentifier::ID_SETGE},
            {0b1110001, InstructionIdentifier::ID_SETGPT},
            {0b1110101, InstructionIdentifier::ID_SETGMT},
            {0b1111001, InstructionIdentifier::ID_SETGET},
            {0b1110010, InstructionIdentifier::ID_SETGPN},
            {0b1110110, InstructionIdentifier::ID_SETGMN},
            {0b1111010, InstructionIdentifier::ID_SETGEN},
            {0b1110011, InstructionIdentifier::ID_SETGPTN},
            {0b1110111, InstructionIdentifier::ID_SETGMTN},
            {0b1111011, InstructionIdentifier::ID_SETGETN}
        };

        const auto encoding{static_cast<unsigned short int>((o0 << 6) | (op1 << 4) | op2)};
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
			(
				disxx::disasm::operand::Register
				{
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rd
				}
			)
		);
        if (op1 == 0b11)
		{
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rs
				)
			);
        }
		else
		{
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
				(
					disxx::disasm::operand::Register
					{
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rs
					}
				)
			);
        }
		this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_X,
				Rn
			)
		);

        return std::make_pair(it->second, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::LoadsAndStores::MemoryCopyAndMemorySet */
