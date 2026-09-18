export module disxx.ui.backend.abstract.IManager;

import disxx.ui.backend.event.Queue;
import disxx.utility.pointer.Pointer;
import disxx.utility.pointer.Weak;

import std;

export namespace disxx::ui::backend::abstract
{
	template <disxx::utility::pointer::Pointer T, disxx::utility::pointer::Weak<T> U>
	class __attribute__((visibility("default"))) [[nodiscard]] IManager
	{
	  public:
		using Owned = T;
		using Weak = U;

	  public:
		virtual ~IManager(void) noexcept = 0;

		[[clang::acquire_handle("Window")]] virtual Weak CreateWindow(void) noexcept = 0;
		virtual void DestroyWindow([[clang::release_handle("Window")]] Weak) noexcept = 0;

		virtual void SetWindow([[clang::use_handle("window")]] const Weak) noexcept = 0;
		virtual std::optional<Weak> GetWindow(void) const noexcept = 0;
	
		virtual void SetCallbacks(void) const noexcept = 0;
	};

	template <disxx::utility::pointer::Pointer T, disxx::utility::pointer::Weak<T> U>
	IManager<T, U>::~IManager(void) noexcept {}
} /* disxx::ui::backend::abstract */
