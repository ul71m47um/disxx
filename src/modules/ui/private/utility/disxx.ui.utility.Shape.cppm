export module disxx.ui.utility.Shape;

import disxx.ui.utility.Renderable;

export namespace disxx::ui::utility
{
	class [[clang::type_visibility("hidden")]] [[nodiscard]] Shape final : public Renderable
	{
	  public:
		enum class Type
		{
			TYPE_TRIANGLE,
			TYPE_RECTANGLE
		};
 
	  private:
		Type m_ShapeType;

	  public:
		explicit Shape(void) noexcept;
		explicit Shape(Type) noexcept;
		
		explicit Shape(const Shape &) noexcept;
		Shape &operator=(const Shape &) noexcept;

		explicit Shape(Shape &&) noexcept;
		Shape &operator=(Shape &&) noexcept;

		inline Type GetShapeType(void) const noexcept;
	};

	inline Shape::Type Shape::GetShapeType(void) const noexcept
	{ return this->m_ShapeType; }
} /* disxx::ui::utility */
