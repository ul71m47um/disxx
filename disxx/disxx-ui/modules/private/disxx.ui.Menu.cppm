export module disxx.ui.Menu;

export import disxx.ui.MenuEntry;
import disxx.ui.Widget;

import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] Menu final : public Widget
	{
	  private:
		std::vector<MenuEntry> m_Entries{};
		std::string m_Text{};

	  public:
		explicit Menu(void) noexcept;
		explicit Menu(std::string_view) noexcept;

		Menu(const Menu &) noexcept;
		Menu &operator=(const Menu &) noexcept;

		Menu(Menu &&) noexcept;
		Menu &operator=(Menu &&) noexcept;

		inline void SetText(std::string_view) noexcept;

		inline void Add(MenuEntry &&) noexcept;

		virtual void Replace(utility::Vec2<float>) noexcept override;

		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;

		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void Render(void) const noexcept override;
	};

	inline void Menu::SetText(std::string_view text) noexcept
	{ this->m_Text = text.data(); }

	inline void Menu::Add(MenuEntry &&entry) noexcept
	{
		entry.Replace
		(
			utility::Vec2<float>
			{
				this->m_Position.x,
				this->m_Position.y
					- this->m_Size.y
					* (static_cast<float>(this->m_Entries.size()) + 1.f)
			}
		);

		this->m_Entries.emplace_back(std::forward<MenuEntry &&>(entry));

		const auto width
		{
			std::max
			(
				std::ranges::max
				(
					this->m_Entries
						| std::views::all
						| std::views::transform([](const auto &var) -> float { return static_cast<float>(var.GetText().size()) * 8.f; })
						| std::ranges::to<std::vector<float>>()
				) + 10.f,
				this->m_Size.x
			)
		};

		// Resize all the entries to max entry
		for (auto &e : this->m_Entries)
			e.Resize(utility::Vec2<float>{width, this->m_Size.y});
	}
} /* disxx::ui */
