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
} /* disxx::ui */
