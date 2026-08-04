export module disxx.disasm.operand.Extension;

import disxx.disasm.operand.IOperand;

import std;

export namespace disxx::disasm::operand
{
	class [[clang::type_visibility("default")]] Extension final : public IOperand
	{
	  public:
		enum class Identifier : unsigned short int
		{
			ID_UXTB, ID_UXTH,
			ID_UXTW, ID_UXTX,
			ID_SXTB, ID_SXTH,
			ID_SXTW, ID_SXTX
		};

	  private:
		Identifier m_Identifier{};
		unsigned short int m_Value{};

	  public:
		explicit Extension(void) noexcept;
		explicit Extension(unsigned short int, unsigned short int) noexcept;

		Extension(const Extension &) noexcept;
		Extension &operator=(const Extension &) noexcept;

		Extension(Extension &&) noexcept;
		Extension &operator=(Extension &&) noexcept;
 
        virtual std::unique_ptr<IOperand> Clone(void) const noexcept override;
	
		inline Identifier GetIdentifier(void) const noexcept;
		inline unsigned short int GetValue(void) const noexcept;
	};

	inline Extension::Identifier Extension::GetIdentifier(void) const noexcept
	{ return this->m_Identifier; }

	inline unsigned short int Extension::GetValue(void) const noexcept
	{ return this->m_Value; }
} /* disxx::disasm::operand */
