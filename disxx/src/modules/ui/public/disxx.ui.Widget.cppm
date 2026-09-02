export module disxx.ui.Widget;

export import disxx.ui.backend.event.MouseMotion;
export import disxx.ui.backend.event.MouseMotion;
export import disxx.ui.backend.event.MouseButton;
export import disxx.ui.backend.event.Keyboard;
export import disxx.ui.backend.event.Reshape;
export import disxx.ui.utility.Vec;

import disxx.ui.backend.abstract.IRenderer;
import disxx.utility.trait.Cloneable;
import disxx.utility.pointer.NonNull;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] Widget : public disxx::utility::trait::Cloneable<Widget>
	{
	  protected:
		static disxx::utility::pointer::NonNull<backend::abstract::IRenderer> s_pRenderer;

	  protected:
		utility::Vec2<float> m_Position{};
		utility::Vec2<float> m_Size{};
		float m_pColor[3]{};
		bool m_bVisible{}, m_bClicked{}, m_bHovered{};

	  public:
		static void ClearBuffer(void) noexcept;
		static void SwapBuffers(void) noexcept;
		static void Redisplay(void) noexcept;
	
	  public:
		explicit Widget(void) noexcept;
		explicit Widget(float, float, float, float) noexcept;
		Widget(const Widget &) noexcept;
		Widget &operator=(const Widget &) noexcept;

		virtual ~Widget(void) noexcept override = default;

		inline utility::Vec2<float> GetPosition(void) const noexcept;
		inline utility::Vec2<float> GetSize(void) const noexcept;
	
		virtual void Replace(utility::Vec2<float>) noexcept;
		virtual void Resize(utility::Vec2<float>) noexcept;
		
		inline void SetColor(float, float, float) noexcept;
		inline void SetVisible(bool) noexcept;
	
		inline bool Visible(void) const noexcept;
		inline bool Clicked(void) const noexcept;
		inline bool Hovered(void) const noexcept;

		virtual void MouseMotionCallback(backend::event::MouseMotion) noexcept;
		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept;
		virtual void KeyboardCallback(backend::event::Keyboard) noexcept;
		virtual void Render(void) const noexcept = 0;
	};

	inline void Widget::SetColor(float r, float g, float b) noexcept
	{
		this->m_pColor[0] = r;
		this->m_pColor[1] = g;
		this->m_pColor[2] = b;
	}

	inline bool Widget::Visible(void) const noexcept
	{ return this->m_bVisible; }

	inline utility::Vec2<float> Widget::GetPosition(void) const noexcept
	{ return utility::Vec2<float>{this->m_Position}; }

	inline utility::Vec2<float> Widget::GetSize(void) const noexcept
	{ return utility::Vec2<float>{this->m_Size}; }

	inline void Widget::SetVisible(bool bVisible) noexcept
	{ this->m_bVisible = bVisible; }

	inline bool Widget::Clicked(void) const noexcept
	{ return this->m_bClicked; }

	inline bool Widget::Hovered(void) const noexcept
	{ return this->m_bHovered; }
} /* disxx::ui */
