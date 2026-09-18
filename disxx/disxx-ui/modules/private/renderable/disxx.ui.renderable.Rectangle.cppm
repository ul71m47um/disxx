export module disxx.ui.renderable.Rectangle;

export import disxx.ui.utility.Vertex;
import disxx.ui.renderable.Shape;

export import std;

export namespace disxx::ui::renderable
{
	class __attribute__((visibility("default"))) [[nodiscard]] Rectangle final : public Shape
	{
	  public:
		explicit Rectangle(void) noexcept;
		
		Rectangle(const Rectangle &) noexcept;
		Rectangle &operator=(const Rectangle &) noexcept;

		Rectangle(Rectangle &&) noexcept;
		Rectangle &operator=(Rectangle &&) noexcept;

		virtual std::vector<utility::Vertex<float>> GetVertices(void) const noexcept override;
	};
} /* disxx::ui::renderable */
