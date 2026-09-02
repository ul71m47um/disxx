module disxx.ui.Frame;

import disxx.ui.renderable.Rectangle;

import std;

namespace disxx::ui
{
	Frame::Frame(void) noexcept
		: Widget{}
	{}

	Frame::Frame(float x, float y, float width, float height) noexcept
		: Widget{x, y, width, height}
	{}

	Frame::Frame(const Frame &other) noexcept
		: Widget{other}
	{}

	Frame &Frame::operator=(const Frame &other) noexcept
	{
		if (this != &other) [[likely]]
			Widget::operator=(other);
		return *this;
	}

	Frame::Frame(Frame &&other) noexcept
		: Widget{std::forward<Frame &&>(other)}
	{}

	Frame &Frame::operator=(Frame &&other) noexcept
	{
		Widget::operator=(std::forward<Frame &&>(other));
		return *this;
	}

	std::unique_ptr<Widget> Frame::Clone(void) const noexcept
	{ return std::make_unique<std::decay<decltype(*this)>::type>(*this); }

	void Frame::Render(void) const noexcept
	{
		if (!this->m_bVisible)
			return;

		// Add a subframe
		renderable::Rectangle subframe{};
		subframe.Replace(utility::Vec2<float>{this->m_Position.x - 1.f, this->m_Position.y - 1.f});
		subframe.Resize(utility::Vec2<float>{this->m_Size.x + 2.f, this->m_Size.y + 2.f});
		subframe.SetColor(utility::Vec3<float>{0.f, 0.f, 0.f});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(subframe));

		// Add the frame itself
		renderable::Rectangle frame{};
		frame.Replace(utility::Vec2<float>{this->m_Position.x, this->m_Position.y});
		frame.Resize(utility::Vec2<float>{this->m_Size.x, this->m_Size.y});
		frame.SetColor(utility::Vec3<float>{this->m_pColor[0], this->m_pColor[1], this->m_pColor[2]});
		s_pRenderer->Push(std::make_unique<renderable::Rectangle>(frame));
	}
} /* disxx::ui */
