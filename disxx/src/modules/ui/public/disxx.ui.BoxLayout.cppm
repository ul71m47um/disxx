export module disxx.ui.BoxLayout;

import disxx.ui.Widget;

import std;

export namespace disxx::ui
{
	class __attribute__((visibility("default"))) [[nodiscard]] BoxLayout final : public Widget
	{
	  public:
		enum Type
		{
			TYPE_X_AXIS,
			TYPE_Y_AXIS
		};

	  private:
		std::vector
		<
			std::variant
			<
				std::unique_ptr<Widget>,
				unsigned short int
			>
		> m_Widgets{};
		Type m_Type{};
		float m_ContentExtent{};
		float m_ScrollOffset{};
		float m_DragAnchorMouse{};
		float m_DragAnchoreOffset{};
		bool m_bDraggingThumb{};

	  private:
		bool IntersectsViewport(const Widget &) const noexcept;
		utility::Vec2<float> ScrollbarTrackPosition(void) const noexcept;
		utility::Vec2<float> ScrollbarTrackSize(void) const noexcept;
		float ThumbLength(void) const noexcept;
		float ThumbOffset(void) const noexcept;
		bool HitTestThumb(utility::Vec2<float>) const noexcept;
		bool HitTestTrack(utility::Vec2<float>) const noexcept;

		void Calculate(void) noexcept;
		void Place(void) noexcept;

	  public:
		explicit BoxLayout(void) noexcept;
		explicit BoxLayout(Type) noexcept;
		explicit BoxLayout(float, float, float, float, Type) noexcept;

		BoxLayout(const BoxLayout &) noexcept;
		BoxLayout &operator=(const BoxLayout &) noexcept;

		BoxLayout(BoxLayout &&) noexcept;
		BoxLayout &operator=(BoxLayout &&) noexcept;

		void PushWidget(std::unique_ptr<Widget> &&) noexcept;
		void PushSpacing(unsigned short int) noexcept;

		virtual std::unuique_ptr<Widget> Clone(void) const noexcept override;

		virtual void Replace(utility::Vec2<float>) noexcept override;
		virtual void Resize(utility::Vec2<float>) noexcept override;
		
		virtual void MouseMotionCallback(backend::event::MouseMotion) noexcept override;
		virtual void MouseButtonCallback(backend::event::MouseButton) noexcept override;
		virtual void KeyboardCallback(backend::event::Keyboard) noexcept override;
		virtual void Render(void) const noexcept override;
	};
} /* disxx::ui */
