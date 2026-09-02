export module disxx.ui.TextInput;

import disxx.ui.Widget;

export import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] TextInput final : public Widget
	{
	  private:
		std::function<void(const Widget *const)> m_Callback{};
		std::string m_Text{};

	  public:
		explicit TextInput(void) noexcept;
		explicit TextInput(float, float, float, float) noexcept;
		TextInput(const TextInput &) noexcept;
		TextInput &operator=(const TextInput &) noexcept;

		virtual ~TextInput(void) noexcept override = default;

		inline void SetText(std::string_view) noexcept;
		inline std::string_view GetText(void) const noexcept;

		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;

		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void KeyboardCallback(backend::event::Keyboard) noexcept override;
		virtual void Render(void) const noexcept override;
	};

	inline void TextInput::SetText(std::string_view text) noexcept
	{ this->m_Text = text; }

	inline std::string_view TextInput::GetText(void) const noexcept
	{ return this->m_Text; }
} // disxx::ui
