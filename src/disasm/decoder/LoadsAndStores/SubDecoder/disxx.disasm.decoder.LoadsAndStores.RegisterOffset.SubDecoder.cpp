module;

#include <unordered_map>
#include <utility>
#include <cstdint>
#include <memory>
#include <vector>
#include <tuple>

module disxx.disasm.decoder.LoadsAndStores.RegisterOffset.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.PrefetchOperand;
import disxx.disasm.operand.Register;
import disxx.disasm.operand.Shift;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::RegisterOffset
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
        // +----+---+--+--+---+-+--+------+-+--+--+--+
        // |size|111|VR|00|opc|1|Rm|option|S|10|Rn|Rt|
        // +----+---+--+--+---+-+--+------+-+--+--+--+

        unsigned short int size, VR, opc, Rm, option, S, Rn, Rt;
        size = bits::extract<unsigned short int, std::uint32_t, 30, 31>(this->m_Insn);
        VR = bits::extract<unsigned short int, std::uint32_t, 26, 26>(this->m_Insn);
        opc = bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        Rm = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        option = bits::extract<unsigned short int, std::uint32_t, 13, 15>(this->m_Insn);
        S = bits::extract<unsigned short int, std::uint32_t, 12, 12>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, std::tuple<InstructionIdentifier, disxx::disasm::operand::Register::Type, unsigned short int>> insnTable = {
        // |encoding|mnemonic|size|amount|
            {0b00000, {InstructionIdentifier::ID_STRB, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b00001, {InstructionIdentifier::ID_LDRB, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b00010, {InstructionIdentifier::ID_LDRSB, disxx::disasm::operand::Register::Type::TYPE_X, 1}},
            {0b00011, {InstructionIdentifier::ID_LDRSB, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b00100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_B, 1}},
            {0b00101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_B, 1}},
            {0b00110, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_Q, 4}},
            {0b00111, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_Q, 4}},
            {0b01000, {InstructionIdentifier::ID_STRH, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b01001, {InstructionIdentifier::ID_LDRH, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b01010, {InstructionIdentifier::ID_LDRSH, disxx::disasm::operand::Register::Type::TYPE_X, 1}},
            {0b01011, {InstructionIdentifier::ID_LDRSH, disxx::disasm::operand::Register::Type::TYPE_W, 1}},
            {0b01100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_H, 1}},
            {0b01101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_H, 1}},
            {0b10000, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_W, 2}},
            {0b10001, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_W, 2}},
            {0b10010, {InstructionIdentifier::ID_LDRSW, disxx::disasm::operand::Register::Type::TYPE_X, 2}},
            {0b10100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_S, 2}},
            {0b10101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_S, 2}},
            {0b11000, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_X, 3}},
            {0b11001, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_X, 3}},
            {0b11100, {InstructionIdentifier::ID_STR, disxx::disasm::operand::Register::Type::TYPE_D, 3}},
            {0b11101, {InstructionIdentifier::ID_LDR, disxx::disasm::operand::Register::Type::TYPE_D, 3}}
        };

        const unsigned short int encoding = (size << 3) | (VR << 2) | opc;
        if (const auto it{insnTable.find(encoding)}; it != insnTable.end())
        {
            const auto &[insn, rtype, amount]{it->second};

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
    
            if (option != 0b011)
            {
                static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddRegisterOffset
                (
                    disxx::disasm::operand::Register
                    {
						bits::extract<unsigned short int, unsigned short int, 0, 0>(option)
							? disxx::disasm::operand::Register::Type::TYPE_X
							: disxx::disasm::operand::Register::Type::TYPE_W,
                        Rm
                    }
                );

                if (encoding <= 0b00101 || (option != 0b010 && option != 0b110 && option != 0b111))
				{
                    static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddExtension
					(
						disxx::disasm::operand::Extension
						{
							option,
							amount
						}
					);
				}
                else if (S && amount)
				{
                    static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddShift
					(
						disxx::disasm::operand::Shift
						{
							0b000,
							amount
						}
					);
				}

                return std::make_pair(insn, std::move(this->m_Operands));
            }
            
            static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddRegisterOffset
			(
				disxx::disasm::operand::Register
				{
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rm
				}
			);
            if (S && amount)
			{
                static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddShift
				(
					disxx::disasm::operand::Shift
					{
						0b000,
						amount
					}
				);
			}

            return std::make_pair(insn, std::move(this->m_Operands));
        }
        
        if (encoding != 0b11010) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        InstructionIdentifier insn{};
        if ((option & 0b010) == 0b010) [[likely]]
            insn = (Rt & 0b11000) == 0b11000 ? InstructionIdentifier::ID_RPRFM : InstructionIdentifier::ID_PRFM;
        else [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

        /*
        if ((Rt & 0b11000) == 0b11000)
        {
            auto imm6{bits::extract<unsigned short int, unsigned short int, 2, 2>(option) << 5};
            imm6 |= bits::extract<unsigned short int, unsigned short int, 0, 0>(option) << 4;
            imm6 |= S << 3;
            imm6 |= bits::extract<unsigned short int, unsigned short int, 0, 2>(Rt);
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 6>>(imm6));
        }
        */

        this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::PrefetchOperand>(encoding));
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
        static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands.rbegin()->get())->AddRegisterOffset
        (
            disxx::disasm::operand::Register
            {
                ((Rt & 0b11000) == 0b11000 || bits::extract<unsigned short int, unsigned short int, 0, 0>(option) == 0b1)
					? disxx::disasm::operand::Register::Type::TYPE_X
					: disxx::disasm::operand::Register::Type::TYPE_W,
				Rm
            }
        );

        if ((Rt & 0b11000) != 0b11000)
        {
            switch (option)
            {
              case 0b010: [[fallthrough]];
              case 0b110: [[fallthrough]];
              case 0b111:
                static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands[2].get())->AddExtension
					(
						disxx::disasm::operand::Extension
						{
							option,
							static_cast<unsigned short int>(S ? 3 : 0)
						}
					);
                return std::make_pair(insn, std::move(this->m_Operands));

              default:
                if (S)
				{
                    static_cast<disxx::disasm::operand::LoadsAndStoresAddress *>(this->m_Operands[2].get())->AddShift
					(
						disxx::disasm::operand::Shift
						{
							0b000,
							3
						}
					);
				}

                return std::make_pair(insn, std::move(this->m_Operands));
            }
        }

        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::LoadsAndStores::RegisterOffset */
