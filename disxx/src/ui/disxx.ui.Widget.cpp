module;

#define INIT_GL_RENDERER(ptr) \
	static bool first{true}; \
	if (first) \
		ptr = new backend::opengl::Renderer{}; \
	first = false

module disxx.ui.Widget;

import disxx.ui.backend.abstract.IRenderer;
import disxx.ui.backend.opengl.Renderer;

namespace disxx::ui
{
	disxx::utility::pointer::NonNull<backend::abstract::IRenderer> Widget::s_pRenderer{};

	void Widget::ClearBuffer(void) noexcept
	{ s_pRenderer->ClearBuffer(); }

	Widget::Widget(void) noexcept
		: m_Position{0, 0}
		, m_Size{0, 0}
		, m_pColor{0.0f, 0.0f, 0.0f}
		, m_bVisible{true}
		, m_bClicked{false}
        , m_bHovered{false}
	{ INIT_GL_RENDERER(s_pRenderer); }

	Widget::Widget(float x, float y, float width, float height) noexcept
		: m_Position{x, y}
		, m_Size{width, height}
		, m_pColor{0.0f, 0.0f, 0.0f}
		, m_bVisible{true}
		, m_bClicked{false}
        , m_bHovered{false}
	{ INIT_GL_RENDERER(s_pRenderer); }

	Widget::Widget(const Widget &other) noexcept
		: m_Position{other.m_Position}
		, m_Size{other.m_Size}
		, m_pColor{other.m_pColor[0], other.m_pColor[1], other.m_pColor[2]}
		, m_bVisible{true}
		, m_bClicked{false}
        , m_bHovered{other.m_bHovered}	
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
			this->m_bVisible = other.m_bVisible;
			this->m_bClicked = other.m_bClicked;
            this->m_bHovered = other.m_bHovered;	
		}

		return *this;
	}

	// Handle nothing here
	void Widget::MouseMotionCallback(backend::event::MouseMotion) noexcept {}	
	void Widget::MouseButtonCallback(backend::event::MouseButton) noexcept {}
	void Widget::KeyboardCallback(backend::event::Keyboard) noexcept {}
} /* disxx::ui */
