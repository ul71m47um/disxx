module;

#include <disconf.hpp>

#include <string_view>
#include <type_traits>
#include <flat_map>
#include <concepts>
#include <variant>

export module disxx.disasm.Printer;

export import disxx.disasm.Instruction;
import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.disasm.operand.PrefetchOperand;
import disxx.disasm.operand.SystemOperand;
import disxx.disasm.operand.MemoryBarrier;
import disxx.disasm.operand.Immediate;
import disxx.disasm.operand.Extension;
import disxx.disasm.operand.Condition;
import disxx.disasm.operand.PState;
import disxx.disasm.operand.Shift;
import disxx.disasm.operand.IOperand;

export import <memory>;

export namespace disxx::disasm
{
	template <std::output_iterator<char> T>
	class __DISXX_EXPORT__ [[nodiscard]] Printer
	{
	  private:
		static const std::flat_map<InstructionID, std::string_view> s_InstructionTable;

		static const std::flat_map<operand::PrefetchOperand::Identifier, std::string_view> s_PrefetchOperandTable;
		static const std::flat_map<operand::SystemOperand::Identifier, std::string_view> s_SystemOperandTable;
		static const std::flat_map<operand::MemoryBarrier::Identifier, std::string_view> s_MemoryBarrierTable;
		static const std::flat_map<operand::Condition::Identifier, std::string_view> s_ConditionTable;
		static const std::flat_map<operand::Extension::Identifier, std::string_view> s_ExtensionTable;
	 	static const std::flat_map<operand::Register::Identifier, std::string_view> s_RegisterTable;
		static const std::flat_map<operand::PState::Identifier, std::string_view> s_PStateTable;
		static const std::flat_map<operand::Shift::Identifier, std::string_view> s_ShiftTable;
 
	  private:
		std::shared_ptr<T> m_pIt;

	  private:
		void Print(const std::unique_ptr<operand::IOperand> &, bool) noexcept;

	  public:
		explicit Printer(void) noexcept = default;
		explicit Printer([[clang::lifetimebound]] const std::shared_ptr<T> &) noexcept;

		Printer(const Printer &) noexcept(std::is_nothrow_copy_constructible<T>::value)
			requires(std::is_copy_constructible<T>::value) = default;
		Printer(const Printer &) noexcept(std::is_nothrow_copy_constructible<T>::value)
			requires(!std::is_copy_constructible<T>::value) = delete;
		Printer &operator=(const Printer &) noexcept(std::is_nothrow_copy_assignable<T>::value)
			requires(std::is_copy_assignable<T>::value) = default;
		Printer &operator=(const Printer &) noexcept(std::is_nothrow_copy_assignable<T>::value)
			requires(!std::is_copy_assignable<T>::value) = delete;

		void Print(const Instruction &) noexcept;
	};

	template <std::output_iterator<char> T>
	Printer<T>::Printer([[clang::lifetimebound]] const std::shared_ptr<T> &ptr) noexcept
		: m_pIt{ptr}
	{}

	template <std::output_iterator<char> T>
	void Printer<T>::Print(const std::unique_ptr<operand::IOperand> &ptr, bool last) noexcept
	{
		if (const auto *pLoadsAndStoresAddress{dynamic_cast<operand::LoadsAndStoresAddress *>(ptr.get())})
		{
			**this->m_pIt++ = '[';

			const auto offset{pLoadsAndStoresAddress->GetPreIndexedOffset()};	
			const auto modifier{pLoadsAndStoresAddress->GetModifier()};
			this->Print(pLoadsAndStoresAddress->GetRegister(), !modifier || !offset);
			if (offset)
			{
				std::visit
				(
					*offset,
					[this](auto &&opr) -> void
					{
						if constexpr (std::is_same<decltype(opr), operand::Register>::value)
						{
							const auto pRegister{std::make_unique<operand::Register>(opr)};
							this->Print(pRegister, true);

							**this->m_pIt++ = ']';
						}
						else
						{
							const auto pImmediate{std::make_unique<typename std::decay<decltype(opr)>::type>(opr.first)};
							this->Print(pImmediate, true);

							**this->m_pIt++ = ']';
							if (opr.second == operand::LoadsAndStoresAddress::PreIndexedOffsetKind::IDX_ACCUMULATIVE)
								**this->m_pIt++ = '!';
						}
					}
				);
			}
			else if (modifier)
				this->Print(*modifier, true);
		}
		else if (const auto *pPrefetchOperand{dynamic_cast<operand::PrefetchOperand *>(ptr.get())})
			for (const auto ch : s_PrefetchOperandTable.at(pPrefetchOperand->GetIdentifier()))
				**this->m_pIt++ = ch;
		else if (const auto *pSystemOperand{dynamic_cast<operand::SystemOperand *>(ptr.get())})
			for (const auto ch : s_SystemOperandTable.at(pSystemOperand->GetIdentifier()))
				**this->m_pIt++ = ch;
		else if (const auto *pMemoryBarrier{dynamic_cast<operand::MemoryBarrier *>(ptr.get())})
			for (const auto ch : s_MemoryBarrierTable.at(pMemoryBarrier->GetIdentifier()))
				**this->m_pIt++ = ch;
		else if (const auto *pCondition{dynamic_cast<operand::Condition *>(ptr.get())})
			for (const auto ch : std::format(".{}", s_ConditionTable.at(pCondition->GetIdentifier())))
				**this->m_pIt++ = ch;
		else if (const auto *pExtension{dynamic_cast<operand::Extension *>(ptr.get())})
			for (const auto ch : std::format("{} #{:#x}", s_ExtensionTable.at(pExtension->GetIdentifier()), pExtension->GetValue()))
				**this->m_pIt++ = ch;
		else if (const auto *pRegister{dynamic_cast<operand::Register *>(ptr.get())})
			for (const auto ch : s_RegisterTable.at(pRegister->GetIdentifier()))
				**this->m_pIt++ = ch;
		else if (const auto *pPState{dynamic_cast<operand::PState *>(ptr.get())})
			for (const auto ch : s_PStateTable.at(pPState->GetIdentifier()))
				**this->m_pIt++ = ch;
		else if (const auto *pShift{dynamic_cast<operand::Shift *>(ptr.get())})
			for (const auto ch : std::format("{} #{:#x}", s_ShiftTable.at(pShift->GetIdentifier()), pShift->GetAmount()))
				**this->m_pIt++ = ch;
		
		if (!last)
			for (const auto ch : ", ")
				**this->m_pIt++ = ch;
	}

	template <std::output_iterator<char> T>
	void Printer<T>::Print(const Instruction &insn) noexcept
	{
		if (const auto id{insn.GetIdentifier()}; !s_InstructionTable.contains(id)) [[unlikely]]
		{
			for (const auto ch : std::format(".long {}", insn.GetBytes()))
				**this->m_pIt++ = ch;
			return;
		}

		for (const auto ch : std::format("{} ", s_InstructionTable.at(insn.GetIdentifier())))
			**this->m_pIt++ = ch;

		for (const auto &ptr : insn.GetOperands())
			this->Print(ptr, ptr == *insn.GetOperands().rbegin());
	}
} /* disxx::disasm */
