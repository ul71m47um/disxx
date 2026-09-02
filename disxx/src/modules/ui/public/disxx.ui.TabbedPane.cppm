export module disxx.ui.TabbedPane;

import disxx.ui.Widget;
export import disxx.ui.Tab;

export import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] TabbedPane final : public Widget
	{
	  private:
		std::vector<Tab> m_Tabs{};
		std::function<void(Tab &)> m_Callback{};

	  public:
		explicit TabbedPane(void) noexcept;
		explicit TabbedPane(float, float, float, float) noexcept;

		TabbedPane(const TabbedPane &) noexcept;
		TabbedPane &operator=(const TabbedPane &) noexcept;

		TabbedPane(TabbedPane &&) noexcept;
		TabbedPane &operator=(TabbedPane &&) noexcept;

		inline void Push(Tab &&) noexcept;
		inline void Pop(void) noexcept;

		inline std::optional<std::reference_wrapper<const Tab>> GetActiveTab(void) const noexcept;
		inline const std::vector<Tab> &GetTabs(void) const noexcept;
		inline std::vector<Tab> &GetTabs(void) noexcept;

		inline void SetTabClickCallback(std::function<void(Tab &)>) noexcept;

		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;

		virtual void Render(void) const noexcept override;
		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void MouseMotionCallback(backend::event::MouseMotion) noexcept override;
	};

	inline void TabbedPane::Push(Tab &&tab) noexcept
	{
		this->m_Tabs.push_back(std::forward<Tab &&>(tab));
		
		for (const auto i : std::views::iota(0ul, this->m_Tabs.size()))
		{
			auto &iTab{this->m_Tabs[i]};
			iTab.Replace
			(
				utility::Vec2<float>
				{
					this->m_Position.x
						+ (this->m_Size.x / static_cast<float>(this->m_Tabs.size()))
						* static_cast<float>(i),
					this->m_Size.y * 0.95f
				}
			);
			iTab.Resize
			(
				utility::Vec2<float>
				{
					(this->m_Size.x / static_cast<float>(this->m_Tabs.size())),
					this->m_Size.y * 0.05f
				}
			);
			
			auto &area{iTab.GetTextArea()};
			area.Replace(utility::Vec2<float>{this->m_Position.x, this->m_Position.y});
			area.Resize(utility::Vec2<float>{this->m_Size.x, this->m_Size.y * 0.95f});
		}
	}

	inline void TabbedPane::SetTabClickCallback(std::function<void(Tab &)> callback) noexcept
	{ this->m_Callback = callback; }

	inline void TabbedPane::Pop(void) noexcept
	{
		if (this->m_Tabs.size() > 0) [[likely]]
			this->m_Tabs.pop_back();
	}

	inline std::optional<std::reference_wrapper<const Tab>> TabbedPane::GetActiveTab(void) const noexcept
	{
		for (const auto &tab : this->m_Tabs)
			if (tab.Clicked())
				return std::cref(tab);
		return std::nullopt;
	}

	inline const std::vector<Tab> &TabbedPane::GetTabs(void) const noexcept
	{ return this->m_Tabs; }

	inline std::vector<Tab> &TabbedPane::GetTabs(void) noexcept
	{ return this->m_Tabs; }
} /* disxx::ui */
