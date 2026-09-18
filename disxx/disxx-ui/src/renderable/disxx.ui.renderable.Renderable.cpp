module disxx.ui.renderable.Renderable;

namespace disxx::ui::renderable
{
	Renderable::Renderable(void) noexcept
		: m_Color{}
		, m_Position{}
		, m_Size{}
	{}

	Renderable::Renderable(const Renderable &other) noexcept
		: m_Color{other.m_Color}
		, m_Position{other.m_Position}
		, m_Size{other.m_Size}
	{}

	Renderable &Renderable::operator=(const Renderable &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			this->m_Color = other.m_Color;
			this->m_Position = other.m_Position;
			this->m_Size = other.m_Size;
		}

		return *this;
	}

	Renderable::Renderable(Renderable &&other) noexcept
		: m_Color{std::move(other.m_Color)}
		, m_Position{std::move(other.m_Position)}
		, m_Size{std::move(other.m_Size)}
	{}

	Renderable &Renderable::operator=(Renderable &&other) noexcept
	{
		this->m_Color = std::move(other.m_Color);
		this->m_Position = std::move(other.m_Position);
		this->m_Size = std::move(other.m_Size);
		
		return *this;
	}

	void Renderable::Replace(utility::Vec2<float> vec) noexcept { this->m_Position = vec; }

	void Renderable::Resize(utility::Vec2<float> vec) noexcept { this->m_Size = vec; }

	utility::Vec2<float> Renderable::GetPosition(void) const noexcept { return this->m_Position; }

	utility::Vec2<float> Renderable::GetSize(void) const noexcept { return this->m_Size; }

	void Renderable::SetColor(utility::Vec3<float> vec) noexcept { this->m_Color = vec; }

	utility::Vec3<float> Renderable::GetColor(void) const noexcept { return this->m_Color; }
} /* disxx::ui::utility */
