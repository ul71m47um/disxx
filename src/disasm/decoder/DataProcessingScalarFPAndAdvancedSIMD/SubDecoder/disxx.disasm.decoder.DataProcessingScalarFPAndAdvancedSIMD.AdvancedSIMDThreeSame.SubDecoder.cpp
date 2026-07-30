module;

#include <unordered_map>
#include <functional>
#include <optional>
#include <utility>
#include <cstdint>
#include <vector>
#include <array>

module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSame.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeSame
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
        // +-+-+-+-----+----+-+--+------+-+--+--+
        // |0|Q|U|01110|size|1|Rm|opcode|1|Rn|Rd|
        // +-+-+-+-----+----+-+--+------+-+--+--+

        unsigned short int Q, U, size, Rm, opcode, Rn, Rd;
        Q = bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        U = bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        size = bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        Rm = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = bits::extract<unsigned short int, std::uint32_t, 11, 15>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        const auto getArrangementSpecifierBorder
        {
            [=](std::initializer_list<unsigned short int> borders = {}) -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier>
            {
                for (const auto &border : borders)
                    if (size == border) [[unlikely]]
                        return std::nullopt;
                return disxx::disasm::operand::VectorArrangementSpecifier
				{
					static_cast<unsigned short int>
					(
						(size << 1)
							| Q
					)
				};
            }
        };

        const auto getSzBasedArrangementSpecifier
        {
            [=] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier>
            {
                const auto sz{size & 0b01};
                if (sz == 0b1 && Q == 0b0) [[unlikely]]
                    return std::nullopt;
                return disxx::disasm::operand::VectorArrangementSpecifier
				{
					static_cast<unsigned short int>
					(
						((sz | 0b10) << 1)
							| Q
					)
				};
            }
        };
        
        std::unordered_map<unsigned short int, std::pair<InstructionIdentifier, std::function<std::optional<disxx::disasm::operand::VectorArrangementSpecifier>(void)>>> insnTable = {
            {
				0b000000,
				{
					InstructionIdentifier::ID_SHADD,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b000001,
				{
					InstructionIdentifier::ID_SQADD,
					getArrangementSpecifierBorder
				}
			},
            {
				0b000010,
				{
					InstructionIdentifier::ID_SRHADD,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b000100,
				{
					InstructionIdentifier::ID_SHSUB,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11});  }
				}
			},
            {
				0b000101,
				{
					InstructionIdentifier::ID_SQSUB,
					getArrangementSpecifierBorder
				}
			},
            {
				0b000110,
				{
					InstructionIdentifier::ID_CMGT,
					getArrangementSpecifierBorder
				}
			},
            {
				0b000111,
				{
					InstructionIdentifier::ID_CMGE,
					getArrangementSpecifierBorder
				}
			},
            {
				0b001000,
				{
					InstructionIdentifier::ID_SSHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b001001,
				{
					InstructionIdentifier::ID_SQSHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b001010,
				{
					InstructionIdentifier::ID_SRSHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b001011,
				{
					InstructionIdentifier::ID_SQRSHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b001100,
				{
					InstructionIdentifier::ID_SMAX,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b001101,
				{
					InstructionIdentifier::ID_SMIN,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b001110,
				{
					InstructionIdentifier::ID_SABD,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b001111,
				{
					InstructionIdentifier::ID_SABA,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b010000,
				{
					InstructionIdentifier::ID_ADD,
					getArrangementSpecifierBorder
				}
			},
            {
				0b010001,
				{
					InstructionIdentifier::ID_CMTST,
					getArrangementSpecifierBorder
				}
			},
            {
				0b010010,
				{
					InstructionIdentifier::ID_MLA,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b010011,
				{
					InstructionIdentifier::ID_MUL,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b010100,
				{
					InstructionIdentifier::ID_SMAXP,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b010101,
				{
					InstructionIdentifier::ID_SMINP,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b010110,
				{
					InstructionIdentifier::ID_SQDMULH,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b00, 0b11}); }
				}
			},
            {
				0b010111,
				{
					InstructionIdentifier::ID_ADDP,
					getArrangementSpecifierBorder
				}
			},
            {
				0b100000,
				{
					InstructionIdentifier::ID_UHADD,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b100001,
				{
					InstructionIdentifier::ID_UQADD,
					getArrangementSpecifierBorder
				}
			},
            {
				0b100010,
				{
					InstructionIdentifier::ID_URHADD,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b100100,
				{
					InstructionIdentifier::ID_UHSUB,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b100101,
				{
					InstructionIdentifier::ID_UQSUB,
					getArrangementSpecifierBorder
				}
			},
            {
				0b100110,
				{
					InstructionIdentifier::ID_CMHI,
					getArrangementSpecifierBorder
				}
			},
            {
				0b100111,
				{
					InstructionIdentifier::ID_CMHS,
					getArrangementSpecifierBorder
				}
			},
            {
				0b101000,
				{
					InstructionIdentifier::ID_USHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b101001,
				{
					InstructionIdentifier::ID_UQSHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b101010,
				{
					InstructionIdentifier::ID_URSHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b101011,
				{
					InstructionIdentifier::ID_UQRSHL,
					getArrangementSpecifierBorder
				}
			},
            {
				0b101100,
				{
					InstructionIdentifier::ID_UMAX,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b101101,
				{
					InstructionIdentifier::ID_UMIN,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b101110,
				{
					InstructionIdentifier::ID_UABD,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b101111,
				{
					InstructionIdentifier::ID_UABA,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b110000,
				{
					InstructionIdentifier::ID_SUB,
					getArrangementSpecifierBorder
				}
			},
            {
				0b110001,
				{
					InstructionIdentifier::ID_CMEQ,
					getArrangementSpecifierBorder
				}
			},
            {
				0b110010,
				{
					InstructionIdentifier::ID_MLS,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b110011,
				{
					InstructionIdentifier::ID_PMUL,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b01, 0b10, 0b11}); }
				}
			},
            {
				0b110100,
				{
					InstructionIdentifier::ID_UMAXP,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b110101,
				{
					InstructionIdentifier::ID_UMINP,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b11}); }
				}
			},
            {
				0b110110,
				{
					InstructionIdentifier::ID_SQRDMULH,
					[&getArrangementSpecifierBorder] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return getArrangementSpecifierBorder({0b00, 0b11}); }
				}
			}
        };

        std::unordered_map<unsigned short int, std::pair<InstructionIdentifier, std::function<std::optional<disxx::disasm::operand::VectorArrangementSpecifier>(void)>>> insnTableWithSize = {
            {0b00011000, {InstructionIdentifier::ID_FMAXNM, getSzBasedArrangementSpecifier}},
            {0b00011001, {InstructionIdentifier::ID_FMLA, getSzBasedArrangementSpecifier}},
            {0b00011010, {InstructionIdentifier::ID_FADD, getSzBasedArrangementSpecifier}},
            {0b00011011, {InstructionIdentifier::ID_FMULX, getSzBasedArrangementSpecifier}},
            {0b00011100, {InstructionIdentifier::ID_FCMEQ, getSzBasedArrangementSpecifier}},
            {0b00011110, {InstructionIdentifier::ID_FMAX, getSzBasedArrangementSpecifier}},
            {0b00011111, {InstructionIdentifier::ID_FRECPS, getSzBasedArrangementSpecifier}},
            {0b00000011, {InstructionIdentifier::ID_AND, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}},
            // Handles in other way - it has different arrangement specifiers
            {0b00011101, {InstructionIdentifier::ID_FMLAL, [] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return std::nullopt; }}},
            {0b00100011, {InstructionIdentifier::ID_BIC, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}},
            {0b01011000, {InstructionIdentifier::ID_FMINNM, getSzBasedArrangementSpecifier}},
            {0b01011001, {InstructionIdentifier::ID_FMLS, getSzBasedArrangementSpecifier}},
            {0b01011010, {InstructionIdentifier::ID_FSUB, getSzBasedArrangementSpecifier}},
            {0b01011011, {InstructionIdentifier::ID_FAMAX, getSzBasedArrangementSpecifier}},
            {0b01011110, {InstructionIdentifier::ID_FMIN, getSzBasedArrangementSpecifier}},
            {0b01011111, {InstructionIdentifier::ID_FRSQRTS, getSzBasedArrangementSpecifier}},
            {0b01000011, {InstructionIdentifier::ID_ORR, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}}, // Alias when Rm == Rn
            // The same thing again... handles in other way
            {0b01011101, {InstructionIdentifier::ID_FMLSL, [] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return std::nullopt; }}},
            {0b01100011, {InstructionIdentifier::ID_ORN, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}},
            {0b10011000, {InstructionIdentifier::ID_FMAXNMP, getSzBasedArrangementSpecifier}},
            {0b10011010, {InstructionIdentifier::ID_FADDP, getSzBasedArrangementSpecifier}},
            {0b10011011, {InstructionIdentifier::ID_FMUL, getSzBasedArrangementSpecifier}},
            {0b10011100, {InstructionIdentifier::ID_FCMGE, getSzBasedArrangementSpecifier}},
            {0b10011101, {InstructionIdentifier::ID_FACGE, getSzBasedArrangementSpecifier}},
            {0b10011110, {InstructionIdentifier::ID_FMAXP, getSzBasedArrangementSpecifier}},
            {0b10011111, {InstructionIdentifier::ID_FDIV, getSzBasedArrangementSpecifier}},
            {0b10000011, {InstructionIdentifier::ID_EOR, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}},
            // Still handles in othe way
            {0b10011001, {InstructionIdentifier::ID_FMLAL2, [] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return std::nullopt; }}},
            {0b10100011, {InstructionIdentifier::ID_BSL, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}},
            {0b11011000, {InstructionIdentifier::ID_FMINNMP, getSzBasedArrangementSpecifier}},
            {0b11011010, {InstructionIdentifier::ID_FABD, getSzBasedArrangementSpecifier}},
            {0b11011011, {InstructionIdentifier::ID_FAMIN, getSzBasedArrangementSpecifier}},
            {0b11011100, {InstructionIdentifier::ID_FCMGT, getSzBasedArrangementSpecifier}},
            {0b11011101, {InstructionIdentifier::ID_FACGT, getSzBasedArrangementSpecifier}},
            {0b11011110, {InstructionIdentifier::ID_FMINP, getSzBasedArrangementSpecifier}},
            {0b11011111, {InstructionIdentifier::ID_FSCALE, getSzBasedArrangementSpecifier}},
            {0b11000011, {InstructionIdentifier::ID_BIT, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}},
            // No comments
            {0b11011001, {InstructionIdentifier::ID_FMLSL2, [] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return std::nullopt; }}},
            {0b11100011, {InstructionIdentifier::ID_BIF, [Q] -> std::optional<disxx::disasm::operand::VectorArrangementSpecifier> { return disxx::disasm::operand::VectorArrangementSpecifier{Q}; }}}
        };

        unsigned short int encoding = (U << 5) | opcode;
        auto it{insnTable.find(encoding)};
        if (it == insnTable.end())
        {
            encoding = (U << 7) | (size << 5) | opcode;
            if (opcode != 0b00011 && opcode != 0b11101)
                encoding &= ~(0b01 << 5);
            it = insnTableWithSize.find(opcode);
            if (it == insnTableWithSize.end()) [[unlikely]]
                return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        }

        auto [insn, specifierFunc]{it->second};
        const auto &spec{specifierFunc()};
        if (encoding == 0b01000011 && Rm == Rn)
            insn = InstructionIdentifier::ID_MOV;
		else if (!spec) [[unlikely]]
        	return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

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
    
        const auto specArray
        {
            [&opcode, &Q](disxx::disasm::operand::VectorArrangementSpecifier specifier)
				-> std::array<disxx::disasm::operand::VectorArrangementSpecifier, 3>
            {
                if (opcode == 0b11001)
                {
                    return
                    {
						disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(Q ? 0b101 : 0b1110)},
						disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(Q ? 0b010 : 0b1110)},
						disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(Q ? 0b010 : 0b1110)}
                    };
                }

                const auto T{specifier};
                return {T, T, T};
            }(*spec)
        };

        for (auto i{0}; const auto &T : specArray)
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(i++).get())->SetVectorArrangementSpecifier(T);

        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeSame */
