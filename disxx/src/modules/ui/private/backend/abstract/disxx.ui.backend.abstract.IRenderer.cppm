export module disxx.ui.backend.abstract.IRenderer;

export import disxx.ui.renderable.Renderable;

export import std;

export namespace disxx::ui::backend::abstract
{
	class __attribute__((visibility("default"))) [[nodiscard]] IRenderer
	{
	  public:
		virtual void Push(std::unique_ptr<renderable::Renderable> &&) noexcept = 0;
		virtual void Pop(void) noexcept = 0;		
		
		virtual void ClearBuffer(void) noexcept = 0;
		virtual void Render(void) noexcept = 0;
	};
} /* disxx::ui::backend::abstract */
