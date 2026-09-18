export module disxx.ui.backend.event.MouseButton;

export import disxx.ui.utility.Vec;

export namespace disxx::ui::backend::event
{
	class __attribute__((visibility("hidden"))) [[nodiscard]] MouseButton
	{
	  private:
		utility::Vec2<float> m_Position{};
		int m_Button{}, m_State{};
	
	  public:
		explicit MouseButton(void) noexcept = default;
		explicit MouseButton(utility::Vec2<float>, int, int) noexcept;

		MouseButton(const MouseButton &) noexcept = default;
		MouseButton &operator=(const MouseButton &) noexcept = default;

		inline utility::Vec2<float> GetPosition(void) const noexcept;
		inline int GetButton(void) const noexcept;
		inline int GetState(void) const noexcept;
	};

	inline utility::Vec2<float> MouseButton::GetPosition(void) const noexcept { return this->m_Position; }
	inline int MouseButton::GetButton(void) const noexcept { return this->m_Button; }
	inline int MouseButton::GetState(void) const noexcept { return this->m_State; }
} /* disxx::ui::backend::event */
