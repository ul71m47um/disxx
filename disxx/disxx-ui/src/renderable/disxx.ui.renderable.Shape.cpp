module disxx.ui.renderable.Shape;

import std;

namespace disxx::ui::renderable
{
	Shape::Shape(void) noexcept
		: Renderable{}
	{}

	Shape::Shape(const Shape &other) noexcept
		: Renderable{other}
	{}

	Shape &Shape::operator=(const Shape &other) noexcept
	{
		if (this != &other) [[likely]]
			Renderable::operator=(other);
		return *this;
	}

	Shape::Shape(Shape &&other) noexcept
		: Renderable{std::forward<Shape &&>(other)}
	{}

	Shape &Shape::operator=(Shape &&other) noexcept
	{
		if (this != &other) [[likely]]
			Renderable::operator=(std::forward<Shape &&>(other));
		return *this;
	}
} /* disxx::ui::utility */
