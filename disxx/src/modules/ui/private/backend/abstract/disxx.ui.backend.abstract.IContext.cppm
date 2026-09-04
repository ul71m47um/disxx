export module disxx.ui.backend.abstract.IContext;

export import disxx.ui.utility.Vec;

export import std;

export namespace disxx::ui::backend::abstract
{
	template <typename T>
	concept Pointer = requires(T ptr)
	{
		{ ptr == nullptr } -> std::same_as<bool>;
		{ ptr = T{} } -> std::same_as<T &>;
		{ T{ptr} } -> std::same_as<T>;
		{ *ptr };
	};

	template <Pointer T>
	class __attribute__((visibility("hidden"))) [[nodiscard]] IContext
	{
	  public:
		using WindowPointer = T;

	  public:
		virtual ~IContext(void) noexcept = 0;

		virtual WindowPointer CreateWindow(utility::Vec2<int>, std::string_view) const noexcept = 0;
		virtual WindowPointer CurrentWindow(void) const noexcept = 0;
		virtual void MakeCurrent(WindowPointer) const noexcept = 0;

		virtual void SwapBuffers(void) const noexcept = 0;
		virtual void PollEvents(void) const noexcept = 0;
	};

	template <Pointer T>
	IContext<T>::~IContext(void) noexcept {}
} /* disxx::ui::backend::abstract */
