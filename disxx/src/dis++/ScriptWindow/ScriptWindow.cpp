module ScriptWindow;

import disxx.ui.MainWindow;
import disxx.ui.SourceEditor;

import ScriptEngine;

import std;

ScriptWindow::ScriptWindow(const std::filesystem::path &path) noexcept
	: m_Win{disxx::ui::utility::Vec2<int>{800, 600}, "dis++ - Ruby output"}
	, m_Engine{}
{
	this->m_Win.SetVisible(true);

	disxx::ui::SourceEditor field
	{
		800.f,
		600.f,
		0.f,
		0.f
	};
	field.SetColor(0.2f, 0.2f, 0.2f);
	for (const auto substr : this->m_Engine.ExecFile(path) | std::views::split('\n'))
		field.AddLine("{}", substr);
	this->m_Win.AddWidget(std::make_unique<disxx::ui::SourceEditor>(field));

	this->m_Win.Redisplay();
}

ScriptWindow::ScriptWindow(const ScriptWindow &other) noexcept
	: m_Win{other.m_Win}
	, m_Engine{other.m_Engine}
{}

ScriptWindow &ScriptWindow::operator=(const ScriptWindow &other) noexcept
{
	if (this != &other) [[likely]]
	{
		this->m_Win = other.m_Win;
		this->m_Engine = other.m_Engine;
	}

	return *this;
}

ScriptWindow::ScriptWindow(ScriptWindow &&other) noexcept
	: m_Win{std::move(other.m_Win)}
	, m_Engine{std::move(other.m_Engine)}
{}

ScriptWindow &ScriptWindow::operator=(ScriptWindow &&other) noexcept
{
	if (this != &other) [[likely]]
	{
		this->m_Win = std::move(other.m_Win);
		this->m_Engine = std::move(other.m_Engine);
	}

	return *this;
}
