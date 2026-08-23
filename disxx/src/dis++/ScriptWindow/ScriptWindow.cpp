module ScriptWindow;

import std;

ScriptWindow::ScriptWindow(void) noexcept
	: m_Win{"Script window"}
	, m_Engine{}
{}

ScriptWindow::ScriptWindow(const std::filesystem::path &path)
	: m_Win{std::format("Script - {}", path.string())}
	, m_Engine{}
{ this->m_Engine.LoadFile(path); }

ScriptWindow::ScriptWindow(const ScriptWindow &other) noexcept
	: m_Win{other.m_Win}
{}
