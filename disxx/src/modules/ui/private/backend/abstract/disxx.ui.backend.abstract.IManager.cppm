export module disxx.ui.backend.abstract.IManager;

import disxx.ui.backend.event.Queue;
import disxx.utility.pointer.NonNull;

import std;

export namespace disxx::ui::backend::abstract
{
	template <typename T>
	concept Pointer = requires(T ptr)
	{
		{ ptr == nullptr } -> std::same_as<bool>;
		{ ptr = T{} } -> std::same_as<T &>;
		{ T{ptr} } -> std::same_as<T>; // Check if it's copyable
		{ *ptr };
	};

	template <Pointer T>
	class __attribute__((visibility("default"))) [[nodiscard]] IManager
	{
	  public:
		virtual ~IManager(void) noexcept = 0;

		[[clang::acquire_handle("Window")]] virtual T CreateWindow(void) noexcept = 0;
		virtual void DestroyWindow([[clang::release_handle("Window")]] T) noexcept = 0;

		virtual void SetWindow([[clang::use_handle("window")]] const T) const noexcept = 0;
		virtual T GetWindow(void) const noexcept = 0;
	
		virtual void SetCallbacks(void) const noexcept = 0;
	};

	template <Pointer T>
	IManager<T>::~IManager(void) noexcept {}
} /* disxx::ui::backend::abstract */
