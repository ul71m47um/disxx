module disxx.ui.Tree;

namespace disxx::ui
{
	Tree::Tree(void) noexcept
		: Button{}
	{}

	Tree::Tree(float x, float y, float width, float height) noexcept
		: Button{x, y, width, height}
	{}

	Tree::Tree(const Tree &other) noexcept
		: Button{other}
	{}

	Tree &Tree::operator=(const Tree &other) noexcept
	{
		if (this != &other) [[likely]]
			Button::operator=(other);
		return *this;
	}

	Tree::Tree(Tree &&other) noexcept
		: Button{std::forward<Tree &&>(other)}
	{}

	Tree &Tree::operator=(Tree &&other) noexcept
	{
		if (this != &other) [[likely]]
			Button::operator=(std::forward<Tree &&>(other));
		return *this;
	}

	void Tree::Replace(utility::Vec2<float> position) noexcept
	{
		const utility::Vec2<float> delta
		{
			position.x - this->m_Position.x,
			position.y - this->m_Position.y
		};
	
		Button::Replace(position);
	
		for (auto &pChild : this->m_Widgets)
			pChild->Replace(utility::Vec2<float>{pChild->GetPosition().x + delta.x, pChild->GetPosition().y + delta.y});
	}

	void Tree::SetText(std::string_view text) noexcept
	{
		this->m_Text = std::format
		(
			"{} {}",
			this->m_bClicked
				? 'v'
				: '>',
			text
		);
	}

	void Tree::MouseButtonCallback(backend::event::MouseButton event) noexcept
	{
		if (event.GetButton() == 0 && event.GetState() == 0)
			this->m_bClicked = !this->m_bClicked;

		if (this->m_bClicked)
			for (auto &pWidget : this->m_Widgets)
				pWidget->SetVisible(true);

		for (auto &pWidget : this->m_Widgets)
			pWidget->MouseButtonCallback(event);

		this->SetText(this->m_Text);
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
