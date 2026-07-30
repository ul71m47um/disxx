module;

#include <unordered_map>
#include <utility>
#include <cstdint>
#include <memory>
#include <vector>

module disxx.disasm.decoder.DataProcessingImmediate.LogicalImmediate.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::DataProcessingImmediate::LogicalImmediate
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
	{ return std::make_unique<std::decay_t<std::decay_t<decltype(*this)>>>(*this); }

	DisassemblyResult SubDecoder::Decode(void) const noexcept
	{
        // +--+---+------+-+----+----+--+--+
        // |sf|opc|100100|N|immr|imms|Rn|Rd|
        // +--+---+------+-+----+----+--+--+

        unsigned short int sf, opc, N, immr, imms, Rn, Rd;
        sf = bits::extract<unsigned short int, std::uint32_t, 31, 31>(this->m_Insn);
        opc = bits::extract<unsigned short int, std::uint32_t, 29, 30>(this->m_Insn);
        N = bits::extract<unsigned short int, std::uint32_t, 22, 22>(this->m_Insn);
        immr = bits::extract<unsigned short int, std::uint32_t, 16, 21>(this->m_Insn);
        imms = bits::extract<unsigned short int, std::uint32_t, 10, 15>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        static const std::unordered_map<unsigned short int, std::pair<InstructionIdentifier, std::optional<InstructionIdentifier>>> insnTable = {
            {0b0000, {InstructionIdentifier::ID_AND, std::nullopt}},
            {0b0010, {InstructionIdentifier::ID_ORR, InstructionIdentifier::ID_MOV}},
            {0b0100, {InstructionIdentifier::ID_EOR, std::nullopt}},
            {0b0110, {InstructionIdentifier::ID_ANDS, InstructionIdentifier::ID_TST}},
            {0b1000, {InstructionIdentifier::ID_AND, std::nullopt}},
            {0b1010, {InstructionIdentifier::ID_ORR, InstructionIdentifier::ID_MOV}},
            {0b1100, {InstructionIdentifier::ID_EOR, std::nullopt}},
            {0b1110, {InstructionIdentifier::ID_ANDS, InstructionIdentifier::ID_TST}}
        };

        const unsigned short int encoding = (sf << 3) | (opc << 2) | (sf == 0b1 ? 0 : N);
        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        const auto &[insn, alias]{it->second};

        std::variant
        <
            disxx::disasm::operand::Immediate<unsigned int, 32>,
            disxx::disasm::operand::Immediate<unsigned long long int, 64>
        > imm{};
        if (sf == 0b1)
        {
            if (const auto result{bits::DecodeBitMasks<unsigned long long int, 64>(N, imms, immr, true)})
                imm.emplace<1>(disxx::disasm::operand::Immediate<unsigned long long int, 64>{std::get<0>(result.value())});
            else
                return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        }
        else
        {
            if (const auto result{bits::DecodeBitMasks<unsigned long long int, 64>(N, imms, immr, true)})
                imm.emplace<0>(disxx::disasm::operand::Immediate<unsigned int, 32>{static_cast<unsigned int>(std::get<0>(result.value()))});
            else
                return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
        }

        if (alias && opc == 0b01 && Rn == 0b11111 && !bits::MoveWidePreferred(sf, N, imms, immr))
        {
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
            std::visit
            (
                [this](auto &&immediate) -> void
                { this->m_Operands.emplace_back(std::make_unique<std::decay_t<decltype(immediate)>>(immediate)); },
                imm
            );

            return std::make_pair(*alias, std::move(this->m_Operands));
        }
        else if (alias && opc == 0b11 && Rd == 0b11111)
        {
			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					sf
						? disxx::disasm::operand::Register::Type::TYPE_X
						: disxx::disasm::operand::Register::Type::TYPE_W,
					Rd,
					opc != 0b11
				)
			);
            std::visit
            (
                [this](auto &&immediate) -> void
                { this->m_Operands.emplace_back(std::make_unique<std::decay_t<decltype(immediate)>>(immediate)); },
                imm
            );

            return std::make_pair(alias.value(), std::move(this->m_Operands));
        }
    
		this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				sf
					? disxx::disasm::operand::Register::Type::TYPE_X
					: disxx::disasm::operand::Register::Type::TYPE_W,
				Rd,
				opc != 0b11
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
        std::visit
        (
            [this](auto &&immediate) -> void
            { this->m_Operands.emplace_back(std::make_unique<std::decay_t<decltype(immediate)>>(immediate)); },
            imm
        );
    
        return std::make_pair(insn, std::move(this->m_Operands));
	}
} /* disxx::disasm::decoder::DataProcessingImmediate::LogicalImmediate */
