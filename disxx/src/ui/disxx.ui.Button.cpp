module disxx.ui.Button;

import disxx.ui.backend.opengl.Renderer;
import disxx.ui.backend.glut.Context;
import disxx.ui.renderable.Rectangle;
import disxx.ui.renderable.Text;
import disxx.ui.utility.Vec;

namespace disxx::ui
{
	Button::Button(void) noexcept
		: Widget{}
		, m_Callback{[](const Widget *const) -> void {}}
		, m_Text{}
		, m_Trigger{Trigger::BTN_NONE}
	{}

	Button::Button(float x, float y, float width, float height) noexcept
		: Widget{x, y, width, height}
		, m_Callback{[](const Widget *const) -> void {}}
		, m_Text{}
		, m_Trigger{Trigger::BTN_NONE}
	{}

	Button::Button(const Button &other) noexcept
		: Widget{other}
		, m_Callback{other.m_Callback}
		, m_Text{other.m_Text}
		, m_Trigger{other.m_Trigger}
	{}

	Button &Button::operator=(const Button &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(other);
			this->m_Callback = other.m_Callback;
			this->m_Text = other.m_Text;
			this->m_Trigger = other.m_Trigger;
		}

		return *this;
	}

	Button::Button(Button &&other) noexcept
		: Widget{std::forward<Button &&>(other)}
		, m_Callback{std::move(other.m_Callback)}
		, m_Text{std::move(other.m_Text)}
		, m_Trigger{std::move(other.m_Trigger)}
	{}

	Button &Button::operator=(Button &&other) noexcept
	{
		Widget::operator=(std::forward<Button &&>(other));
		this->m_Callback = std::move(other.m_Callback);
		this->m_Text = std::move(other.m_Text);
		this->m_Trigger = std::move(other.m_Trigger);

		return *this;
	}

	std::unique_ptr<Widget> Button::Clone(void) const noexcept
	{ return std::make_unique<std::decay<decltype(*this)>::type>(*this); }

	void Button::Render(void) const noexcept
	{
		if (!this->m_bVisible)
			return;

		// Add a frame
		renderable::Rectangle frame{};
		frame.Replace(utility::Vec2<float>{this->m_Position.x - 1.f, this->m_Position.y - 1.f});
		frame.Resize(utility::Vec2<float>{this->m_Size.x + 2.f, this->m_Size.y + 2.f});
		frame.SetColor(utility::Vec3<float>{0.f, 0.f, 0.f});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(frame));

		// Add the button itself
		renderable::Rectangle btn{};
		btn.Replace(utility::Vec2<float>{this->m_Position.x, this->m_Position.y});
		btn.Resize(utility::Vec2<float>{this->m_Size.x, this->m_Size.y});
		btn.SetColor(utility::Vec3<float>{this->m_pColor[0], this->m_pColor[1], this->m_pColor[2]});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(btn));
		
		// Add a text
        if (!this->m_Text.empty())
        {
			renderable::Text txt{};
			txt.Replace
			(
            	utility::Vec2<float>
				{
					this->m_Position.x + (this->m_Size.x - (9.f * this->m_Text.size())) / 2.0f, 
            		this->m_Position.y + this->m_Size.y / 3.0f - 4.5f
				}
			);
			txt.SetColor(utility::Vec3<float>{1.f, 1.f, 1.f});
			txt.SetText(this->m_Text);
			s_pRenderer->Push(std::make_unique<renderable::Text>(txt));
        }

		s_pRenderer->Render();
	}

	void Button::MouseButtonCallback(backend::event::MouseButton event) noexcept
	{
		const auto [x, y]{event.GetPosition()};
		if (!(x >= this->m_Position.x && x <= this->m_Position.x + this->m_Size.x && y >= this->m_Position.y && y <= this->m_Position.y + this->m_Size.y))
			return;

		if (const auto button{event.GetButton()}, state{event.GetState()}; button == 0 && state == 0)
			this->m_bClicked = true;
		else if (button == 0 && state == 1)
			this->m_bClicked = false;

		if (this->m_bClicked && this->m_Trigger == Trigger::BTN_CLICKED)
			this->m_Callback(this);
	}

	void Button::MouseMotionCallback(backend::event::MouseMotion event) noexcept
	{
		if (event.Passive())
			return;

		const auto [x, y]{event.GetPosition()};
		this->m_bHovered = (x >= this->m_Position.x && x <= this->m_Position.x + this->m_Size.x && y >= this->m_Position.y && y <= this->m_Position.y + this->m_Size.y);
		if (this->m_bHovered && this->m_Trigger == Trigger::BTN_HOVERED)
			this->m_Callback(this);
	}
} /* disxx::ui */
