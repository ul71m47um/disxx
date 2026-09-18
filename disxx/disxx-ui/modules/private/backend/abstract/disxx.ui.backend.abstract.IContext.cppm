export module disxx.ui.backend.abstract.IContext;

export import disxx.ui.utility.Vec;

export import std;

import disxx.utility.pointer.Pointer;
import disxx.utility.pointer.Weak;

export namespace disxx::ui::backend::abstract
{
	template <disxx::utility::pointer::Pointer T, disxx::utility::pointer::Weak<T> U>
	class __attribute__((visibility("hidden"))) [[nodiscard]] IContext
	{
	  public:
		using WindowPointer = U;

	  public:
		virtual ~IContext(void) noexcept = 0;

		virtual WindowPointer CreateWindow(utility::Vec2<int>, std::string_view) const noexcept = 0;
		virtual std::optional<WindowPointer> CurrentWindow(void) const noexcept = 0;
		virtual void MakeCurrent(WindowPointer) const noexcept = 0;

		virtual void SwapBuffers(void) const noexcept = 0;
		virtual void PollEvents(void) const noexcept = 0;
	};

	template <disxx::utility::pointer::Pointer T, disxx::utility::pointer::Weak<T> U>
	IContext<T, U>::~IContext(void) noexcept {}
} /* disxx::ui::backend::abstract */
