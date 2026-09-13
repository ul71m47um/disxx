module disxx.ui.TreeItem;

namespace disxx::ui
{
	TreeItem::TreeItem(void) noexcept
		: Button{}
	{}

	TreeItem::TreeItem(std::string_view text) noexcept
		: Button{}	
	{ Button::SetText(text); }

	TreeItem::TreeItem(const TreeItem &other) noexcept
		: Button{other}
	{}

	TreeItem &TreeItem::operator=(const TreeItem &other) noexcept
	{
		if (this != &other) [[likely]]
			Button::operator=(other);
		return *this;
	}

	TreeItem::TreeItem(TreeItem &&other) noexcept
		: Button{std::forward<TreeItem &&>(other)}
	{}

	TreeItem &TreeItem::operator=(TreeItem &&other) noexcept
	{
		if (this != &other) [[likely]]
			Button::operator=(std::forward<TreeItem &&>(other));
		return *this;
	}
} /* disxx::ui */
