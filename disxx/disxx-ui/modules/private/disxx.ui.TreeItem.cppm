export module disxx.ui.TreeItem;

import disxx.ui.Button;

import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] TreeItem final : public Button
	{
	  public:
		explicit TreeItem(void) noexcept;
		explicit TreeItem(std::string_view) noexcept;

		TreeItem(const TreeItem &) noexcept;
		TreeItem &operator=(const TreeItem &) noexcept;

		TreeItem(TreeItem &&) noexcept;
		TreeItem &operator=(TreeItem &&) noexcept;
	};
} /* disxx::ui */
