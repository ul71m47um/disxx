module disxx.ui.backend.glut.Window;

import disxx.ui.backend.glut.Manager;

namespace disxx::ui::backend::glut
{	
	Window::~Window(void) noexcept { this->Destroy(); }
	
	void Window::Destroy(void) noexcept { Manager::Init()->DestroyWindow(this->m_hWin); }

	void Window::Iconify(void) noexcept
	{
		this->Switch();
		glutIconifyWindow();
	}

	void Window::Show(void) noexcept
	{
		this->Switch();
		glutShowWindow();
		// Set a timer to avoid a race
		glutTimerFunc
		(
			0,
			[](int hWin) -> void
			{
				glutSetWindow(hWin);
				glutPostRedisplay();
			},
			glutGetWindow()
		);
	}

	void Window::Hide(void) noexcept
	{
		this->Switch();
		glutHideWindow();
	}

	void Window::Push(void) noexcept
	{
		this->Switch();
		glutPushWindow();
	}

	void Window::Pop(void) noexcept
	{
		this->Switch();
		glutPopWindow();
	}

	void Window::SetTitle(std::string_view title) noexcept
	{
		this->Switch();
		glutSetWindowTitle(title.data());
	}

	void Window::SetSize(utility::Vec2<int> size) noexcept
	{
		const auto [width, height]{size};
		this->Switch();
		glutReshapeWindow(width, height);
	}

	void utility::Vec2<int> Window::GetSize() noexcept
	{
		return utility::Vec2<int>
		{
			glutGet(GLUT_WINDOW_WIDTH),
			glutGet(GLUT_WINDOW_HEIGHT)
		};
	}

	bool Window::ShouldClose(void) const noexcept { return false; }

	int Window::Exec(std::function<void(event::Queue &)> f) const noexcept { f(this->m_Events); }
} /* disxx::ui::backend::glut */
