export module disxx.ui.Tree;

export import disxx.ui.TreeItem;
import disxx.ui.Button;
import disxx.ui.Widget;

export import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] Tree final : public Button
	{
	  private:
		std::vector<std::unique_ptr<Widget>> m_Widgets{};

	  private:
		void Relayout(void) noexcept;

	  public:
		explicit Tree(void) noexcept;
		explicit Tree(float, float, float, float) noexcept;

		Tree(const Tree &) noexcept;
		Tree &operator=(const Tree &) noexcept;

		Tree(Tree &&) noexcept;
		Tree &operator=(Tree &&) noexcept;

		inline unsigned long int GetChildrenCount(void) const noexcept;

		inline void Push(std::unique_ptr<Widget> &&) noexcept;
		inline void Pop(void) noexcept;

		virtual void Replace(utility::Vec2<float>) noexcept override;
		virtual void SetText(std::string_view) noexcept override;
		virtual utility::Vec2<float> GetSize(void) const noexcept override;
		
		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void Render(void) const noexcept override;
	};

	inline unsigned long int Tree::GetChildrenCount(void) const noexcept { return this->m_Widgets.size(); }

	inline void Tree::Push(std::unique_ptr<Widget> &&ptr) noexcept
	{
		if (!ptr) [[unlikely]]
			return;

		ptr->SetVisible(this->m_bClicked);
		this->m_Widgets.emplace_back(std::forward<std::unique_ptr<Widget> &&>(ptr));

		this->Relayout();
	}

	inline void Tree::Pop(void) noexcept
	{
		if (this->m_Widgets.size() > 0) [[likely]]
		{
			this->m_Widgets.pop_back();
			this->Relayout();	
		}
	}
} /* disxx::ui */
