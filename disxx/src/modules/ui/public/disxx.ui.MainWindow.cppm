export module disxx.ui.MainWindow;

export import disxx.ui.utility.Vec;

import disxx.ui.backend.glut.Context;
import disxx.ui.backend.glut.Window;
import disxx.ui.Widget;

import disxx.utility.pointer.NonNull;
import disxx.utility.Overload;

export import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] MainWindow
	{
	  private:
		std::vector<std::unique_ptr<Widget>> m_Widgets{};
		utility::Vec2<int> m_InitialSize{};
		utility::Vec2<int> m_Size{};
		#if defined(BACKEND_CTX_GLUT)
			std::shared_ptr<backend::glut::Window> m_pWin{};
		#else
		#	error "Context required"
		#endif

	  public:
		template <typename ...Args>
		static void Init(Args &&...) noexcept;

	  public:
		explicit MainWindow(void) noexcept;
		explicit MainWindow(utility::Vec2<int>, std::string_view) noexcept;

		MainWindow(const MainWindow &) noexcept;
		MainWindow &operator=(const MainWindow &) noexcept;

		MainWindow(MainWindow &&) noexcept;
		MainWindow &operator=(MainWindow &&) noexcept;

		~MainWindow(void) noexcept = default;

		inline utility::Vec2<int> GetSize(void) const noexcept;
	
		inline void SetSize(utility::Vec2<int>) noexcept;
		inline void SetTitle(std::string_view) noexcept;
		inline void SetVisible(bool) noexcept;
		
		inline void AddWidget(std::unique_ptr<Widget> &&) noexcept;
		inline std::vector<std::unique_ptr<Widget>> &GetWidgets(void) noexcept;
	
		int Exec(void) noexcept;
	};

	template <typename ...Args>
	void MainWindow::Init(Args &&...args) noexcept
	{
		#if defined(BACKEND_CTX_GLUT)
			backend::glut::Context::Init(std::forward<Args>(args)...);
		#else
		#	error "Context required"
		#endif
	}

	inline utility::Vec2<int> MainWindow::GetSize(void) const noexcept
	{
		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
		return utility::Vec2<int>{this->m_Size};
	}

	inline void MainWindow::SetSize(utility::Vec2<int> size) noexcept
	{ this->m_pWin->SetSize(size); }

	inline void MainWindow::SetTitle(std::string_view title) noexcept
	{ this->m_pWin->SetTitle(title); }

	inline void MainWindow::SetVisible(bool visible) noexcept
	{
		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
		if (visible)
			this->m_pWin->Show();
		else
			this->m_pWin->Hide();
	}

	inline void MainWindow::AddWidget(std::unique_ptr<Widget> &&pWidget) noexcept
	{
		this->m_Widgets.emplace_back(std::move(pWidget));
		//backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
		//backend::glut::Context::Get()->Redisplay();
	}

	inline std::vector<std::unique_ptr<Widget>> &MainWindow::GetWidgets(void) noexcept
	{ return this->m_Widgets; }
} /* disxx::ui */
