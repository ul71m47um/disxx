module disxx.disasm.decoder.LoadsAndStores.ExclusiveRegister.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::ExclusiveRegister
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
        // +-+--+-------+-+-+--+--+---+--+--+
        // |1|sz|0010010|L|0|Rs|o0|Rt2|Rn|Rt|
        // +-+--+-------+-+-+--+--+---+--+--+

        unsigned short int sz, L, Rs, o0, Rn, Rt;
        sz = utility::bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        L = utility::bits::extract<unsigned short int, std::uint32_t, 22, 22>(this->m_Insn);
        Rs = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        o0 = utility::bits::extract<unsigned short int, std::uint32_t, 15, 15>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static std::array<InstructionIdentifier, 4> insnTable = {
			InstructionIdentifier::ID_STTXR, InstructionIdentifier::ID_STLTXR,
			InstructionIdentifier::ID_LDTXR, InstructionIdentifier::ID_LDATXR
        };

		const auto rtype
		{
			sz
				? disxx::disasm::operand::Register::Type::TYPE_X
				: disxx::disasm::operand::Register::Type::TYPE_W
		};

        if (L == 0b0)
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(rtype, Rs));
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(rtype, Rt));
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
 
        return std::make_pair
		(
			insnTable.at(static_cast<unsigned long int>(L << 1) | o0),
			std::move(this->m_Operands)
		);
	}
} /* disxx::disasm::decoder::LoadsAndStores::ExclusiveRegister */
