module;

#ifdef __APPLE__
#	include <GLUT/glut.h>
#else
#	include <GL/freeglut.h>
#endif

module disxx.ui.backend.glut.Context;

import disxx.ui.backend.glut.Manager;
import disxx.ui.backend.glut.Window;
import disxx.ui.utility.Vec;

import disxx.utility.pointer.NonNull;

namespace disxx::ui::backend::glut
{
	disxx::utility::pointer::NonNull<Context> Context::s_pInstance{new Context{}};

	Context::WindowPointer Context::CreateWindow(utility::Vec2<int> size, std::string_view title) const noexcept
	{
		const auto ptr{Manager::Get()->CreateWindow()};
		ptr->SetTitle(title.data());
		ptr->SetSize(size);

		return std::make_shared<Window>(dynamic_cast<Window &>(*ptr));
	}
	Context::WindowPointer Context::CurrentWindow(void) const noexcept
	{ return std::make_shared<Window>(dynamic_cast<Window &>(*Manager::Get()->GetWindow())); }

	void Context::MakeCurrent(Context::WindowPointer ptr) const noexcept { Manager::Get()->SetWindow(ptr); }
	
	void Context::SwapBuffers(void) const noexcept { glutSwapBuffers(); }
	void Context::PollEvents(void) const noexcept { glutCheckLoop(); }
	void Context::Redisplay(void) const noexcept { glutPostRedisplay(); }
} /* disxx::ui::backend::glut */
