export module Application;

import disxx.utility.error.NullPointerError;

import disxx.ui.MainWindow;
import disxx.ui.SourceEditor;
import disxx.ui.TabbedPane;
import disxx.ui.Widget;

import ScriptWindow;
import ScriptEngine;
import DisLog;

export import std;

export class __attribute__((visibility("hidden"))) [[nodiscard]] Application
{
  private:
	static Application *s_pInstance;
	
  private:
	disxx::ui::MainWindow m_Window{};
	disxx::ui::SourceEditor *m_pLabels;
	disxx::ui::TabbedPane *m_pTabs;
	std::vector<disxx::ui::Widget *> m_ModalWidgets{};
	std::vector<ScriptWindow> m_ScriptWindows{};
	DisLog m_Logger{};
	bool m_bActiveModal{};

  private:
	static void Init(void) noexcept;

  private:
	explicit Application(void) noexcept;
	
	Application(const Application &) noexcept = delete;
	Application &operator=(const Application &) noexcept = delete;

	void MainMenu(void) noexcept;
	void Setup(std::filesystem::path) noexcept;
	void LoadLabels(const std::filesystem::path &) noexcept;
	void Disassemble(const std::filesystem::path &) noexcept;
	void RequestFile(std::string_view, std::string_view, std::function<void(std::filesystem::path)>) noexcept;
	void ClearModal(void) noexcept;

  public:
	// THIS FUNCTION CALLS ONCE!
	[[clang::always_inline]] inline static Application *Init(int &, char **&) noexcept;
	
	~Application(void) noexcept = default;

	inline int Exec(void) const noexcept;
};

inline Application *Application::Init(int &argc, char **&argv) noexcept
{
	ScriptEngine::Init(argc, argv);

	if (argv == nullptr || *argv == nullptr) [[unlikely]]
		return nullptr;
	
	disxx::ui::MainWindow::Init(&argc, argv);
    
	if (!s_pInstance) [[likely]]
        s_pInstance = new Application{};

	static auto &sArgc{argc};
	static auto &sArgv{argv};
	std::set_terminate
	(
		[] -> void
		{
			Application::s_pInstance->m_Window.SetVisible(false);

			Application::s_pInstance->m_Logger.LogErr
			(
				sArgc && sArgv
					? sArgv[0]
					: "unknown"
			);
		
			std::string path
			{
				std::filesystem::path
				{
					sArgc && sArgv
						? sArgv[0]
						:
						#ifdef _WIN32
							".\\dis++"
						#else
							"./dis++"
						#endif
				}
				.parent_path()
				.string()
				+ std::filesystem::path::preferred_separator
				+ "reporter"
			};

			std::system(path.c_str());
			std::exit(1);
		}
	);

	return s_pInstance;
}

inline int Application::Exec(void) const noexcept { return this->m_Window.Exec(); }
