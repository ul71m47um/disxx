export module disxx.ui.renderable.Text;

import disxx.ui.renderable.Renderable;

export import std;

export namespace disxx::ui::renderable
{
	class __attribute__((visibility("default"))) [[nodiscard]] Text final : public Renderable
	{
	  private:
		std::string m_Text{};

	  public:
		explicit Text(void) noexcept;
		explicit Text(std::string_view) noexcept;

		Text(const Text &) noexcept;
		Text &operator=(const Text &) noexcept;

		Text(Text &&) noexcept;
		Text &operator=(Text &&) noexcept;

		inline void SetText(std::string_view) noexcept;
		inline std::string_view GetText(void) const noexcept;
	
		virtual std::vector<utility::Vertex<float>> GetVertices(void) const noexcept override;
	};

	inline void Text::SetText(std::string_view str) noexcept
	{ this->m_Text = str; }

	inline std::string_view Text::GetText(void) const noexcept
	{ return this->m_Text; }
} /* disxx::ui::renderable */
