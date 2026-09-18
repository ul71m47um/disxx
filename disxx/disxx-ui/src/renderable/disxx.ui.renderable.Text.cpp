module disxx.ui.renderable.Text;

namespace disxx::ui::renderable
{
	Text::Text(void) noexcept
		: Renderable{}
		, m_Text{}
	{}

	Text::Text(std::string_view str) noexcept
		: Renderable{}
		, m_Text{str}
	{}

	Text::Text(const Text &other) noexcept
		: Renderable{other}
		, m_Text{other.m_Text}
	{}

	Text &Text::operator=(const Text &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Renderable::operator=(other);
			this->m_Text = other.m_Text;
		}

		return *this;
	}

	Text::Text(Text &&other) noexcept
		: Renderable{std::move(other)}
		, m_Text{std::move(other.m_Text)}
	{}

	Text &Text::operator=(Text &&other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Renderable::operator=(std::forward<Text &&>(other));
			this->m_Text = std::move(other.m_Text);
		}

		return *this;
	}

	std::vector<utility::Vertex<float>> Text::GetVertices(void) const noexcept
	{ return std::vector<utility::Vertex<float>>{}; }
} /* disxx::ui::utility */
