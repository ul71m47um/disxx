export module disxx.ui.MenuEntry;

import disxx.ui.Widget;

export import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] MenuEntry final : public Widget
	{
	  private:
		std::function<void(void)> m_Callback{};
		std::string m_Text{};
	
	  public:
		explicit MenuEntry(void) noexcept;
		explicit MenuEntry(std::string_view, std::function<void(void)>) noexcept;

		MenuEntry(const MenuEntry &) noexcept;
		MenuEntry &operator=(const MenuEntry &) noexcept;
	
		MenuEntry(MenuEntry &&) noexcept;
		MenuEntry &operator=(MenuEntry &&) noexcept;

		inline void SetText(std::string_view) noexcept;
		inline void SetCallback(std::function<void(void)>) noexcept;

		inline std::string_view GetText(void) const noexcept;

		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;

		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void Render(void) const noexcept override;
	
		inline void operator()(void) const noexcept;
	};

	inline void MenuEntry::SetText(std::string_view str) noexcept
	{ this->m_Text = str.data(); }

	inline void MenuEntry::SetCallback(std::function<void(void)> f) noexcept
	{ this->m_Callback = f; }

	inline std::string_view MenuEntry::GetText(void) const noexcept
	{ return this->m_Text; }

	inline void MenuEntry::operator()(void) const noexcept
	{ this->m_Callback(); }
} /* disxx::ui */
