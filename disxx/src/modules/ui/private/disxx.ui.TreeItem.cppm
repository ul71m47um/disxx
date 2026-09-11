export module disxx.ui.TreeItem;

import disxx.ui.Widget;

import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] TreeItem final : public Widget
	{
	  private:
		std::function<void(void)> m_Callback{};
		std::string m_Text{};

	  public:
		explicit TreeItem(void) noexcept;
		explicit TreeItem(std::string_view) noexcept;

		TreeItem(const TreeItem &) noexcept;
		TreeItem &operator(const TreeItem &) noexcept;

		TreeItem(TreeItem &&) noexcept;
		TreeItem &operator=(TreeItem &&) noexcept;

		inline void SetCallback(std::function<void(void)>) noexcept;
		
		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void Render(void) const noexcept override;
	};

	inline TreeItem::SetCallback(std::function<void(void)> callback) noexcept
	{ this->m_Callback = callback; }
} /* disxx::ui */
