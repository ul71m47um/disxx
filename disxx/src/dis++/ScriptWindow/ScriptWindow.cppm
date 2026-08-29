export module ScriptWindow;

import disxx.ui.MainWindow;

import ScriptEngine;

import std;

export class ScriptWindow
{
  private:
	disxx::ui::MainWindow m_Win{};
	ScriptEngine m_Engine{};

  public:
	explicit ScriptWindow(const std::filesystem::path &) noexcept;

	ScriptWindow(const ScriptWindow &) noexcept;
	ScriptWindow &operator=(const ScriptWindow &) noexcept;

	ScriptWindow(ScriptWindow &&) noexcept;
	ScriptWindow &operator=(ScriptWindow &&) noexcept;
};
