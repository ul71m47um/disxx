module disxx.ui.renderable.Rectangle;

import disxx.ui.utility.Vertex;
import disxx.ui.utility.Vec;

import std;

namespace disxx::ui::renderable
{
	Rectangle::Rectangle(void) noexcept
		: Shape{}
	{}

	Rectangle::Rectangle(const Rectangle &other) noexcept
		: Shape{other}
	{}

	Rectangle &Rectangle::operator=(const Rectangle &other) noexcept
	{
		if (this != &other) [[likely]]
			Shape::operator=(other);
		return *this;
	}

	Rectangle::Rectangle(Rectangle &&other) noexcept
		: Shape{std::forward<Rectangle &&>(other)}
	{}

	Rectangle &Rectangle::operator=(Rectangle &&other) noexcept
	{
		if (this != &other) [[likely]]
			Shape::operator=(std::forward<Rectangle &&>(other));
		return *this;
	}

	std::vector<utility::Vertex<float>> Rectangle::GetVertices(void) const noexcept
	{
		std::vector<utility::Vertex<float>> vertices{};
		
		// First triangle
		vertices.emplace_back(utility::Vertex<float>{this->m_Position, this->m_Color});
		vertices.emplace_back(utility::Vertex<float>{utility::Vec2<float>{this->m_Position.x, this->m_Position.y + this->m_Size.y}, this->m_Color});
		vertices.emplace_back(utility::Vertex<float>{utility::Vec2<float>{this->m_Position.x + this->m_Size.x, this->m_Position.y + this->m_Size.y}, this->m_Color});

		// Second triangle
		vertices.emplace_back(utility::Vertex<float>{utility::Vec2<float>{this->m_Position.x + this->m_Size.x, this->m_Position.y + this->m_Size.y}, this->m_Color});
		vertices.emplace_back(utility::Vertex<float>{utility::Vec2<float>{this->m_Position.x + this->m_Size.x, this->m_Position.y}, this->m_Color});
		vertices.emplace_back(utility::Vertex<float>{this->m_Position, this->m_Color});
	
		return vertices;
	}
} /* disxx::ui::renderable */
