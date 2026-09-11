module disxx.ui.BoxLayout;

namespace disxx::ui
{
	BoxLayout::BoxLayout(void) noexcept
		: Widget{}
		, m_Widgets{}
		, m_Type{}
	{}

	BoxLayout::BoxLayout(Type type) noexcept
		: Widget{}
		, m_Widgets{}
		, m_Type{type}
	{}

	BoxLayout::BoxLayout(float x, float y, float width, float height, Type type) noexcept
		: Widget{x, y, width, height}
		, m_Widgets{}
		, m_Type{type}
	{}

	BoxLayout::BoxLayout(const BoxLayout &other) noexcept
		: Widget{other}
		, m_Widgets{}
		, m_Type{other.m_Type}
	{
		for (const auto &widget : other.m_Widgets)
		{
			std::visit
			(
				[this](auto &widget) -> void
				{
					if constexpr (std::same_as<decltype(widget), unsigned short int>::value)
						this->m_Widgets.push_back({widget});
					else if (widget)
						this->m_Widgets.emplace_back({widget->Clone()});
				},
				widget
			);
		}
	}

	BoxLayout &BoxLayout::operator=(const BoxLayout &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(other);
			for (const auto &widget : other.m_Widgets)
			{
				std::visit
				(
					[this](auto &widget) -> void
					{
						if constexpr (std::same_as<decltype(widget), unsigned short int>::value)
							this->m_Widgets.push_back({widget});
						else if (widget)
							this->m_Widgets.emplace_back({widget->Clone()});
					},
					widget
				);
			}
			this->m_Type = other.m_Type;
		}

		return *this;
	}

	BoxLayout::BoxLayout(BoxLayout &&other) noexcept
		: Widget{std::forward<BoxLayout &&>(other)}
		, m_Widgets{std::move(other.m_Widgets)}
		, m_Type{std::move(other.m_Type)}
	{}

	BoxLayout &BoxLayout::operator=(BoxLayout &&other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(std::forward<BoxLayout &&>(other));
			this->m_Widgets = std::move(other.m_Widgets);
			this->m_Type = std::move(other.m_Type);
		}

		return *this;
	}
} /* disxx::ui */
