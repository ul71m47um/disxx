module disxx.ui.Tree;

namespace disxx::ui
{
	Tree::Tree(void) noexcept
		: Button{}
		, m_Widgets{}
	{}

	Tree::Tree(float x, float y, float width, float height) noexcept
		: Button{x, y, width, height}
		, m_Widgets{}
	{}

	Tree::Tree(const Tree &other) noexcept
		: Button{other}
		, m_Widgets{}
	{
		for (const auto &pWidget : other.m_Widgets)
			if (pWidget) [[likely]]
				this->m_Widgets.emplace_back(pWidget->Clone());
	}

	Tree &Tree::operator=(const Tree &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Button::operator=(other);
			for (const auto &pWidget : other.m_Widgets)
				if (pWidget) [[likely]]
					this->m_Widgets.emplace_back(pWidget->Clone());
		}

		return *this;
	}

	Tree::Tree(Tree &&other) noexcept
		: Button{std::forward<Tree &&>(other)}
		, m_Widgets{std::move(other.m_Widgets)}
	{}

	Tree &Tree::operator=(Tree &&other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Button::operator=(std::forward<Tree &&>(other));
			this->m_Widgets = std::move(other.m_Widgets);
		}

		return *this;
	}

	void Tree::Relayout(void) noexcept
	{
		for (const auto i : std::views::iota(0ul, this->m_Widgets.size()))
        {
			auto &pWidget{this->m_Widgets.at(i)};
           	if (!pWidget) [[unlikely]]
				continue;

			auto offset{this->m_Size.y};
			for (auto it{this->m_Widgets.begin()}; it != this->m_Widgets.begin() + i; ++it)
				if (const auto &ptr{*it}) [[likely]]
					offset += ptr->GetSize().y;

			pWidget->Replace
			(
				utility::Vec2<float>
				{
					this->m_Position.x + this->m_Size.x * 0.05f,
					this->m_Position.y - offset
				}
			);
			pWidget->Resize
			(
				utility::Vec2<float>
				{
					this->m_Size.x - this->m_Size.x * 0.05f,
					this->m_Size.y
				}
			);
        }
	}

	void Tree::Replace(utility::Vec2<float> position) noexcept
	{
		Button::Replace(position);
		this->Relayout();
	}

	void Tree::SetText(std::string_view text) noexcept
	{
		this->m_Text = std::format
		(
			"{} {}",
			this->m_bClicked
				? 'v'
				: '>',
			std::regex_replace
			(
				text.data(),
				std::regex{R"(^(>|v)\s)"},
				std::string{}
			)
		);
	}

	utility::Vec2<float> Tree::GetSize(void) const noexcept
	{
		if (this->m_bClicked)
		{
			auto height{this->m_Size.y};
			for (const auto &pWidget : this->m_Widgets)
				if (pWidget) [[likely]]	
					height += pWidget->GetSize().y;

			return utility::Vec2<float>{this->m_Size.x, height};
		}

		return this->m_Size;
	}

	void Tree::MouseButtonCallback(backend::event::MouseButton event) noexcept
	{
		const auto [x, y]{event.GetPosition()};
		const bool bInBounds{x >= this->m_Position.x && x <= this->m_Position.x + this->m_Size.x && y >= this->m_Position.y && y <= this->m_Position.y + this->m_Size.y};
		if (bInBounds && event.GetButton() == 0 && event.GetState() == 0)
		{
			this->m_bClicked = !this->m_bClicked;
			
			for (auto &pWidget : this->m_Widgets)
				pWidget->SetVisible(this->m_bClicked);
		}

		for (auto &pWidget : this->m_Widgets)
			if (pWidget) [[likely]]
				pWidget->MouseButtonCallback(event);
		this->SetText(this->m_Text);

		this->Relayout();
	}

	void Tree::Render(void) const noexcept
	{
		if (!this->m_bVisible)
			return;

		Button::Render();
		for (const auto &pWidget : this->m_Widgets)
			if (pWidget) [[likely]]
				if (pWidget->Visible())
					pWidget->Render();
	}
} /* disxx::ui */
