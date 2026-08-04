export module Application;

import disxx.utility.error.NullPointerError;
import disxx.ui.MainWindow;
import disxx.ui.Widget;
import ScriptEngine;
import FileInput;
import DisLog;

export import std;

export class __attribute__((visibility("hidden"))) [[nodiscard]] Application
{
  private:
	static Application *s_pInstance;
	
  private:
	disxx::ui::MainWindow m_Window{};
	DisLog m_Logger{};
	FileInput m_pInput{};

  private:
	static void Init(void) noexcept(false);

  private:
	explicit Application(void) noexcept(false);
	
	Application(const Application &) noexcept(false) = delete;
	Application &operator=(const Application &) noexcept(false) = delete;

	void Disassemble(const std::filesystem::path &) noexcept(false);

  public:
	// THIS FUNCTION CALLS ONCE!
	[[clang::always_inline]] inline static Application *Init(int &, char **&) noexcept(false);
	
	~Application(void) noexcept = default;

	int Exec(void) const noexcept(false);
};

inline Application *Application::Init(int &argc, char **&argv) noexcept(false)
{
	// ScriptEngine should be defined first, so safety check is delayed
	ScriptEngine::Init(argc, argv);

	if (argv == nullptr || *argv == nullptr) [[unlikely]]
		throw disxx::utility::error::NullPointerError{"NullPointerError"};
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
