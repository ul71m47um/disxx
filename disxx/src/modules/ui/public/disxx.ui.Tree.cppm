export module disxx.ui.Tree;

import disxx.ui.Widget;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] Tree final : public Widget
	{
	  private:
		std::vector<std::unique_ptr<Widget>> m_Widgets{};
		std::string m_Text{};

	  public:
		explicit Tree(void) noexcept;
		explicit Tree(float, float, float, float) noexcept;

		Tree(const Tree &) noexcept;
		Tree &operator=(const Tree &) noexcept;

		Tree(Tree &&) noexcept;
		Tree &operator=(Tree &&) noexcept;

		inline void Push(std::unique_ptr<Widget> &&) noexcept;
	
		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void Render(void) const noexcept override;
	};
} /* disxx::ui */
