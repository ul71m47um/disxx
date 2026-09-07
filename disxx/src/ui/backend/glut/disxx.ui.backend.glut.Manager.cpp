module;

#ifdef __APPLE__
#	include <GLUT/glut.h>
#else
#	include <GL/freeglut.h>
#endif

module disxx.ui.backend.glut.Manager;

import disxx.ui.backend.event.MouseButton;
import disxx.ui.backend.event.MouseMotion;
import disxx.ui.backend.event.Keyboard;
import disxx.ui.backend.event.Reshape;
import disxx.ui.backend.glut.Window;
import disxx.ui.utility.Vec;

import disxx.utility.pointer.NonNull;

import std;

namespace disxx::ui::backend::glut
{
	disxx::utility::pointer::NonNull<Manager> Manager::s_pInstance{new Manager{}};

	void Manager::MouseButtonCallback(int button, int state, int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;

		glutSetWindow(std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_hWin);
		y = glutGet(GLUT_WINDOW_HEIGHT) - y;
		
		event::MouseButton event
		{
			utility::Vec2<float>
			{
				static_cast<float>(x),
				static_cast<float>(y)
			},
			button,
			state
		};
		std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_Events.Push(event);
	}

	void Manager::MousePassiveMotionCallback(int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;
	
		glutSetWindow(std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_hWin);
		y = glutGet(GLUT_WINDOW_HEIGHT) - y;

		event::MouseMotion event
		{
			utility::Vec2<float>
			{
				static_cast<float>(x),
				static_cast<float>(y)
			},
			true
		};
		std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_Events.Push(event);
	}

	void Manager::MouseMotionCallback(int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;
	
		glutSetWindow(std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_hWin);
		y = glutGet(GLUT_WINDOW_HEIGHT) - y;
		
		event::MouseMotion event
		{
			utility::Vec2<float>
			{
				static_cast<float>(x),
				static_cast<float>(y)
			},
			false
		};
		std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_Events.Push(event);
	}

	void Manager::KeyboardCallback(unsigned char key, int, int) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;

		event::Keyboard event{key};
		std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_Events.Push(event);
	}

	void Manager::ReshapeCallback(int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;
	
		event::Reshape event
		{
			utility::Vec2<float>
			{
				static_cast<float>(x),
				static_cast<float>(y)
			}
		};
		std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_Events.Push(event);
	}

	void Manager::WindowCloseCallback(void) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;
	
		std::dynamic_pointer_cast<Window>(this->m_Windows.at(hWin))->m_bShouldClose = true;
	}
	
	Manager::Weak Manager::CreateWindow(void) noexcept
	{
		const auto hWin{glutCreateWindow("Window")};
		this->m_Windows[hWin] = std::make_shared<Window>(hWin);
		this->SetCallbacks();

		return this->m_Windows[hWin];
	}

	void Manager::DestroyWindow(Weak ptr) noexcept
	{
		if (const auto pWin{ptr.lock()}) [[likely]]
		{
			if (const auto pCurrentWindow{this->m_pCurrentWindow.lock()}) [[likely]]
				if (pCurrentWindow->GetHandle() == pWin->GetHandle())
					this->m_pCurrentWindow.reset();

			const auto hWin{pWin->GetHandle()};
			if (auto it{this->m_Windows.find(hWin)}; it != this->m_Windows.end()) [[likely]]
				this->m_Windows.erase(it);
			glutDestroyWindow(hWin);
		}
	}

	void Manager::SetWindow(const Weak ptr) noexcept
	{
		if (const auto pWin{ptr.lock()}) [[likely]]
		{
			this->m_pCurrentWindow = pWin;
			glutSetWindow(pWin->GetHandle());
		}
	}

	std::optional<Manager::Weak> Manager::GetWindow(void) const noexcept
	{
		if (const auto hWin{glutGetWindow()}; !this->m_Windows.contains(hWin) || !this->m_pCurrentWindow.lock()) [[unlikely]]
			return std::nullopt;
		return this->m_pCurrentWindow;
	}

	void Manager::SetCallbacks(void) const noexcept
	{
		glutDisplayFunc(+[] -> void {});

		glutMouseFunc
		(
			+[](int button, int state, int x, int y) -> void
			{
				s_pInstance->MouseButtonCallback
				(
					button,
					state,
					x,
					y
				);
			}
		);
		glutPassiveMotionFunc
		(
			+[](int x, int y) -> void
			{ s_pInstance->MousePassiveMotionCallback(x, y); }
		);
		glutMotionFunc
		(
			+[](int x, int y) -> void
			{ s_pInstance->MouseMotionCallback(x, y); }
		);
		glutKeyboardFunc
		(
			+[](unsigned char key, int x, int y) -> void
			{ s_pInstance->KeyboardCallback(key, x, y); }
		);
		glutReshapeFunc
		(
			+[](int width, int height) -> void
			{ s_pInstance->ReshapeCallback(width, height); }
		);
	}
} /* disxx::ui::backend::glut */
