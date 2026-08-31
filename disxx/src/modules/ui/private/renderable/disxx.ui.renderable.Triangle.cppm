export module disxx.ui.renderable.Triangle;

export import disxx.ui.utility.Vertex;
import disxx.ui.renderable.Shape;

export import std;

export namespace disxx::ui::renderable
{
	class __attribute__((visibility("default"))) [[nodiscard]] Triangle final : public Shape
	{
	  public:
		explicit Triangle(void) noexcept;

		Triangle(const Triangle &) noexcept;
		Triangle &operator=(const Triangle &) noexcept;

		Triangle(Triangle &&) noexcept;
		Triangle &operator=(Triangle &&) noexcept;

		virtual std::vector<utility::Vertex<float>> GetVertices(void) const noexcept override;
	};
} /* disxx::ui::renderable */
