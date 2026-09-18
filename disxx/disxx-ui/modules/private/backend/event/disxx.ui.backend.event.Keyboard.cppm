export module disxx.ui.backend.event.Keyboard;

export import disxx.ui.utility.Vec;

export namespace disxx::ui::backend::event
{
	class __attribute__((visibility("hidden"))) [[nodiscard]] Keyboard
	{
	  private:
		unsigned char m_Key{};
	
	  public:
		explicit Keyboard(void) noexcept = default;
		explicit Keyboard(unsigned char) noexcept;

		Keyboard(const Keyboard &) noexcept = default;
		Keyboard &operator=(const Keyboard &) noexcept = default;

		inline unsigned char GetKey(void) const noexcept;
	};

	inline unsigned char Keyboard::GetKey(void) const noexcept { return this->m_Key; }
} /* disxx::ui::backend::event */
