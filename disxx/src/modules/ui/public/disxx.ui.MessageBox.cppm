export module disxx.ui.MessageBox;

import disxx.ui.MainWindow;

export import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] MessageBox
	{
	  private:
		MainWindow m_Win{};

	  public:
		explicit MessageBox(void) noexcept;
		explicit MessageBox(std::string_view) noexcept;

		MessageBox(const MessageBox &) noexcept;
		MessageBox &operator=(const MessageBox &other) noexcept;

		MessageBox(MessageBox &&) noexcept;
		MessageBox &operator=(MessageBox &&) noexcept;

		inline int Exec(void) const noexcept;
	};

	inline int MessageBox::Exec(void) const noexcept
	{
		this->m_Win.Exec();
		return 0;
	}
} /* disxx::ui */
