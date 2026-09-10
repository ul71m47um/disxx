module;

#ifdef __APPLE__
#	include <GLUT/glut.h>
#else
#	include <GL/freeglut.h>
#endif

module disxx.ui.backend.glut.Window;

import disxx.ui.backend.glut.Manager;
import disxx.ui.backend.glut.Context;

namespace
{
	class __attribute__((visibility("hidden"))) [[nodiscard]] WinGuard
	{
	  private:
		disxx::ui::backend::glut::Window::Handle m_hWin;

	  public:
		explicit WinGuard(disxx::ui::backend::glut::Window::Handle) noexcept;
	
		WinGuard(const WinGuard &) noexcept = delete;
		WinGuard &operator=(const WinGuard &) noexcept = delete;
	
		~WinGuard(void) noexcept;
	};

	WinGuard::WinGuard(disxx::ui::backend::glut::Window::Handle hWin) noexcept
		: m_hWin{hWin}
	{}

	WinGuard::~WinGuard(void) noexcept
	{
		if (this->m_hWin) [[likely]]
			glutSetWindow(this->m_hWin);
	}
} /* */

namespace disxx::ui::backend::glut
{
	Window::Window(const Handle &handle) noexcept
		: abstract::Window<Handle>{handle}
	{}

	Window::~Window(void) noexcept { this->Destroy(); }
	
	void Window::Destroy(void) noexcept
	{
		WinGuard guard{glutGetWindow()};

		if (!this->m_hWin) [[unlikely]]
			return;

		glutSetWindow(std::exchange(this->m_hWin, {}));
		if (const auto opt{Context::Get()->CurrentWindow()}) [[likely]]
			Manager::Get()->DestroyWindow(*opt);
	}

	void Window::Iconify(void) noexcept
	{
		WinGuard guard{glutGetWindow()};

		glutSetWindow(this->m_hWin);
		glutIconifyWindow();
	}

	void Window::Show(void) noexcept
	{
		WinGuard guard{glutGetWindow()};

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
		WinGuard guard{glutGetWindow()};

		glutSetWindow(this->m_hWin);
		glutHideWindow();
	}

	void Window::Push(void) noexcept
	{
		WinGuard guard{glutGetWindow()};

		glutSetWindow(this->m_hWin);
		glutPushWindow();
	}

	void Window::Pop(void) noexcept
	{
		WinGuard guard{glutGetWindow()};

		glutSetWindow(this->m_hWin);
		glutPopWindow();
	}

	void Window::SetTitle(std::string_view title) noexcept
	{
		WinGuard guard{glutGetWindow()};

		glutSetWindow(this->m_hWin);
		glutSetWindowTitle(title.data());
	}

	void Window::SetSize(utility::Vec2<int> size) noexcept
	{
		WinGuard guard{glutGetWindow()};

		this->m_Size = size;
		glutSetWindow(this->m_hWin);
		glutReshapeWindow(this->m_Size.x, this->m_Size.y);
	}

	void Window::Redisplay(void) const noexcept
	{
		WinGuard guard{glutGetWindow()};

		glutSetWindow(this->m_hWin);
		glutPostRedisplay();
	}

	utility::Vec2<int> Window::GetSize(void) const noexcept { return this->m_Size; }

	bool Window::ShouldClose(void) const noexcept { return this->m_bShouldClose; }

	int Window::Exec(std::function<int(event::Queue &)> func) noexcept
	{
		WinGuard guard{glutGetWindow()};

		glutSetWindow(this->m_hWin);
		return func(this->m_Events);
	}
} /* disxx::ui::backend::glut */
