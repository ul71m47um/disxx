module disxx.ui.MenuBar;

import disxx.ui.backend.GLUTContext;
import disxx.ui.renderable.Rectangle;
import disxx.ui.utility.Vec;

namespace disxx::ui
{
	MenuBar::MenuBar(void) noexcept
		: Widget
		{
			0.f,
			backend::GLUTContext::GetWindowSize().y * 0.97f,
			backend::GLUTContext::GetWindowSize().x,
			backend::GLUTContext::GetWindowSize().y * 0.03f
		}
		, m_Menus{}
	{}

	MenuBar::MenuBar(const MenuBar &other) noexcept
		: Widget{other}
		, m_Menus{other.m_Menus}
	{}

	MenuBar &MenuBar::operator=(const MenuBar &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(other);
			this->m_Menus = other.m_Menus;
		}

		return *this;
	}

	MenuBar::MenuBar(MenuBar &&other) noexcept
		: Widget{std::forward<MenuBar &&>(other)}
		, m_Menus{std::move(other.m_Menus)}
	{}

	MenuBar &MenuBar::operator=(MenuBar &&other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(std::forward<MenuBar &&>(other));
			this->m_Menus = std::move(other.m_Menus);
		}

		return *this;
	}

	std::unique_ptr<Widget> MenuBar::Clone(void) const noexcept
	{ return std::make_unique<std::decay<decltype(*this)>::type>(*this); }

	void MenuBar::HandleMouse(int button, int state, int x, int y) noexcept
	{
		for (auto &menu : this->m_Menus)
			menu.HandleMouse(button, state, x, y);
	}

	void MenuBar::Render(void) const noexcept
	{
		if (!this->m_Visible) [[unlikely]]
			return;

		for (const auto &menu : this->m_Menus)
			menu.Render();
	
		renderable::Rectangle separator{};
		separator.Replace(this->m_Position);
		separator.Resize(utility::Vec2<float>{this->m_Size.x, 1.f});
		separator.SetColor(utility::Vec3<float>{0.f, 0.f, 0.f});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(separator));
	
		s_pRenderer->Render();
	}
} /* disxx::ui */
