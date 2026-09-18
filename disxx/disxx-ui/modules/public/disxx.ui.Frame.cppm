export module disxx.ui.Frame;

import disxx.ui.Widget;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] Frame final : public Widget
	{
	  public:
		explicit Frame(void) noexcept;
		explicit Frame(float, float, float, float) noexcept;

		Frame(const Frame &) noexcept;
		Frame &operator=(const Frame &) noexcept;

		Frame(Frame &&) noexcept;
		Frame &operator=(Frame &&) noexcept;
		
		virtual std::unique_ptr<Widget> Clone(void) const noexcept override;
		
		virtual void Render(void) const noexcept override;
	};
} /* disxx::ui */
