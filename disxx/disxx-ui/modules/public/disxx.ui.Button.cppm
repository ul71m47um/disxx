export module disxx.ui.Button;

import disxx.ui.Widget;

export import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] Button : public Widget
	{
	  public:
		enum class Trigger
		{
			BTN_NONE,
			BTN_CLICKED,
			BTN_HOVERED
		};

	  protected:
		std::function<void(const Widget *const)> m_Callback{};
		std::string m_Text{};
		Trigger m_Trigger{};

	  public:
		explicit Button(void) noexcept;
        explicit Button(float, float, float, float) noexcept;
        
		Button(const Button &) noexcept;
        Button &operator=(const Button &) noexcept;

		Button(Button &&) noexcept;
		Button &operator=(Button &&) noexcept;

		virtual ~Button(void) noexcept override = default;

		inline void SetCallback(const Trigger, std::function<void(const Widget *const)>) noexcept;
		virtual void SetText(std::string_view) noexcept;	

		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;

		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void MouseMotionCallback(backend::event::MouseMotion) noexcept override;
		virtual void Render(void) const noexcept override;
	};

	inline void Button::SetCallback(const Trigger trigger, std::function<void(const Widget *const)> callback) noexcept
	{
		if (trigger != Trigger::BTN_NONE)
		{
			this->m_Callback = callback;
			this->m_Trigger = trigger;
		}
		else
		{
			// Don't touch the callback here!
			// It won't be used anyway...
			this->m_Trigger = Trigger::BTN_NONE;
		}
	}	
} /* disxx::ui */
