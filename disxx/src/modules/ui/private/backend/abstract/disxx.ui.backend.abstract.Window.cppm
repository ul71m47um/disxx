export module disxx.ui.backend.abstract.Window;

import disxx.ui.backend.event.Queue;
import disxx.ui.utility.Vec;

import std;

export namespace disxx::ui::backend::abstract
{
	template <typename T>
	class __attribute__((visibility("hidden"))) Window
	{
	  public:
		using Handle = T;

	  private:
		event::Queue m_Events{};
		Handle m_hWin{};
	
	  public:
		explicit Window(void) noexcept
			requires std::is_default_constructible<Handle>::value = default;
		explicit Window(Handle &) noexcept
			requires std::is_copy_constructible<Handle>::value;
	
		Window(const Window &) noexcept(std::is_nothrow_copy_constructible<Handle>::value)
			requires std::is_copy_constructible<Handle>::value = default;
		Window(const Window &) noexcept(std::is_nothrow_copy_constructible<Handle>::value)
			requires (!std::is_copy_constructible<Handle>::value) = delete;
	
		Window &operator=(const Window &) noexcept(std::is_nothrow_copy_assignable<Handle>::value)
			requires std::is_copy_assignable<Handle>::value = default;
		Window &operator=(const Window &) noexcept(std::is_nothrow_copy_assignable<Handle>::value)
			requires (!std::is_copy_assignable<Handle>::value) = delete;
	
		virtual ~Window(void) noexcept = 0;
		virtual void Destroy(void) noexcept = 0;

		inline Handle &GetHandle(void) const noexcept;
	
		virtual void Iconify(void) noexcept = 0;
	
		virtual void Show(void) noexcept = 0;
		virtual void Hide(void) noexcept = 0;
	
		virtual void Push(void) noexcept = 0;
		virtual void Pop(void) noexcept = 0;
	
		virtual void SetTitle(std::string_view) noexcept = 0;
		virtual void SetSize(utility::Vec2<int>) noexcept = 0;
	
		virtual utility::Vec2<int> GetSize(void) const noexcept = 0;
	
		virtual bool ShouldClose(void) const noexcept = 0;

		virtual int Exec(std::function<int(event::Queue &)>) noexcept = 0;
	};

	template <typename T>
	inline Window<T>::Handle &Window<T>::GetHandle(void) const noexcept { return this->m_hWin; }
} /* disxx::ui::backend::abstract */
