export module disxx.ui.MenuBar;

import disxx.ui.Widget;
import disxx.ui.Menu;

import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] MenuBar final : public Widget
	{
	  private:
		std::vector<Menu> m_Menus{};

	  public:
		explicit MenuBar(void) noexcept;

		MenuBar(const MenuBar &) noexcept;
		MenuBar &operator=(const MenuBar &) noexcept;

		MenuBar(MenuBar &&) noexcept;
		MenuBar &operator=(MenuBar &&) noexcept;

		inline void Add(Menu &&) noexcept;
	
		virtual void Render(void) const noexcept override;
	};

	inline void MenuBar::Add(Menu &&menu) noexcept
	{ this->m_Menus.emplace_back(std::forward<Menu &&>(menu)); }
} /* disxx::ui */
