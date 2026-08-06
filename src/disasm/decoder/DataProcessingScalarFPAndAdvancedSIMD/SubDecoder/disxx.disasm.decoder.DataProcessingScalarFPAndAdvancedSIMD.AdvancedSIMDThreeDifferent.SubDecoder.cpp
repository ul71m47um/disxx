module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeDifferent.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeDifferent
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
        // +-+-+-+-----+----+-+--+------+--+--+--+
        // |0|Q|U|01110|size|1|Rm|opcode|00|Rn|Rd|
        // +-+-+-+-----+----+-+--+------+--+--+--+

        unsigned short int Q, U, size, Rm, opcode, Rn, Rd;
        Q = utility::bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        U = utility::bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        size = utility::bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        Rm = utility::bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = utility::bits::extract<unsigned short int, std::uint32_t, 12, 15>(this->m_Insn);
        Rn = utility::bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = utility::bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        const auto addSingleTaFirst
		{
			[](disxx::disasm::operand::VectorArrangementSpecifier Ta, disxx::disasm::operand::VectorArrangementSpecifier Tb)
				-> std::array<disxx::disasm::operand::VectorArrangementSpecifier, 3>
			{ return {Ta, Tb, Tb}; }
		};
        const auto addDoubleTaFirst
		{
			[](disxx::disasm::operand::VectorArrangementSpecifier Ta, disxx::disasm::operand::VectorArrangementSpecifier Tb)
				-> std::array<disxx::disasm::operand::VectorArrangementSpecifier, 3>
			{ return {Ta, Ta, Tb}; }
		};
        const auto addSingleTbFirst
		{
			[](disxx::disasm::operand::VectorArrangementSpecifier Ta, disxx::disasm::operand::VectorArrangementSpecifier Tb)
				-> std::array<disxx::disasm::operand::VectorArrangementSpecifier, 3>
			{ return {Tb, Ta, Ta}; }
		};

        std::unordered_map
		<
			unsigned short int,
			std::pair
			<
				InstructionIdentifier,
				std::function
				<
					std::array
					<
						disxx::disasm::operand::VectorArrangementSpecifier,
						3
					>
					(
						disxx::disasm::operand::VectorArrangementSpecifier,
						disxx::disasm::operand::VectorArrangementSpecifier
					)
				>
			>
		> insnTable = {
            {0b000000, {InstructionIdentifier::ID_SADDL, addSingleTaFirst}},
            {0b100000, {InstructionIdentifier::ID_SADDL2, addSingleTaFirst}},
            {0b000001, {InstructionIdentifier::ID_SAADW, addDoubleTaFirst}},
            {0b100001, {InstructionIdentifier::ID_SAADW2, addDoubleTaFirst}},
            {0b000010, {InstructionIdentifier::ID_SSUBL, addSingleTaFirst}},
            {0b000010, {InstructionIdentifier::ID_SSUBL2, addSingleTaFirst}},
            {0b000011, {InstructionIdentifier::ID_SSUBW, addDoubleTaFirst}},
            {0b100011, {InstructionIdentifier::ID_SSUBW2, addDoubleTaFirst}},
            {0b000100, {InstructionIdentifier::ID_ADDHN, addSingleTbFirst}},
            {0b100100, {InstructionIdentifier::ID_ADDHN2, addSingleTbFirst}},
            {0b000101, {InstructionIdentifier::ID_SABAL, addSingleTaFirst}},
            {0b100101, {InstructionIdentifier::ID_SABAL2, addSingleTaFirst}},
            {0b000110, {InstructionIdentifier::ID_SUBHN, addSingleTbFirst}},
            {0b100110, {InstructionIdentifier::ID_SUBHN2, addSingleTbFirst}},
            {0b000111, {InstructionIdentifier::ID_SABDL, addSingleTaFirst}},
            {0b100111, {InstructionIdentifier::ID_SABDL2, addSingleTaFirst}},
            {0b001000, {InstructionIdentifier::ID_SMLAL, addSingleTaFirst}},
            {0b101000, {InstructionIdentifier::ID_SMLAL2, addSingleTaFirst}},
            {0b001001, {InstructionIdentifier::ID_SQDMLAL, addSingleTaFirst}},
            {0b101001, {InstructionIdentifier::ID_SQDMLAL2, addSingleTaFirst}},
            {0b001010, {InstructionIdentifier::ID_SMLSL, addSingleTaFirst}},
            {0b101010, {InstructionIdentifier::ID_SMLSL2, addSingleTaFirst}},
            {0b001011, {InstructionIdentifier::ID_SQDMLSL, addSingleTaFirst}},
            {0b101011, {InstructionIdentifier::ID_SQDMLSL2, addSingleTaFirst}},
            {0b001100, {InstructionIdentifier::ID_SMULL, addSingleTaFirst}},
            {0b101100, {InstructionIdentifier::ID_SMULL2, addSingleTaFirst}},
            {0b001101, {InstructionIdentifier::ID_SQDMULL, addSingleTaFirst}},
            {0b101101, {InstructionIdentifier::ID_SQDMULL2, addSingleTaFirst}},
            {0b001110, {InstructionIdentifier::ID_PMULL, addSingleTaFirst}},
            {0b101110, {InstructionIdentifier::ID_PMULL2, addSingleTaFirst}},
            {0b010000, {InstructionIdentifier::ID_UADDL, addSingleTaFirst}},
            {0b110000, {InstructionIdentifier::ID_UADDL2, addSingleTaFirst}},
            {0b010001, {InstructionIdentifier::ID_UAADW, addDoubleTaFirst}},
            {0b110001, {InstructionIdentifier::ID_UAADW2, addDoubleTaFirst}},
            {0b010010, {InstructionIdentifier::ID_USUBL, addSingleTaFirst}},
            {0b110010, {InstructionIdentifier::ID_USUBL2, addSingleTaFirst}},
            {0b010011, {InstructionIdentifier::ID_USUBW, addDoubleTaFirst}},
            {0b110011, {InstructionIdentifier::ID_USUBW2, addDoubleTaFirst}},
            {0b010100, {InstructionIdentifier::ID_RADDHN, addSingleTbFirst}},
            {0b110100, {InstructionIdentifier::ID_RADDHN2, addSingleTbFirst}},
            {0b010101, {InstructionIdentifier::ID_UABAL, addSingleTaFirst}},
            {0b110101, {InstructionIdentifier::ID_UABAL2, addSingleTaFirst}},
            {0b010110, {InstructionIdentifier::ID_RSUBHN, addSingleTbFirst}},
            {0b110110, {InstructionIdentifier::ID_RSUBHN2, addSingleTbFirst}},
            {0b010111, {InstructionIdentifier::ID_UABDL, addSingleTaFirst}},
            {0b110111, {InstructionIdentifier::ID_UABDL2, addSingleTaFirst}},
            {0b011000, {InstructionIdentifier::ID_UMLAL, addSingleTaFirst}},
            {0b111000, {InstructionIdentifier::ID_UMLAL2, addSingleTaFirst}},
            {0b011010, {InstructionIdentifier::ID_UMLSL, addSingleTaFirst}},
            {0b111010, {InstructionIdentifier::ID_UMLSL2, addSingleTaFirst}},
            {0b011100, {InstructionIdentifier::ID_UMULL, addSingleTaFirst}},
            {0b111100, {InstructionIdentifier::ID_UMULL2, addSingleTaFirst}}
        };

        const unsigned short int encoding = (Q << 5) | (U << 4) | opcode;
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end() || (size == 0b11 && opcode != 0b1110)) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        const auto &[insn, fmtf]{it->second};

        const auto result
        {
            [this, &opcode, &size, &Q] -> std::expected
			<
				std::pair
				<
					disxx::disasm::operand::VectorArrangementSpecifier,
					disxx::disasm::operand::VectorArrangementSpecifier
				>,
				disxx::utility::error::DisassemblyError
			>
            {
                if (opcode == 0b1001 || opcode == 0b1011)
                {
                    if (size == 0b00 || size == 0b11) [[unlikely]]
                        return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
                    
                    return std::make_pair
                    (
						disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(0b101 | ((size != 0b01) << 1))},
                        disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>((size << 1) | Q)}
                    );
                }
                else if (opcode == 0b1110)
                {
                    if (size == 0b01 || size == 0b10) [[unlikely]]
                        return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
                
                    return std::make_pair
                    (
						disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(size == 0b00 ? 0b0011 : 0b1111)},
                    	disxx::disasm::operand::VectorArrangementSpecifier{size == 0b00 ? Q : static_cast<unsigned short int>(0b110 | Q)}    
                    );
                }

                return std::make_pair
                (
					disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(((size + 1) << 1) | 0b1)},
                    disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>((size << 1) | Q)}
                );
            }()
        };

        if (!result) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        const auto &[Ta, Tb]{result.value()};

        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_V,
				Rd
			)
		);
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_V,
				Rn
			)
		);
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_V,
				Rm
			)
		);
        for (auto i{0}; const auto &spec : fmtf(Ta, Tb))
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(i++).get())->SetVectorArrangementSpecifier(spec);
        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeDifferent */
