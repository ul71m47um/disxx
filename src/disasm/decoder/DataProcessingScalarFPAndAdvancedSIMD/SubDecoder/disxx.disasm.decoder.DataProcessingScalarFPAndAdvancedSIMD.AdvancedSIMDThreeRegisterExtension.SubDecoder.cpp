module;

#include <unordered_map>
#include <utility>
#include <cstdint>
#include <vector>
#include <array>

module disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeRegisterExtension.SubDecoder;

import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Register;
import disxx.disasm.utility.bits;
import disxx.disasm.InstructionIdentifier;

namespace disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeRegisterExtension
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
        // +-+-+-+-----+----+-+--+-+------+-+--+--+
        // |0|Q|U|01110|size|0|Rm|1|opcode|1|Rn|Rd|
        // +-+-+-+-----+----+-+--+-+------+-+--+--+

        unsigned short int Q, U, size, Rm, opcode, Rn, Rd;
        Q = bits::extract<unsigned short int, std::uint32_t, 30, 30>(this->m_Insn);
        U = bits::extract<unsigned short int, std::uint32_t, 29, 29>(this->m_Insn);
        size = bits::extract<unsigned short int, std::uint32_t, 22, 23>(this->m_Insn);
        Rm = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        opcode = bits::extract<unsigned short int, std::uint32_t, 11, 14>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rd = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);

        std::unordered_map<unsigned short int, InstructionIdentifier> insnTable = {
            {0b00000010, InstructionIdentifier::ID_SDOT},
            {0b10000010, InstructionIdentifier::ID_SDOT},
            {0b00001110, InstructionIdentifier::ID_FCVTN},
            {0b10001110, InstructionIdentifier::ID_FCVTN2},
            {0b00001111, InstructionIdentifier::ID_FDOT},
            {0b10001111, InstructionIdentifier::ID_FDOT},
            {0b00011110, InstructionIdentifier::ID_FCVTN},
            {0b10011110, InstructionIdentifier::ID_FCVTN},
            {0b00011111, InstructionIdentifier::ID_FDOT},
            {0b10011111, InstructionIdentifier::ID_FDOT},
            {0b00100011, InstructionIdentifier::ID_USDOT},
            {0b10100011, InstructionIdentifier::ID_USDOT},
            {0b01000000, InstructionIdentifier::ID_SQRDMLAH},
            {0b11000000, InstructionIdentifier::ID_SQRDMLAH},
            {0b01000001, InstructionIdentifier::ID_SQRDMLSH},
            {0b11000001, InstructionIdentifier::ID_SQRDMLSH},
            {0b01000010, InstructionIdentifier::ID_UDOT},
            {0b11000010, InstructionIdentifier::ID_UDOT},
            {0b01001000, InstructionIdentifier::ID_FCMLA},
            {0b11001000, InstructionIdentifier::ID_FCMLA},
            {0b01001100, InstructionIdentifier::ID_FCADD},
            {0b11001100, InstructionIdentifier::ID_FCADD},
            {0b01011111, InstructionIdentifier::ID_BFDOT},
            {0b11011111, InstructionIdentifier::ID_BFDOT},
            {0b01111111, InstructionIdentifier::ID_BFMLALB},
            {0b11111111, InstructionIdentifier::ID_BFMLALT},
            {0b00001000, InstructionIdentifier::ID_FMLALLBB},
            {0b00011000, InstructionIdentifier::ID_FMLALLBT},
            {0b00111111, InstructionIdentifier::ID_FMLALB},
            {0b10001000, InstructionIdentifier::ID_FMLALLTB},
            {0b10011000, InstructionIdentifier::ID_FMLALLTT},
            {0b10100100, InstructionIdentifier::ID_SMMLA},
            {0b10100101, InstructionIdentifier::ID_USMMLA},
            {0b10111111, InstructionIdentifier::ID_FMLALT},
            {0b11001101, InstructionIdentifier::ID_FMMLA},
            {0b11011101, InstructionIdentifier::ID_BFMMLA},
            {0b11100100, InstructionIdentifier::ID_UMMLA},
            {0b11101101, InstructionIdentifier::ID_FMMLA}
        };

        unsigned short int encoding = (Q << 7) | (U << 6) | (size << 4) | opcode;
        if (opcode <= 0b0010)
            encoding &= ~(0b11 << 4);

        if (U == 0b1 && (opcode >> 2) == 0b10)
        {
            encoding &= ~0b11;
            encoding &= ~(0b11 << 4);
        }
        else if (U == 0b1 && (opcode & ~(0b1 << 1)) == 0b1100)
        {
            encoding &= ~(0b1 << 1);
            encoding &= ~(0b11 << 4);
        }

        const auto it{insnTable.find(encoding)};
        if (it == insnTable.end()) [[unlikely]]
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
    
        if (opcode == 0b1110)
        {
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{Q});
            
            const disxx::disasm::operand::VectorArrangementSpecifier Tb{static_cast<unsigned short int>(size == 0b00 ? 0b101 : 0b010 | Q)};
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())->SetVectorArrangementSpecifier(Tb);
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())->SetVectorArrangementSpecifier(Tb);

            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (U == 0b0 && size <= 0b01 && opcode == 0b1111)
        {
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())->SetVectorArrangementSpecifier
            (
				disxx::disasm::operand::VectorArrangementSpecifier
				{
                	[&size, &Q](void) -> unsigned short int
                	{
               	    	if (size == 0b00)
               	        	return 0b100 | Q;
                    	return 0b010 | Q;
                	}()
				}
            );

            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{Q});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{Q});

            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if ((opcode >> 2) == 0b01 || opcode == 0b0010 || opcode == 0b0011)
        {
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(0b100 | Q)});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{Q});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{Q});
            
            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (U == 0b1 && opcode <= 0b0001)
        {
			const auto bits{static_cast<unsigned short int>((size << 1) | Q)};
			if (bits < 0b010 || bits > 0b101) [[unlikely]]
				return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

            for (auto &pReg : this->m_Operands)
                static_cast<disxx::disasm::operand::Register *>(pReg.get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{bits});

            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (U == 0b1 && (((opcode >> 2) == 0b10) || ((opcode & ~(0b1 << 1)) == 0b1100)))
        {
			const auto bits{static_cast<unsigned short int>((size << 1) | Q)};
			if (bits < 0b010) [[unlikely]]
				return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};

            for (auto &pReg : this->m_Operands)
                static_cast<disxx::disasm::operand::Register *>(pReg.get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{bits});

            // rot
            this->m_Operands.emplace_back
            (
                std::make_unique<disxx::disasm::operand::Immediate<unsigned short int, 16>>
                (
                    (opcode >> 2) == 0b10
                        ? std::array<unsigned short int, 4>{0, 90, 180, 270}.at(opcode & ~(0b11 << 2))
                        : (bits::extract<unsigned short int, unsigned short int, 1, 1>(opcode) ? 270 : 90)
                )
            );
        }
        else if (U == 0b1 && (size == 0b01 || size == 0b11) && (opcode == 0b1101))
        {
            if (size == 0b01)
            {
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
                    ->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(0b100 | Q)});
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
                    ->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(0b010 | Q)});
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
                    ->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{static_cast<unsigned short int>(0b010 | Q)});

                return std::make_pair(it->second, std::move(this->m_Operands));
            }

            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b101});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b011});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b011});
                
            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (opcode == 0b1000)
        {
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b101});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b001});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b001});
        
            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (size == 0b11 && opcode == 0b1111)
        {
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b011});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b001});
            static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
				->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b001});
        
            return std::make_pair(it->second, std::move(this->m_Operands));
        }
        else if (opcode == 0b1101)
        {
            if (size == 0b00)
            {
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b010});
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b001});
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b101});
        
                return std::make_pair(it->second, std::move(this->m_Operands));
            }
            else
            {
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(0).get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b101});
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(1).get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b001});
                static_cast<disxx::disasm::operand::Register *>(this->m_Operands.at(2).get())
					->SetVectorArrangementSpecifier(disxx::disasm::operand::VectorArrangementSpecifier{0b001});
        
                return std::make_pair(it->second, std::move(this->m_Operands));
            }
        }
        
        return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}}; // Can't define instruction's type
	}
} /* disxx::disasm::decoder::DataProcessingScalarFPAndAdvancedSIMD::AdvancedSIMDThreeRegisterExtension */
