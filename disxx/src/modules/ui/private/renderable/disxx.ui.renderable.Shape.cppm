export module disxx.ui.renderable.Shape;

import disxx.ui.renderable.Renderable;

export namespace disxx::ui::renderable
{
	class __attribute__((visibility("default"))) [[nodiscard]] Shape : public Renderable
	{
	  public:
		explicit Shape(void) noexcept;
		
		Shape(const Shape &) noexcept;
		Shape &operator=(const Shape &) noexcept;

		Shape(Shape &&) noexcept;
		Shape &operator=(Shape &&) noexcept;
	};
} /* disxx::ui::renderable */
