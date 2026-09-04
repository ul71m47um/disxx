module disxx.ui.MainWindow;

namespace disxx::ui
{
	MainWindow::MainWindow(void) noexcept
		: m_Widgets{}
		, m_InitialSize{}
		, m_Size{}
		, m_pWin{nullptr}
	{
		this->m_pWin = backend::glut::Context::Get()->CreateWindow(utility::Vec2<int>{this->m_Size}, "");
		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
	}

	MainWindow::MainWindow(utility::Vec2<int> size, std::string_view title) noexcept
		: m_Widgets{}
		, m_InitialSize{utility::Vec2<int>{size}}
		, m_Size{size}
		, m_pWin{nullptr}
	{
		this->m_pWin = backend::glut::Context::Get()->CreateWindow(utility::Vec2<int>{this->m_Size}, title);
		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
	}

	MainWindow::MainWindow(const MainWindow &other) noexcept
		: m_Widgets{}
		, m_InitialSize{utility::Vec2<int>{other.m_InitialSize}}
		, m_Size{other.m_Size}
		, m_pWin{nullptr}
	{
		for (const auto &pWidget : other.m_Widgets)
			this->m_Widgets.emplace_back(pWidget->Clone());

		this->m_pWin = backend::glut::Context::Get()->CreateWindow(utility::Vec2<int>{this->m_Size}, "Copy");
		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);
	}

	MainWindow &MainWindow::operator=(const MainWindow &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			for (const auto &pWidget : other.m_Widgets)
				this->m_Widgets.emplace_back(pWidget->Clone());
			this->m_InitialSize = other.m_InitialSize;
			this->m_Size = other.m_Size;
		}

		return *this;
	}

	MainWindow::MainWindow(MainWindow &&other) noexcept
		: m_Widgets{std::move(other.m_Widgets)}
		, m_InitialSize{std::move(utility::Vec2<int>{other.m_InitialSize})}
		, m_Size{std::move(other.m_Size)}
		, m_pWin{std::move(other.m_pWin)}
	{ backend::glut::Context::Get()->MakeCurrent(this->m_pWin); }

	MainWindow &MainWindow::operator=(MainWindow &&other) noexcept
	{
		if (this != &other) [[likely]]
		{
			this->m_Widgets = std::move(other.m_Widgets);
			this->m_InitialSize = std::move(other.m_InitialSize);
			this->m_Size = std::move(other.m_Size);
			this->m_pWin = std::move(other.m_pWin);
		}

		backend::glut::Context::Get()->MakeCurrent(this->m_pWin);

		return *this;
	}

	int MainWindow::Exec(void) noexcept
	{
		const auto &pCtx{backend::glut::Context::Get()};
		return this->m_pWin->Exec
		(
			[this, &pCtx](auto &events) mutable -> int
			{
				while (!this->m_pWin->ShouldClose())
				{
					pCtx->PollEvents();

					events.Visit
					(
						#pragma clang diagnostic push
						#pragma clang diagnostic ignored "-Wctad-maybe-unsupported"
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

					for (const auto &pWidget : this->m_Widgets)
						pWidget->Render();

					pCtx->SwapBuffers();
				}
			
				return 0;
			}
		);
	}
} /* disxx::ui */
