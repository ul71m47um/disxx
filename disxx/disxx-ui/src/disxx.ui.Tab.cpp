module disxx.ui.Tab;

import disxx.ui.renderable.Rectangle;
import disxx.ui.renderable.Text;

namespace disxx::ui
{
	Tab::Tab(void) noexcept
		: Widget{}
		, m_pWidget{}
		, m_Text{}
	{}

	Tab::Tab(float x, float y, float width, float height) noexcept
		: Widget{x, y, width, height}
		, m_pWidget{}
		, m_Text{}
	{}

	Tab::Tab(const Tab &other) noexcept
		: Widget{other}
		, m_pWidget{other.m_pWidget ? other.m_pWidget->Clone() : nullptr}
		, m_Text{other.m_Text}
	{}

	Tab &Tab::operator=(const Tab &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(other);
			if (this->m_pWidget)
				this->m_pWidget.reset();
			if (other.m_pWidget)
				this->m_pWidget = other.m_pWidget->Clone();
			this->m_Text = other.m_Text;
		}

		return *this;
	}

	Tab::Tab(Tab &&other) noexcept
		: Widget{std::forward<Tab &&>(other)}
		, m_pWidget{std::move(other.m_pWidget)}
		, m_Text{std::move(other.m_Text)}
	{}

	Tab &Tab::operator=(Tab &&other) noexcept
	{
		Widget::operator=(std::forward<Tab &&>(other));
		if (this->m_pWidget)
			this->m_pWidget.reset();
		this->m_pWidget = std::move(other.m_pWidget);
		this->m_Text = std::move(other.m_Text);
		
		return *this;
	}

	std::unique_ptr<Widget> Tab::Clone(void) const noexcept
	{ return std::make_unique<std::decay<decltype(*this)>::type>(*this); }

	void Tab::Render(void) const noexcept
	{
		if (!this->m_bVisible)
			return;

		float heightModifier{this->m_bClicked ? 5.f : 0.f};

		// Add a frame
		renderable::Rectangle frame{};
		frame.Replace(utility::Vec2<float>{this->m_Position.x - 1.f, this->m_Position.y});
		frame.Resize(utility::Vec2<float>{this->m_Size.x + 2.f, this->m_Size.y + 1.f + heightModifier});
		frame.SetColor(utility::Vec3<float>{0.f, 0.f, 0.f});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(frame));

		// Add the tab itself
		renderable::Rectangle tab{};
		tab.Replace(utility::Vec2<float>{this->m_Position.x, this->m_Position.y});
		tab.Resize(utility::Vec2<float>{this->m_Size.x, this->m_Size.y + heightModifier});
		tab.SetColor(utility::Vec3<float>{this->m_pColor[0], this->m_pColor[1], this->m_pColor[2]});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(tab));
		
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

	void Tab::MouseButtonCallback(backend::event::MouseButton event) noexcept
	{
		if (this->m_pWidget)
			this->m_pWidget->MouseButtonCallback(event);

		const auto [x, y]{event.GetPosition()};
		if (!(x >= this->m_Position.x && x <= this->m_Position.x + this->m_Size.x && y >= this->m_Position.y && y <= this->m_Position.y + this->m_Size.y))
			return;

		if (!this->m_bClicked && event.GetButton() == 0 && event.GetState() == 0)
			this->m_bClicked = true;
	}

	void Tab::MouseMotionCallback(backend::event::MouseMotion event) noexcept
	{
		if (this->m_pWidget)
			this->m_pWidget->MouseMotionCallback(event);
	}
} /* disxx::ui */
