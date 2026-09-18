export module disxx.ui.renderable.Renderable;

export import disxx.ui.utility.Vertex;
export import disxx.ui.utility.Vec;

export import std;

export namespace disxx::ui::renderable
{
	class __attribute__((visibility("default"))) [[nodiscard]] Renderable
	{
	  protected:
		utility::Vec3<float> m_Color{};
		utility::Vec2<float> m_Position{};
		utility::Vec2<float> m_Size{};

	  public:
		explicit Renderable(void) noexcept;

		Renderable(const Renderable &) noexcept;
		Renderable &operator=(const Renderable &) noexcept;

		Renderable(Renderable &&) noexcept;
		Renderable &operator=(Renderable &&) noexcept;

		virtual ~Renderable(void) noexcept = default;

		void Replace(utility::Vec2<float>) noexcept;
		void Resize(utility::Vec2<float>) noexcept;

		void SetColor(utility::Vec3<float>) noexcept;

		utility::Vec2<float> GetPosition(void) const noexcept;
		utility::Vec2<float> GetSize(void) const noexcept;
		utility::Vec3<float> GetColor(void) const noexcept;

		virtual std::vector<utility::Vertex<float>> GetVertices(void) const noexcept = 0;
	};
} /* disxx::ui::renderable */
