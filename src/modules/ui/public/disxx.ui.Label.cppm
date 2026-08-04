export module disxx.ui.Label;

import disxx.ui.Widget;

export import std;

export namespace disxx::ui
{
	class [[clang::type_visibility("default")]] [[nodiscard]] Label final : public Widget
	{
	  private:
		std::string m_Text{};

	  public:
		explicit Label(void) noexcept;
		explicit Label(float, float, float, float) noexcept;

		Label(const Label &) noexcept;
		Label &operator=(const Label &) noexcept;

		Label(Label &&) noexcept;
		Label &operator=(Label &&) noexcept;

		inline void SetText(std::string_view) noexcept;
		inline std::string_view GetText(void) const noexcept;
	
		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;

		virtual void Render(void) const noexcept override;
	};

	inline void Label::SetText(std::string_view str) noexcept
	{ this->m_Text = str.data(); }

	inline std::string_view Label::GetText(void) const noexcept
	{ return this->m_Text; }
} /* disxx::ui */
