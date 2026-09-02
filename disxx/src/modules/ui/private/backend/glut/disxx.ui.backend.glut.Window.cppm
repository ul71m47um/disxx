module;

#ifdef __APPLE__
#	include <GLUT/glut.h>
#else
#	include <GL/freeglut.h>
#endif

export module disxx.ui.backend.glut.Window;

export import disxx.ui.backend.event.Queue;
import disxx.ui.backend.abstract.Window;
import disxx.ui.backend.glut.Manager;
import disxx.ui.utility.Vec;

export namespace disxx::ui::backend::glut
{
	class __attribute__((visibility("default"))) [[nodiscard]] Window final : public abstract::Window<int>
	{
	  friend class Manager;

	  public:
		explicit Window(void) noexcept = default;
		explicit Window(const Handle &) noexcept;

		Window(const Window &) noexcept = default;
		Window &operator=(const Window &) noexcept = default;

		virtual ~Window(void) noexcept override;
		virtual void Destroy(void) noexcept override;

		virtual void Iconify(void) noexcept override;

		virtual void Show(void) noexcept override;
		virtual void Hide(void) noexcept override;

		virtual void Push(void) noexcept override;
		virtual void Pop(void) noexcept override;

		virtual void SetTitle(std::string_view) noexcept override;
		virtual void SetSize(utility::Vec2<int>) noexcept override;

		virtual utility::Vec2<int> GetSize(void) const noexcept override;

		virtual bool ShouldClose(void) const noexcept override;
	
		virtual int Exec(std::function<int(event::Queue &)>) noexcept override;
	};
} /* disxx::ui::backend */
