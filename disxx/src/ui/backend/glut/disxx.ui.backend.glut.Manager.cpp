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
	disxx::utility::pointer::NonNull<Manager> Manager::s_pInstance{new Manger{}};

	void Manager::MouseButtonCallback(int button, int state, int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;

		event::MouseButton event{utility::Vec2<float>{x, y}, button, state};
		this
			->m_Windows
			.at(hWin)
			.m_Events
			.push(event);
	}

	void MousePassiveMotionCallback(int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;
	
		event::MouseMotion event{utility::Vec2<float>{x, y}, true};
		this
			->m_Windows
			.at(hWin)
			.m_Events
			.push(event);
	}

	void MouseMotionCallback(int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;
	
		event::MouseMotion event{utility::Vec2<float>{x, y}, false};
		this
			->m_Windows
			.at(hWin)
			.m_Events
			.push(event);
	}

	void KeyboardCallback(unsigned char key, int, int) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;

		event::Keyboard event{key};
		this
			->m_Windows
			.at(hWin)
			.m_Events
			.push(event);
	}

	void ReshapeCallback(int x, int y) const noexcept
	{
		const auto hWin{glutGetWindow()};
		if (!this->m_Windows.contains(hWin)) [[unlikely]]
			return;
	
		event::Reshape event{utility::Vec2<float>{x, y}};
		this
			->m_Windows
			.at(hWin)
			.m_Events
			.push(event);
	}
	
	std::shared_ptr<abstract::Window> Manager::CreateWindow(void) noexcept
	{
		const auto hWin{glutCreateWindow("")};
		const auto ptr{std::make_shared<glut::Window>(hWin)};
		this->m_Windows[hWin] = ptr;

		return ptr;
	}

	void Manager::DestroyWindow(std::shared_ptr<abstract::Window<int>> ptr) noexcept
	{
		const auto hWin{ptr->GetHandle()};
		if (auto it{this->m_Windows.find(hWin)}; it != this->m_Windows.end()) [[likely]]
			this->m_Windows.erase(it);
		glutDestroyWindow(hWin);
	}

	void Manager::SetWindow(const std::shared_ptr<abstract::Window<int>> ptr) const noexcept
	{
		if (!ptr) [[unlikely]]
			return;
		
		glutSetWindow(ptr->GetHandle());
	}

	virtual std::shared_ptr<abstract::Window<int>> GetWindow(void) const noexcept { return this->m_Windows.at(glutGetWindow()); }

	void Manager::SetCallbacks(void) const noexcept
	{
		glutDisplayFunc(+[] -> void {});

		glutMouseFunc
		(
			+[](int button, int state, int x, int y) -> void
			{
				s_pInstace->MouseButtonCallback
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
			{ s_pInstace->ReshapeCallback(width, height); }
		);
	}
} /* disxx::ui::backend::glut */
