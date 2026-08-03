module;

#include <disconf.hpp>

export module disxx.disasm.operand.IOperand;

export import disxx.utility.trait.Cloneable;

export namespace disxx::disasm::operand
{
    class [[clang::type_visibility("default")]] [[nodiscard]] IOperand : public disxx::utility::trait::Cloneable<IOperand>
    {
      public:
		explicit IOperand(void) noexcept = default;

		IOperand(const IOperand &) noexcept = default;
		IOperand &operator=(const IOperand &) noexcept = default;

		virtual ~IOperand(void) noexcept override = default;
	};
} /* operand */
