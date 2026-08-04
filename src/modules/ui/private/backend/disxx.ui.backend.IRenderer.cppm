export module disxx.ui.backend.IRenderer;

export import disxx.ui.utility.Renderable;

export import std;

export namespace disxx::ui::backend
{
	class __attribute__((visibility("default"))) [[nodiscard]] IRenderer
	{
	  public:
		virtual void Push(std::unique_ptr<utility::Renderable> &&) noexcept = 0;
		virtual void Pop(void) noexcept = 0;		
		
		virtual void ClearBuffer(void) noexcept = 0;
		virtual void Render(void) noexcept = 0;
	};
} /* disxx::ui::backend */
