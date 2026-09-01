export module disxx.ui.backend.event.MouseMotion;

export import disxx.ui.utility.Vec;

export namespace disxx::ui::backend::event
{
	class __attribute__((visibility("hidden"))) [[nodiscard]] MouseMotion
	{
	  private:
		utility::Vec2<float> m_Position{};
		bool m_bPassive{};
	
	  public:
		explicit MouseMotion(void) noexcept = default;
		explicit MouseMotion(utility::Vec2<float>, bool) noexcept;

		MouseMotion(const MouseMotion &) noexcept = default;
		MouseMotion &operator=(const MouseMotion &) noexcept = default;

		inline utility::Vec2<float> GetPosition(void) const noexcept;
		inline bool GetPassive(void) const noexcept;
	};

	inline utility::Vec2<float> MouseMotion::GetPosition(void) const noexcept { return this->m_Position; }
	inline bool MouseMotion::GetPassive(void) const noexcept { return this->m_bPassive; }
} /* disxx::ui::backend::event */
