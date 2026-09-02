module disxx.ui.TabbedPane;

import disxx.ui.renderable.Rectangle;
import disxx.ui.renderable.Text;

namespace disxx::ui
{
	TabbedPane::TabbedPane(void) noexcept
		: Widget{}
		, m_Tabs{}
		, m_Callback{[](Tab &_) -> void {}}
	{}

	TabbedPane::TabbedPane(float x, float y, float width, float height) noexcept
		: Widget{x, y, width, height}
		, m_Tabs{}
		, m_Callback{[](Tab &_) -> void {}}
	{}

	TabbedPane::TabbedPane(const TabbedPane &other) noexcept
		: Widget{other}
		, m_Tabs{other.m_Tabs}
		, m_Callback{other.m_Callback}
	{}

	TabbedPane &TabbedPane::operator=(const TabbedPane &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(other);
			this->m_Tabs = other.m_Tabs;
			this->m_Callback = other.m_Callback;
		}

		return *this;
	}

	TabbedPane::TabbedPane(TabbedPane &&other) noexcept
		: Widget{std::forward<TabbedPane &&>(other)}
		, m_Tabs{std::move(other.m_Tabs)}
		, m_Callback{std::move(other.m_Callback)}
	{}

	TabbedPane &TabbedPane::operator=(TabbedPane &&other) noexcept
	{
		Widget::operator=(std::forward<TabbedPane &&>(other));
		this->m_Tabs = std::move(other.m_Tabs);
		this->m_Callback = std::move(other.m_Callback);
		
		return *this;
	}

	std::unique_ptr<Widget> TabbedPane::Clone(void) const noexcept
	{ return std::make_unique<std::decay<decltype(*this)>::type>(*this); }

	void TabbedPane::Render(void) const noexcept
	{
		if (!this->m_bVisible)
			return;

		// Add a subframe
		renderable::Rectangle subframe{};
		subframe.Replace(utility::Vec2<float>{this->m_Position.x - 1.f, this->m_Position.y - 1.f});
		subframe.Resize(utility::Vec2<float>{this->m_Size.x + 2.f, this->m_Size.y + 2.f});
		subframe.SetColor(utility::Vec3<float>{0.f, 0.f, 0.f});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(subframe));

		// Add the frame itself
		renderable::Rectangle frame{};
		frame.Replace(utility::Vec2<float>{this->m_Position.x, this->m_Position.y});
		frame.Resize(utility::Vec2<float>{this->m_Size.x, this->m_Size.y});
		frame.SetColor(utility::Vec3<float>{this->m_pColor[0], this->m_pColor[1], this->m_pColor[2]});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(frame));

		for (const auto &tab : this->m_Tabs)
		{
			tab.Render();
			if (tab.Clicked())
				tab.GetTextArea().Render();
		}
	}

	void TabbedPane::MouseButtonCallback(backend::event::MouseButton event) noexcept
	{
		const auto [x, y]{event.GetPosition()};
		if (!(x >= this->m_Position.x && x <= this->m_Position.x + this->m_Size.x && y >= this->m_Position.y && y <= this->m_Position.y + this->m_Size.y))
			return;

		for (auto &tab : this->m_Tabs)
		{
			const auto [tabX, tabY]{tab.GetPosition()};
			const auto [tabWidth, tabHeight]{tab.GetSize()};
			const auto cond{x >= tabX && x <= tabX + tabWidth && y >= tabY && y <= tabY + tabHeight};
			if (const auto button{event.GetButton()}, state{event.GetState()}; button == 0 && state == 0 && cond && tab.Clicked())
				tab.SetPassive();
			else if (button == 0 && state == 0 && cond)
			{
				for (auto &other : this->m_Tabs)
					other.SetPassive();
				tab.MouseButtonCallback(event);
				this->m_Callback(tab);
			}
			else if (cond || tab.Clicked())
			{
				tab.MouseButtonCallback(event);
				this->m_Callback(tab);
			}
		}
	}

	void TabbedPane::MouseMotionCallback(backend::event::MouseMotion event) noexcept
	{
		for (auto &tab : this->m_Tabs)
			if (tab.Clicked())
				tab.GetTextArea().MouseMotionCallback(event);
	}
} /* disxx::ui */
