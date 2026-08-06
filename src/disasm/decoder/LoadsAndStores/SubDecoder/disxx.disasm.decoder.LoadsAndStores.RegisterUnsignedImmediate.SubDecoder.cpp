module disxx.disasm.decoder.LoadsAndStores.RegisterUnsignedImmediate.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.PrefetchOperand;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::RegisterUnsignedImmediate
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
        // +----+---+--+--+---+-----+--+--+
        // |size|111|VR|01|opc|imm12|Rn|Rt|
        // +----+---+--+--+---+-----+--+--+

        unsigned short int size, VR, opc, imm12, Rn, Rt;
        size = utility::bits::extract<unsigned short int, std::uint32_t, 30, 31>(this->m_Insn);
        VR = utility::bits::extract<unsigned short int, std::uint32_t, 26, 26>(this->m_Insn);
        opc = utility::bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        imm12 = utility::bits::extract<unsigned short int, std::uint32_t, 10, 21>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);
        
        /*
        if ((size & 0b10) == 0b10 && VR == 0b0 && opc == 0b11)
            throw DisassemblyError(this->m_Insn);
        else if (size != 0b00 && VR == 0b1 && (opc & 0b10) == 0b10)
            throw DisassemblyError(this->m_Insn);
        */


        std::unordered_map<unsigned short int, std::tuple<InstructionIdentifier, disxx::disasm::operand::Register::Type, unsigned short int>> insnTable = {
        //  |encoding|mnemonic|register size|data size (already in bytes)|
            {0b00000, {InstructionIdentifier::ID_STRB, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b00001, {InstructionIdentifier::ID_LDRB, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b00010, {InstructionIdentifier::ID_LDRSB, disxx::disasm::operand::Register::Type::TYPE_X, 1}},
            {0b00011, {InstructionIdentifier::ID_LDRSB, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b00100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_B, 1}},
            {0b00101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_B, 1}},
            {0b00110, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_Q, 16}},
            {0b00111, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_Q, 16}},
            {0b01000, {InstructionIdentifier::ID_STRH, disxx::disasm::operand::Register::Type::TYPE_W, 2}},
            {0b01001, {InstructionIdentifier::ID_LDRH, disxx::disasm::operand::Register::Type::TYPE_W, 2}},
            {0b01010, {InstructionIdentifier::ID_LDRSH, disxx::disasm::operand::Register::Type::TYPE_X, 2}},
            {0b01011, {InstructionIdentifier::ID_LDRSH, disxx::disasm::operand::Register::Type::TYPE_W, 2}},
            {0b01100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_H, 2}},
            {0b01101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_H, 2}},
            {0b10000, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_W, 4}},
            {0b10001, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_W, 4}},
            {0b10010, {InstructionIdentifier::ID_LDRSW, disxx::disasm::operand::Register::Type::TYPE_X, 4}},
            {0b10100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_S, 4}},
            {0b10101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_S, 4}},
            {0b11000, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_X, 8}},
            {0b11001, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_X, 8}},
            {0b11100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_D, 8}},
            {0b11101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_D, 8}}
        };

        unsigned short int encoding = (size << 3) | (VR << 2) | opc;
        if (const auto it{insnTable.find(encoding)}; it != insnTable.end())
        {
            const auto &[insn, rtype, dsize]{it->second};

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
            if (imm12)
			{
                static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddImmediatePreIndexedOffset
				(
					disxx::disasm::operand::Immediate<unsigned short int, 12>{static_cast<unsigned short int>(imm12 * dsize)},
					disxx::disasm::operand::LoadsAndStoresAddress::PreIndexedOffsetKind::IDX_REGULAR
				);
            }

			return std::make_pair(insn, std::move(this->m_Operands));
        }

        if (encoding != 0b11010) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
            
        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::PrefetchOperand>(Rt));
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
		if (imm12)
		{
            static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddImmediatePreIndexedOffset
			(
				disxx::disasm::operand::Immediate<unsigned short int, 12>{static_cast<unsigned short int>(imm12 * 8)},
				disxx::disasm::operand::LoadsAndStoresAddress::PreIndexedOffsetKind::IDX_REGULAR
			);
        }

		return std::make_pair(InstructionIdentifier::ID_PRFM, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::LoadsAndStores::RegisterUnsignedImmediate */
