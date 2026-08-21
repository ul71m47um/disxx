export module FailHandler;

import disxx.utility.ini.Parser;
import disxx.ui.MainWindow;

export class __attribute__((visibility("hidden"))) [[nodiscard]] FailHandler
{
  private:
	static FailHandler *s_pInstance;

  private:
	disxx::ui::MainWindow m_Window{};
	disxx::utility::ini::Parser m_Parser{};

  private:
	explicit FailHandler(void) noexcept(false);
	
	FailHandler(const FailHandler &) noexcept(false) = delete;
	FailHandler &operator=(const FailHandler &) noexcept(false) = delete;

  public:
	// THIS FUNCTION CALLS ONCE!
	static FailHandler *Init(int &, char **&) noexcept(false);
	
	~FailHandler(void) noexcept = default;
	int Exec(void) const noexcept(false);
};
