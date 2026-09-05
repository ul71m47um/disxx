module disxx.ui.MessageBox;

import disxx.ui.Widget;
import disxx.ui.Button;
import disxx.ui.Label;

namespace disxx::ui
{
	MessageBox::MessageBox(void) noexcept
		: m_Window{utility::Vec2<int>{300, 150}, "Warning"}
	{
		this->m_Window.SetVisible(true);

		Label lbl
		{
			150.f,
			125.f,
			0.f,
			0.f
		};
		lbl.SetText("");
		this->m_Window.AddWidget(std::make_unique<Label>(std::move(lbl)));

		disxx::ui::Button btn{125.f, 25.f, 50.f, 25.f};
		btn.SetColor(0.3f, 0.3f, 0.3f);
		btn.SetText("OK");
		btn.SetCallback
		(
			disxx::ui::Button::Trigger::BTN_CLICKED,
			[this](const disxx::ui::Widget *const _) mutable -> void
			{
				for (auto &pWidget : this->m_Window.GetWidgets())
					pWidget->SetVisible(false);
				this->m_Window.SetVisible(false);
			}
		);
		this->m_Window.AddWidget(std::make_unique<Button>(std::move(btn)));
	}

	MessageBox::MessageBox(std::string_view text) noexcept
		: m_Window{utility::Vec2<int>{300, 150}, "Warning"}
	{
		this->m_Window.SetVisible(true);

		Label lbl
		{
			std::clamp((300.f - (text.size() + 4) * 9.f) + (300.f / (text.size() + 4) * 9.f), 0.f, 300.f),
			125.f,
			0.f,
			0.f
		};
		lbl.SetText(std::format("[!] {}", text));
		this->m_Window.AddWidget(std::make_unique<Label>(std::move(lbl)));

		disxx::ui::Button btn{125.f, 25.f, 50.f, 25.f};
		btn.SetColor(0.3f, 0.3f, 0.3f);
		btn.SetText("OK");
		btn.SetCallback
		(
			disxx::ui::Button::Trigger::BTN_CLICKED,
			[this](const disxx::ui::Widget *const _) mutable -> void
			{
				for (auto &pWidget : this->m_Window.GetWidgets())
					pWidget->SetVisible(false);
				this->m_Window.SetVisible(false);
			}
		);
		this->m_Window.AddWidget(std::make_unique<Button>(std::move(btn)));
	}

	MessageBox::MessageBox(const MessageBox &other) noexcept
		: m_Window{other.m_Window}
	{}

	MessageBox &MessageBox::operator=(const MessageBox &other) noexcept
	{
		if (this != &other) [[likely]]
			this->m_Window = other.m_Window;
		return *this;
	}

	MessageBox::MessageBox(MessageBox &&other) noexcept
		: m_Window{std::move(other.m_Window)}
	{}

	MessageBox &MessageBox::operator=(MessageBox &&other) noexcept
	{
		if (this != &other) [[likely]]
			this->m_Window = std::move(other.m_Window);
		return *this;
	}
} /* disxx::ui */
