export module disxx.ui.backend.glut.Manager;

import disxx.ui.backend.abstract.IManager;
import disxx.ui.backend.abstract.Window;

import disxx.utility.pointer.NonNull;

export import std;

export namespace disxx::ui::backend::glut
{
	class __attribute__((visibility("default"))) [[nodiscard]] Manager final : public abstract::IManager
	<
		std::shared_ptr<abstract::Window<int>>,
		std::weak_ptr<abstract::Window<int>>
	>
	{
	  private:
		static disxx::utility::pointer::NonNull<Manager> s_pInstance;

	  private:
		// Windows and their handles
		std::map<int, Owned> m_Windows{};
		Weak m_pCurrentWindow{};
		
	  private:
		explicit Manager(void) = default;

		void MouseButtonCallback(int, int, int, int) const noexcept;
		void MousePassiveMotionCallback(int, int) const noexcept;
		void MouseMotionCallback(int, int) const noexcept;
		void KeyboardCallback(unsigned char, int, int) const noexcept;
		void ReshapeCallback(int, int) const noexcept;
		void WindowCloseCallback(void) const noexcept;

	  public:
		static inline disxx::utility::pointer::NonNull<Manager> &Get(void) noexcept;
	
	  public:
		Manager(const Manager &) noexcept = delete;
		Manager &operator=(const Manager &) = delete;

		Manager(Manager &&) noexcept = delete;
		Manager &operator=(Manager &&) noexcept = delete;

		[[clang::acquire_handle("Window")]] virtual Weak CreateWindow(void) noexcept override;
		virtual void DestroyWindow([[clang::release_handle("Window")]] Weak) noexcept override;

		virtual void SetWindow([[clang::use_handle("window")]] const Weak) noexcept override;
		virtual std::optional<Weak> GetWindow(void) const noexcept override;
	
		virtual void SetCallbacks(void) const noexcept override;
	};

	inline disxx::utility::pointer::NonNull<Manager> &Manager::Get(void) noexcept { return s_pInstance; }
} /* disxx::ui::backend::glut */
