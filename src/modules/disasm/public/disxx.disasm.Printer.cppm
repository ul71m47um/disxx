module;

#include <disconf.hpp>

#include <type_traits>
#include <flat_map>
#include <concepts>

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

	  public:
		explicit Printer(void) noexcept = default;
		explicit Printer(std::shared_ptr<T> &) noexcept;

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
	Printer<T>::Printer(std::shared_ptr<T> &ptr) noexcept
		: m_pIt{ptr}
	{}

	template <std::output_iterator<char> T>
	void Printer<T>::Print(const Instruction &insn) noexcept
	{
		if (const auto id{insn.GetIdentifier()}; !s_InstructionTable.contains(id)) [[unlikely]]
		{
			for (const auto ch : std::format(".long {}", insn.GetBytes()))
				**this->m_pIt++ = ch;
			return;
		}
	}
} /* disxx::disasm */
