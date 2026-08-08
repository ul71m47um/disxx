module;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#pragma clang diagnostic ignored "-Wdocumentation-deprecated-sync"
#pragma clang diagnostic ignored "-Wheader-hygiene"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wundef"
#ifdef __APPLE__
#	include <Ruby/ruby.h>
#else
#	include <ruby.h>
#endif
#pragma clang diagnostic pop

export module ScriptEngine;

export import std;

export class ScriptEngine
{
  private:
	VALUE m_Disxx{};
	VALUE m_Loader{};
	VALUE m_ExecutableFile{};
	VALUE m_Section{};
	VALUE m_Label{};
	VALUE m_Disassembler{};

  public:
	[[clang::always_inline]] static inline void Init(int &argc, char **&argv) noexcept;
	static inline void ShutDown(void) noexcept;

  public:
	class EngineError final : public std::exception
	{
	  private:
		std::string m_Err{};

	  public:
		explicit EngineError(void) noexcept;
		explicit EngineError(std::string_view) noexcept;

		EngineError(const EngineError &) noexcept;
		EngineError &operator=(const EngineError &) noexcept;

		EngineError(EngineError &&) noexcept;
		EngineError &operator=(EngineError &&) noexcept;

		virtual ~EngineError(void) noexcept override = default;

		virtual const char *what(void) const noexcept override;
	};

  public:
	using ExecResult = std::expected<std::monostate, EngineError>;

  public:
	explicit ScriptEngine(void) noexcept;

	ScriptEngine(const ScriptEngine &) noexcept = delete;
	ScriptEngine &operator=(const ScriptEngine &) noexcept = delete;

	ScriptEngine(ScriptEngine &&) noexcept = delete;
	ScriptEngine &operator=(ScriptEngine &&) noexcept = delete;

	~ScriptEngine(void) noexcept = default;

	ExecResult ExecFile(const std::filesystem::path &) noexcept;
	ExecResult ExecString(std::string_view) noexcept;
};

[[clang::always_inline]] inline void ScriptEngine::Init(int &argc, char **&argv) noexcept
{
	RUBY_INIT_STACK

	ruby_sysinit(&argc, &argv);
    ruby_init();
    ruby_init_loadpath();
}

inline void ScriptEngine::ShutDown(void) noexcept
{ ruby_cleanup(0); }
