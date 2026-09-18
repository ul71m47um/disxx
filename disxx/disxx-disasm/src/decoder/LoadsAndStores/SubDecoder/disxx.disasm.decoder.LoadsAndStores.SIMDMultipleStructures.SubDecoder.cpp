module disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructures.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::SIMDMultipleStructures
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
        // +-+-+-------+-+------+------+----+--+--+
        // |0|Q|0011000|L|000000|opcode|size|Rn|Rt|
        // +-+-+-------+-+------+------+----+--+--+

        unsigned short int Q, L, opcode, size, Rn, Rt;
        Q = utility::bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        L = utility::bits::extract<unsigned short int, std::uint32_t, 22, 22>(this->m_Insn);
        opcode = utility::bits::extract<unsigned short int, std::uint32_t, 12, 15>(this->m_Insn);
        size = utility::bits::extract<unsigned short int, std::uint32_t, 10, 11>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, std::pair<InstructionIdentifier, unsigned short int>> insnTable = {
            {0b00000, {InstructionIdentifier::ID_ST4, 4}},
            {0b00010, {InstructionIdentifier::ID_ST4, 4}},
            {0b00100, {InstructionIdentifier::ID_ST3, 3}},
            {0b00110, {InstructionIdentifier::ID_ST3, 3}},
            {0b00111, {InstructionIdentifier::ID_ST1, 1}},
            {0b01000, {InstructionIdentifier::ID_ST2, 2}},
            {0b01010, {InstructionIdentifier::ID_ST2, 2}},
            {0b10000, {InstructionIdentifier::ID_LD4, 4}},
            {0b10010, {InstructionIdentifier::ID_LD4, 4}},
            {0b10100, {InstructionIdentifier::ID_LD3, 3}},
            {0b10110, {InstructionIdentifier::ID_LD3, 3}},
            {0b10111, {InstructionIdentifier::ID_LD1, 1}},
            {0b11000, {InstructionIdentifier::ID_LD2, 2}},
            {0b11010, {InstructionIdentifier::ID_LD2, 2}}
        };

        const auto it{insnTable.find(static_cast<unsigned short int>((L << 1) | opcode))};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        const auto &[insn, nregs]{it->second};
        
		for (const disxx::disasm::operand::VectorArrangementSpecifier spec{static_cast<unsigned short int>((size << 1) | Q)}; auto Ri : std::views::iota(Rt, std::add_sat<unsigned short int>(Rt, nregs)))
        {
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_V,
					Ri
				)
			);
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.rbegin()->get())->SetVectorArrangementSpecifier(spec);
        }
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
    
        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::LoadsAndStores::SIMDMultipleStructures */
