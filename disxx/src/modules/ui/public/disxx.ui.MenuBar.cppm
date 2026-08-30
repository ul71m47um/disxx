export module disxx.ui.MenuBar;

export import disxx.ui.Menu;
import disxx.ui.backend.GLUTContext;
import disxx.ui.Widget;

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

		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;

		virtual void HandleMouse(int, int, int, int) noexcept override;
		virtual void Render(void) const noexcept override;
	};

	inline void MenuBar::Add(Menu &&menu) noexcept
	{
		const auto [width, height]{backend::GLUTContext::GetWindowSize()};
		menu.Resize(utility::Vec2<float>{width * 0.05f, height * 0.03f});
		auto offset{0.f};
		for (const auto &other : this->m_Menus)
			offset += other.GetSize().x;
		menu.Replace(utility::Vec2<float>{offset, this->m_Position.y});
		this->m_Menus.emplace_back(std::forward<Menu &&>(menu));
	}
} /* disxx::ui */
