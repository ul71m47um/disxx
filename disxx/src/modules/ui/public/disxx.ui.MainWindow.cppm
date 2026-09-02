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
		inline void SetVisible(bool) noexcept;
		inline void AddWidget(std::unique_ptr<Widget> &&) noexcept;
		inline std::vector<std::unique_ptr<Widget>> &GetWidgets(void) noexcept;
		inline void Redisplay(void) const noexcept;
	
		template <typename F> requires std::is_function<F>::value
		int Exec(F &&) noexcept;
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
	{ return utility::Vec2<int>{this->m_Size}; }

	inline void MainWindow::SetVisible(bool visible) noexcept
	{
		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
		if (visible)
			this->m_pWin->Show();
		else
			this->m_pWin->Hide();
	}

	inline void MainWindow::AddWidget(std::unique_ptr<Widget> &&pWidget) noexcept
	{ this->m_Widgets.emplace_back(std::move(pWidget)); }

	inline std::vector<std::unique_ptr<Widget>> &MainWindow::GetWidgets(void) noexcept
	{ return this->m_Widgets; }

	inline void MainWindow::Redisplay(void) const noexcept
	{
		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
		backend::glut::Context::Get()->Redisplay();
	}

	template <typename F> requires std::is_function<F>::value
	int MainWindow::Exec(F &&func) noexcept
	{
		const auto &pCtx{backend::glut::Context::Get()};
		return this->m_pWin->Exec
		(
			[this, &pCtx, &func](auto &events) mutable -> void
			{
				while (!this->m_pWin->ShouldClose())
				{
					pCtx->PollEvents();

					events.Visit
					(
						disxx::utility::Overload
						{
							[this, &pCtx](backend::event::MouseButton event) mutable -> void
							{
								pCtx->MakeCurrent(this->m_pWin);

								for (const auto i : std::views::iota(0ul, this->m_Widgets.size()))
									if (auto &pWidget{this->m_Widgets.at(i)}; pWidget->Visible())
										pWidget->MouseButtonCallback(event);
								pCtx->Redisplay();
							},
							[this, &pCtx](backend::event::MouseMotion event) mutable -> void
							{
								pCtx->MakeCurrent(this->m_pWin);

								for (const auto i : std::views::iota(0ul, this->m_Widgets.size()))
									if (auto &pWidget{this->m_Widgets.at(i)}; pWidget->Visible())
										pWidget->MouseMotionCallback(event);
								pCtx->Redisplay();
							},
							[this, &pCtx](backend::event::Keyboard event) mutable -> void 
							{
								pCtx->MakeCurrent(this->m_pWin);

								for (const auto i : std::views::iota(0ul, this->m_Widgets.size()))
									if (auto &pWidget{this->m_Widgets.at(i)}; pWidget->Visible())
										pWidget->KeyboardCallback(event);
								pCtx->Redisplay();
							},
							[this, &pCtx](backend::event::Reshape event) mutable -> void
							{
								pCtx->MakeCurrent(this->m_pWin);

								auto sX{static_cast<float>(this->m_Size.x) / static_cast<float>(this->m_InitialSize.x)};
								auto sY{static_cast<float>(this->m_Size.y) / static_cast<float>(this->m_InitialSize.y)};
	
								const auto [width, height]{event.GetSize()};
								this->m_Size = utility::Vec2<int>
								{
									static_cast<int>(width),
									static_cast<int>(height)
								};

								for (const auto &pWidget : this->m_Widgets)
								{
									const auto [x, y]{pWidget->GetPosition()};
									const auto [w, h]{pWidget->GetSize()};

									pWidget->Replace(utility::Vec2<float>{x * sX, y * sY});
									pWidget->Resize(utility::Vec2<float>{w * sX, h * sY});
								}

								pCtx->Redisplay();
							}
						}
					);

					// User's code
					func();

					pCtx->SwapBuffers();
				}
			}
		);
	}
} /* disxx::ui */
