module ScriptWindow;

import disxx.ui.MainWindow;
import disxx.ui.SourceEditor;

import ScriptEngine;

import std;

ScriptWindow::ScriptWindow(const std::filesystem::path &path)
	: m_Win{800, 600, std::format("Script - {}", path.string())}
	, m_Engine{}
{
	const auto result{this->m_Engine.LoadFile(path)};

	disxx::ui::SourceEditor field
	{
		800.f,
		600.f,
		0.f,
		0.f
	};
	field.SetColor(0.2f, 0.2f, 0.2f);
}

ScriptWindow::ScriptWindow(const ScriptWindow &other) noexcept
	: m_Win{other.m_Win}
{}
