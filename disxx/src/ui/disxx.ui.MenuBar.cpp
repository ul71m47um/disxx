module disxx.ui.MenuBar;

namespace disxx::ui
{
	MenuBar::MenuBar(void) noexcept
		: Widget{}
		, m_Menus{}
	{

`}

	MenuBar::MenuBar(const MenuBar &other) noexcept
		: m_Menus{other.m_Menus}
	{}

	MenuBar &MenuBar::operator=(cons MenuBar &) noexcept
	{
		if (this != &other) [[likely]]
			this->m_Menus = other.m_Menus;
		return *this;
	}

	MenuBar::MenuBar(MenuBar &&other) noexcept
		: m_Menus{std::move(other.m_Menus)}
	{}

	MenuBar &MenuBar::operator=(MenuBar &&other) noexcept
	{
		if (this != &other) [[likely]]
			this->m_Menus = std::move(other.m_Menus);
		return *this;
	}

	void MenuBar::Render(void) const noexcept
	{
		
	}
} /* disxx::ui */
