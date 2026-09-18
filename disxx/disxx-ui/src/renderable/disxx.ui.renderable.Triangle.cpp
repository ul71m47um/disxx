module disxx.ui.renderable.Triangle;

import disxx.ui.utility.Vertex;
import disxx.ui.utility.Vec;

import std;

namespace disxx::ui::renderable
{
	Triangle::Triangle(void) noexcept
		: Shape{}
	{}

	Triangle::Triangle(const Triangle &other) noexcept
		: Shape{other}
	{}

	Triangle &Triangle::operator=(const Triangle &other) noexcept
	{
		if (this != &other) [[likely]]
			Shape::operator=(other);
		return *this;
	}

	Triangle::Triangle(Triangle &&other) noexcept
		: Shape{std::forward<Triangle &&>(other)}
	{}

	Triangle &Triangle::operator=(Triangle &&other) noexcept
	{
		if (this != &other) [[likely]]
			Shape::operator=(std::forward<Triangle &&>(other));
		return *this;
	}

	std::vector<utility::Vertex<float>> Triangle::GetVertices(void) const noexcept
	{
		std::vector<utility::Vertex<float>> vertices{};
		
		vertices.emplace_back(utility::Vertex<float>{this->m_Position, this->m_Color});
		vertices.emplace_back(utility::Vertex<float>{utility::Vec2<float>{this->m_Position.x, this->m_Position.y + this->m_Size.y}, this->m_Color});
		vertices.emplace_back(utility::Vertex<float>{utility::Vec2<float>{this->m_Position.x + this->m_Size.x, this->m_Position.y + this->m_Size.y}, this->m_Color});

		return vertices;
	}
} /* disxx::ui::renderable */
