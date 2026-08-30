module;

#define INIT_GL_RENDERER(ptr) \
	static bool first{true}; \
	if (first) \
		ptr = new backend::GLRenderer{}; \
	first = false

module disxx.ui.Widget;

import disxx.ui.backend.IRenderer;

namespace disxx::ui
{
	disxx::utility::pointer::NonNull<backend::IRenderer> Widget::s_pRenderer{};

	void Widget::ClearBuffer(void) noexcept
	{ s_pRenderer->ClearBuffer(); }

	Widget::Widget(void) noexcept
		: m_Position{0, 0}
		, m_Size{0, 0}
		, m_pColor{0.0f, 0.0f, 0.0f}
		, m_Visible{true}
		, m_IsClicked{false}
        , m_IsHovered{false}
	{ INIT_GL_RENDERER(s_pRenderer); }

	Widget::Widget(float x, float y, float width, float height) noexcept
		: m_Position{x, y}
		, m_Size{width, height}
		, m_pColor{0.0f, 0.0f, 0.0f}
		, m_Visible{true}
		, m_IsClicked{false}
        , m_IsHovered{false}
	{ INIT_GL_RENDERER(s_pRenderer); }

	Widget::Widget(const Widget &other) noexcept
		: m_Position{other.m_Position}
		, m_Size{other.m_Size}
		, m_pColor{other.m_pColor[0], other.m_pColor[1], other.m_pColor[2]}
		, m_Visible{true}
		, m_IsClicked{false}
        , m_IsHovered{other.m_IsHovered}	
	{}

	void Widget::Replace(utility::Vec2<float> position) noexcept
	{ this->m_Position = position; }

	void Widget::Resize(utility::Vec2<float> size) noexcept
	{ this->m_Size = size; }
	
	Widget &Widget::operator=(const Widget &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			this->m_Position = other.m_Position;
			this->m_Size = other.m_Size;
			#pragma clang diagnostic push
			#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
			for (const auto i : std::views::iota(0u, 3u))
				this->m_pColor[i] = other.m_pColor[i];
			#pragma clang diagnostic pop
			this->m_Visible = other.m_Visible;
			this->m_IsClicked = other.m_IsClicked;
            this->m_IsHovered = other.m_IsHovered;	
		}

		return *this;
	}

	/*
	 * Handle Nothing.
	 */

	void Widget::HandleKeyboard(unsigned char, int, int)
	{ return; }

	void Widget::HandleMouse(int, int, int, int)
    { return; }
	
	void Widget::HandleMotion(int, int)
	{ return; }
} /* disxx::ui */
