export module disxx.disasm.operand.LoadsAndStoresAddress;

import disxx.disasm.operand.IOperand;

export import disxx.disasm.operand.Immediate;
export import disxx.disasm.operand.Extension;
export import disxx.disasm.operand.Register;
export import disxx.disasm.operand.Shift;

export import std;

export namespace disxx::disasm::operand
{
	class [[clang::type_visibility("default")]] LoadsAndStoresAddress final : public IOperand
	{
	  public:
		using ImmediatePreIndexedOffset = std::variant
		<
			Immediate<signed short int, 7>,
			Immediate<signed short int, 9>,
			Immediate<signed short int, 10>,
			Immediate<unsigned short int, 12>
		>;

	  public:
		enum class PreIndexedOffsetKind : bool
		{
			IDX_REGULAR,
			IDX_ACCUMULATIVE
		};

	  private:
		std::optional
		<
			std::variant
			<
				Extension,
				Shift
			>
		> m_Modifier{};
		std::optional
		<
			std::variant
			<
				Register,
				std::pair
				<
					ImmediatePreIndexedOffset,
					PreIndexedOffsetKind
				>
			>
		> m_PreIndexedOffset{};
		Register m_BaseRegister{};

	  public:
		explicit LoadsAndStoresAddress(void) noexcept;
		explicit LoadsAndStoresAddress(Register &&) noexcept;
		
		LoadsAndStoresAddress(const LoadsAndStoresAddress &) noexcept;
		LoadsAndStoresAddress &operator=(const LoadsAndStoresAddress &) noexcept;

		LoadsAndStoresAddress(LoadsAndStoresAddress &&) noexcept;
		LoadsAndStoresAddress &operator=(LoadsAndStoresAddress &&) noexcept;

        virtual std::unique_ptr<IOperand> Clone(void) const noexcept override;

		inline void AddImmediatePreIndexedOffset(const ImmediatePreIndexedOffset, const PreIndexedOffsetKind) noexcept;
		inline void AddRegisterOffset(Register &&) noexcept;

		inline void AddExtension(Extension &&) noexcept;
		inline void AddShift(Shift &&) noexcept;

		inline const Register &GetRegister(void) const noexcept;
		inline std::optional
		<
			std::variant
			<
				Register,
				std::pair
				<
					ImmediatePreIndexedOffset,
					PreIndexedOffsetKind
				>
			>
		> GetPreIndexedOffset(void) const noexcept;
		inline std::optional
		<
			std::variant
			<
				Extension,
				Shift
			>
		> GetModifier(void) const noexcept;
	};

	inline void LoadsAndStoresAddress::AddImmediatePreIndexedOffset(const ImmediatePreIndexedOffset offset, const PreIndexedOffsetKind kind) noexcept
	{
		this->m_PreIndexedOffset.emplace
		(
			std::in_place_type
			<
				std::pair
				<
					ImmediatePreIndexedOffset,
					PreIndexedOffsetKind
				>
			>,
			std::make_pair(offset, kind)
		);
	}

	inline void LoadsAndStoresAddress::AddRegisterOffset(Register &&reg) noexcept
	{
		this->m_PreIndexedOffset.emplace
		(
			std::in_place_type<Register>,
			std::forward<Register &&>(reg)
		);
	}

	inline void LoadsAndStoresAddress::AddExtension(Extension &&extension) noexcept
	{
		this->m_Modifier.emplace
		(
			std::in_place_type<Extension>,
			std::forward<Extension &&>(extension)
		);
	}

	inline void LoadsAndStoresAddress::AddShift(Shift &&shift) noexcept
	{
		this->m_Modifier.emplace
		(
			std::in_place_type<Shift>,
			std::forward<Shift &&>(shift)
		);
	}

	inline const Register &LoadsAndStoresAddress::GetRegister(void) const noexcept
	{ return this->m_BaseRegister; }

	inline std::optional
	<
		std::variant
		<
			Register,
			std::pair
			<
				LoadsAndStoresAddress::ImmediatePreIndexedOffset,
				LoadsAndStoresAddress::PreIndexedOffsetKind
			>
		>
	> LoadsAndStoresAddress::GetPreIndexedOffset(void) const noexcept
	{ return this->m_PreIndexedOffset; }

	inline std::optional
	<
		std::variant
		<
			Extension,
			Shift
		>
	> LoadsAndStoresAddress::GetModifier(void) const noexcept
	{ return this->m_Modifier; }
} /* disxx::disasm::operand */
