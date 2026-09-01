module;

#ifdef __APPLE__
#	include <GLUT/glut.h>
#else
#	include <GL/freeglut.h>
#endif

export module disxx.ui.backend.glut.Context;

import disxx.ui.backend.abstract.IContext;
import disxx.ui.backend.glut.Manager;
import disxx.ui.backend.glut.Window;
import disxx.ui.utility.Vec;

import disxx.utility.pointer.NonNull;

export import std;

export namespace disxx::ui::backend::glut
{
	class __attribute__((visibility("default"))) [[nodiscard]] Context final : public abstract::IContext<std::shared_ptr<Window>>
	{
	  public:
		using WindowPointer = std::shared_ptr<Window>;

	  private:
		static disxx::utility::pointer::NonNull<Context> s_pInstance;

	  public:
		template <typename ...Args> static void Init(Args &&...) noexcept;
		static inline disxx::utility::pointer::NonNull<Context> &Get(void) noexcept;

	  private:
		explicit Context(void) noexcept = default;

	  public:
		Context(const Context &) noexcept = delete;
		Context &operator=(const Context &) noexcept = delete;

		Context(Context &&) noexcept = delete;
		Context &operator=(Context &&) noexcept = delete;

		virtual ~Context(void) noexcept override = default;

		virtual WindowPointer CreateWindow(utility::Vec2<int>, std::string_view) const noexcept override;
		virtual WindowPointer CurrentWindow(void) const noexcept override;
		virtual void MakeCurrent(WindowPointer) const noexcept override;

		virtual void SwapBuffers(void) const noexcept override;
		virtual void PollEvents(void) const noexcept override;
		virtual void Redisplay(void) const noexcept override;
	};

	template <typename ...Args> void Context::Init(Args &&...args) noexcept
	{
		if constexpr (sizeof...(args) == 0)
		{
			int argc{0};
			#pragma clang diagnostic push
			#pragma clang diagnostic ignored "-Wbraced-scalar-init"
			#pragma clang diagnostic ignored "-Wwritable-strings"
			char *argv[]{{""}};
			#pragma clang diagnostic pop
			glutInit(&argc, argv);
		}
		else if constexpr (sizeof...(args) == 2)
			glutInit(std::forward<Args>(args)...);
		else
		{
			static_assert
			(
				false,
				std::format
				(
					"Incorrect arguments for {}",
					std::source_location{}
						.function_name()
				)
			);
		}

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

		Manager::Get()->SetCallbacks();
	}

	inline disxx::utility::pointer::NonNull<Context> &Context::Get(void) noexcept { return s_pInstance; }
} /* disxx::ui::backend::glut */
