export module disxx.ui.backend.event.Reshape;

export import disxx.ui.utility.Vec;

export namespace disxx::ui::backend::event
{
	class __attribute__((visibility("hidden"))) [[nodiscard]] Reshape
	{
	  private:
		utility::Vec2<float> m_Size{};
	
	  public:
		explicit Reshape(void) noexcept = default;
		explicit Reshape(utility::Vec2<float>) noexcept;

		Reshape(const Reshape &) noexcept = default;
		Reshape &operator=(const Reshape &) noexcept = default;

		inline utility::Vec2<float> GetSize(void) const noexcept;
	};

	inline utility::Vec2<float> Reshape::GetSize(void) const noexcept { return this->m_Size; }
} /* disxx::ui::backend::event */
