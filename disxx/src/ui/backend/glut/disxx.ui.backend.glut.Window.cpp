module;

#ifdef __APPLE__
#	include <GLUT/glut.h>
#else
#	include <GL/freeglut.h>
#endif

module disxx.ui.backend.glut.Window;

import disxx.ui.backend.glut.Manager;
import disxx.ui.backend.glut.Context;

namespace disxx::ui::backend::glut
{
	Window::Window(const Handle &handle) noexcept
		: abstract::Window<Handle>{handle}
	{}

	Window::~Window(void) noexcept { this->Destroy(); }
	
	void Window::Destroy(void) noexcept
	{ Manager::Get()->DestroyWindow(std::make_shared<Window>(this->m_hWin)); }

	void Window::Iconify(void) noexcept
	{
		glutSetWindow(this->m_hWin);
		glutIconifyWindow();
	}

	void Window::Show(void) noexcept
	{
		glutSetWindow(this->m_hWin);
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
		glutSetWindow(this->m_hWin);
		glutHideWindow();
	}

	void Window::Push(void) noexcept
	{
		glutSetWindow(this->m_hWin);
		glutPushWindow();
	}

	void Window::Pop(void) noexcept
	{
		glutSetWindow(this->m_hWin);
		glutPopWindow();
	}

	void Window::SetTitle(std::string_view title) noexcept
	{
		glutSetWindow(this->m_hWin);
		glutSetWindowTitle(title.data());
	}

	void Window::SetSize(utility::Vec2<int> size) noexcept
	{
		const auto [width, height]{size};
		glutSetWindow(this->m_hWin);
		glutReshapeWindow(width, height);
	}

	utility::Vec2<int> Window::GetSize(void) const noexcept
	{
		glutSetWindow(this->m_hWin);
		return utility::Vec2<int>
		{
			glutGet(GLUT_WINDOW_WIDTH),
			glutGet(GLUT_WINDOW_HEIGHT)
		};
	}

	bool Window::ShouldClose(void) const noexcept { return false; }

	int Window::Exec(std::function<int(event::Queue &)> func) noexcept { return func(this->m_Events); }
} /* disxx::ui::backend::glut */
