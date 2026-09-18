module disxx.ui.BoxLayout;

import disxx.ui.renderable.Rectangle;

import std;

namespace disxx::ui
{
	BoxLayout::BoxLayout(void) noexcept
		: Widget{}
		, m_Widgets{}
		, m_Type{}
		, m_ContentExtent{}
		, m_ScrollOffset{}
		, m_DragAnchorMouse{}
		, m_DragAnchorOffset{}
		, m_bDraggingThumb{}
	{}

	BoxLayout::BoxLayout(Type type) noexcept
		: Widget{}
		, m_Widgets{}
		, m_Type{type}
		, m_ContentExtent{}
		, m_ScrollOffset{}
		, m_DragAnchorMouse{}
		, m_DragAnchorOffset{}
		, m_bDraggingThumb{}
	{}

	BoxLayout::BoxLayout(float x, float y, float width, float height, Type type) noexcept
		: Widget{x, y, width, height}
		, m_Widgets{}
		, m_Type{type}
		, m_ContentExtent{}
		, m_ScrollOffset{}
		, m_DragAnchorMouse{}
		, m_DragAnchorOffset{}
		, m_bDraggingThumb{}
	{}

	BoxLayout::BoxLayout(const BoxLayout &other) noexcept
		: Widget{other}
		, m_Widgets{}
		, m_Type{other.m_Type}
		, m_ContentExtent{other.m_ContentExtent}
		, m_ScrollOffset{other.m_ScrollOffset}
		, m_DragAnchorMouse{other.m_DragAnchorMouse}
		, m_DragAnchorOffset{other.m_DragAnchorOffset}
		, m_bDraggingThumb{other.m_bDraggingThumb}
	{
		for (const auto &widget : other.m_Widgets)
		{
			std::visit
			(
				[this](auto &&var) -> void
				{
					if constexpr (std::same_as<typename std::decay<decltype(var)>::type, unsigned short int>)
						this->m_Widgets.push_back(var);
					else if (var)
						this->m_Widgets.emplace_back(var->Clone());
				},
				widget
			);
		}

		this->Calculate();
		this->Place();
	}

	BoxLayout &BoxLayout::operator=(const BoxLayout &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(other);
			for (const auto &widget : other.m_Widgets)
			{
				std::visit
				(
					[this](auto &&var) -> void
					{
						if constexpr (std::same_as<typename std::decay<decltype(var)>::type, unsigned short int>)
							this->m_Widgets.push_back(var);
						else if (var)
							this->m_Widgets.emplace_back(var->Clone());
					},
					widget
				);
			}
			this->m_Type = other.m_Type;
			this->m_ContentExtent = other.m_ContentExtent;
			this->m_ScrollOffset = other.m_ScrollOffset;
			this->m_DragAnchorMouse = other.m_DragAnchorMouse;
			this->m_DragAnchorOffset = other.m_DragAnchorOffset;
			this->m_bDraggingThumb = other.m_bDraggingThumb;
		}

		this->Calculate();
		this->Place();

		return *this;
	}

	BoxLayout::BoxLayout(BoxLayout &&other) noexcept
		: Widget{std::forward<BoxLayout &&>(other)}
		, m_Widgets{std::move(other.m_Widgets)}
		, m_Type{std::move(other.m_Type)}
		, m_ContentExtent{std::move(other.m_ContentExtent)}
		, m_ScrollOffset{std::move(other.m_ScrollOffset)}
		, m_DragAnchorMouse{std::move(other.m_DragAnchorMouse)}
		, m_DragAnchorOffset{std::move(other.m_DragAnchorOffset)}
		, m_bDraggingThumb{std::move(other.m_bDraggingThumb)}
	{}

	BoxLayout &BoxLayout::operator=(BoxLayout &&other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(std::forward<BoxLayout &&>(other));
			this->m_Widgets = std::move(other.m_Widgets);
			this->m_Type = std::move(other.m_Type);
			this->m_ContentExtent = std::move(other.m_ContentExtent);
			this->m_ScrollOffset = std::move(other.m_ScrollOffset);
			this->m_DragAnchorMouse = std::move(other.m_DragAnchorMouse);
			this->m_DragAnchorOffset = std::move(other.m_DragAnchorOffset);
			this->m_bDraggingThumb = std::move(other.m_bDraggingThumb);
		}

		return *this;
	}

	std::unique_ptr<Widget> BoxLayout::Clone(void) const noexcept
	{ return std::make_unique<typename std::decay<decltype(*this)>::type>(*this); }

	bool BoxLayout::IntersectsViewport(const Widget &widget) const noexcept
	{
		const auto origin{this->GetPosition()}, extent{this->GetSize()}, wPos{widget.GetPosition()}, wSize{widget.GetSize()};
		if (this->m_Type == TYPE_X_AXIS)
			return (wPos.x + wSize.x > origin.x) && (wPos.x < origin.x + extent.x);
		else
			return (wPos.y + wSize.y > origin.y) && (wPos.y < origin.y + extent.y);
	}

	void BoxLayout::Calculate(void) noexcept
	{
		this->m_ContentExtent = 0.f;

		for (const auto &entry : this->m_Widgets)
		{
			std::visit
			(
				[this](auto &&var) mutable -> void
				{
					if constexpr (std::same_as<typename std::decay<decltype(var)>::type, std::unique_ptr<Widget>>)
					{
						if (!var) [[unlikely]]
							return;

						if (const auto size{var->GetSize()}; this->m_Type == Type::TYPE_X_AXIS)
							this->m_ContentExtent += size.x;
						else
							this->m_ContentExtent += size.y;
					}
					else
						this->m_ContentExtent += var;
				},
				entry
			);
		}
	}

	void BoxLayout::Place(void) noexcept
	{
		this->m_ScrollOffset = std::clamp
		(
			this->m_ScrollOffset,
			0.f,
			std::max
			(
				0.f,
				this->m_ContentExtent - (
					this->m_Type == Type::TYPE_X_AXIS
						? this->m_Size.x
						: this->m_Size.y
				)
			)
		);

		auto cursor{-this->m_ScrollOffset};

		for (const auto &entry : this->m_Widgets)
		{
			std::visit
			(
				[this, &cursor](auto &&var) mutable -> void
				{
					if constexpr (std::same_as<typename std::decay<decltype(var)>::type, std::unique_ptr<Widget>>)
					{
						if (!var) [[unlikely]]
							return;

						const auto size{var->GetSize()};
						if (this->m_Type == Type::TYPE_X_AXIS)
						{
							var->Replace(utility::Vec2<float>{this->m_Position.x + this->m_Size.y - var->GetSize().y + cursor, this->m_Position.y});
							cursor += size.x;
						}
						else
						{
							cursor += size.y;
							var->Replace
							(
								utility::Vec2<float>
								{
									this->m_Position.x,
									this->m_Position.y + this->m_Size.y - this->m_ScrollOffset - cursor
								}
							);
						}
					}
					else
						cursor += var;
				},
				entry
			);
		}
	}

	void BoxLayout::Replace(utility::Vec2<float> position) noexcept
	{
		Widget::Replace(position);
		this->Place();
	}

	void BoxLayout::Resize(utility::Vec2<float> size) noexcept
	{
		Widget::Resize(size);
		this->Place();
	}

	void BoxLayout::ScrollTo(float offset) noexcept
	{
		this->m_ScrollOffset = std::clamp
		(
			offset,
			0.f,
			std::max
			(
				0.f,
				this->m_ContentExtent - (
					this->m_Type == Type::TYPE_X_AXIS
						? this->m_Size.x
						: this->m_Size.y
				)
			)
		);
		this->Place();
	}

	utility::Vec2<float> BoxLayout::ScrollbarTrackPosition(void) const noexcept
	{
		if (this->m_Type == Type::TYPE_X_AXIS)
			return utility::Vec2<float>{this->m_Position.x, this->m_Position.y + this->m_Size.y - s_ScrollbarThickness};
		return utility::Vec2<float>{this->m_Position.x + this->m_Size.x - s_ScrollbarThickness, this->m_Position.y};
	}

	utility::Vec2<float> BoxLayout::ScrollbarTrackSize(void) const noexcept
	{
		if (this->m_Type == Type::TYPE_X_AXIS)
			return utility::Vec2<float>{this->m_Size.x, s_ScrollbarThickness};
		return utility::Vec2<float>{s_ScrollbarThickness, this->m_Size.y};
	}

	float BoxLayout::ThumbLength(void) const noexcept
	{
		const auto viewport
		{
			this->m_Type == Type::TYPE_X_AXIS
				? this->m_Size.x
				: this->m_Size.y
		};

		if (this->m_ContentExtent <= 0.f)
			return viewport;

		const float ratio{viewport / this->m_ContentExtent};
		return std::min(viewport, std::max(s_MinThumbLength, viewport * ratio));
	}

	float BoxLayout::ThumbOffset(void) const noexcept
	{
		const auto track
		{
			(
				this->m_Type == Type::TYPE_X_AXIS
					? this->m_Size.x
					: this->m_Size.y
			) - this->ThumbLength()
		}, maxOffset{std::max(0.f, this->m_ContentExtent - (this->m_Type == Type::TYPE_X_AXIS ? this->m_Size.x : this->m_Size.y))};
		return (maxOffset > 0.f) ? (track * (this->m_ScrollOffset / maxOffset)) : 0.f;
	}

	bool BoxLayout::HitTestThumb(utility::Vec2<float> point) const noexcept
	{
		const auto trackPos{this->ScrollbarTrackPosition()}, trackSize{this->ScrollbarTrackSize()};
		const auto thumbOff{this->ThumbOffset()}, thumbLen{this->ThumbLength()};

		if (this->m_Type == TYPE_Y_AXIS)
			return point.x >= trackPos.x && point.x <= trackPos.x + trackSize.x &&
				point.y >= trackPos.y + thumbOff && point.y <= trackPos.y + thumbOff + thumbLen;
		else
			return point.y >= trackPos.y && point.y <= trackPos.y + trackSize.y &&
				point.x >= trackPos.x + thumbOff && point.x <= trackPos.x + thumbOff + thumbLen;
	}

	bool BoxLayout::HitTestTrack(utility::Vec2<float> point) const noexcept
	{
		const auto trackPos{this->ScrollbarTrackPosition()}, trackSize{this->ScrollbarTrackSize()};

		return point.x >= trackPos.x && point.x <= trackPos.x + trackSize.x &&
			point.y >= trackPos.y && point.y <= trackPos.y + trackSize.y;
	}

	void BoxLayout::Render(void) const noexcept
	{
		if (!this->Visible())
			return;

		for (const auto &entry : this->m_Widgets)
		{
			std::visit
			(
				[this](auto &&var) -> void
				{
					if constexpr (std::same_as<typename std::decay<decltype(var)>::type, std::unique_ptr<Widget>>)
					{
						if (!var) [[unlikely]]
							return;

						if (this->IntersectsViewport(*var))
							var->Render();
					}
				},
				entry
			);
		}

		if (this->m_ContentExtent > (this->m_Type == TYPE_X_AXIS ? this->m_Size.x : this->m_Size.y))
		{
			const auto trackPos{this->ScrollbarTrackPosition()}, trackSize{this->ScrollbarTrackSize()};
			const auto thumbOff{this->ThumbOffset()}, thumbLen{this->ThumbLength()};
			auto thumbPos{trackPos}, thumbSize{trackSize};

			if (this->m_Type == TYPE_X_AXIS)
			{
				thumbPos.x += thumbOff;
				thumbSize.x = thumbLen;
			}
			else
			{
				thumbPos.y += thumbOff;
				thumbSize.y = thumbLen;
			}

			renderable::Rectangle track{};
			track.Replace(trackSize);
			track.Resize(trackPos);
			track.SetColor(utility::Vec3<float>{0.4f, 0.4f, 0.4f});
			s_pRenderer->Push(std::make_unique<renderable::Rectangle>(track));

			renderable::Rectangle thumb{};
			thumb.Replace(thumbSize);
			thumb.Resize(thumbPos);
			thumb.SetColor(utility::Vec3<float>{0.4f, 0.4f, 0.4f});
			s_pRenderer->Push(std::make_unique<renderable::Rectangle>(thumb));

			s_pRenderer->Render();
		}
	}

	void BoxLayout::MouseMotionCallback(backend::event::MouseMotion event) noexcept
	{
		const auto [x, y]{event.GetPosition()};
		if (this->m_bDraggingThumb)
		{
			const auto delta{(this->m_Type == TYPE_X_AXIS ? x : y) - this->m_DragAnchorMouse};
			const auto track{(this->m_Type == TYPE_X_AXIS ? this->m_Size.x : this->m_Size.y) - this->ThumbLength()};
			const auto maxOffset{std::max(0.f, this->m_ContentExtent - (this->m_Type == TYPE_X_AXIS ? this->m_Size.x : this->m_Size.y))};

			if (track > 0.f)
				this->ScrollTo(this->m_DragAnchorOffset + delta * (maxOffset / track));
			return;
		}

		for (auto &entry : this->m_Widgets)
		{
			std::visit
			(
				[this, event](auto &&var) -> void
				{
					if constexpr (std::same_as<typename std::decay<decltype(var)>::type, std::unique_ptr<Widget>>)
					{
						if (!var) [[unlikely]]
							return;

						if (this->IntersectsViewport(*var))
							var->MouseMotionCallback(event);
					}
				},
				entry
			);
		}
	}

	void BoxLayout::MouseButtonCallback(backend::event::MouseButton event) noexcept
	{
		const auto [x, y]{event.GetPosition()};
		const bool bInBounds
		{
			x >= this->m_Position.x && x <= this->m_Position.x + this->m_Size.x &&
			y >= this->m_Position.y && y <= this->m_Position.y + this->m_Size.y
		};

		if (this->m_ContentExtent > (this->m_Type == TYPE_X_AXIS ? this->m_Size.x : this->m_Size.y))
		{
			if (event.GetButton() == 0 && event.GetState() == 0 && this->HitTestThumb(event.GetPosition()))
			{
				this->m_bDraggingThumb = true;
				this->m_DragAnchorMouse = (this->m_Type == TYPE_X_AXIS) ? x : y;
				this->m_DragAnchorOffset = this->m_ScrollOffset;
				return;
			}

			if (event.GetButton() != 0)
				this->m_bDraggingThumb = false;

			if (event.GetButton() == 0 && event.GetState() == 0 && this->HitTestTrack(event.GetPosition()))
			{
				const utility::Vec2<float> trackPos{this->ScrollbarTrackPosition()};
				const float clickMain{(this->m_Type == TYPE_X_AXIS) ? x : y};
				const float trackMain{(this->m_Type == TYPE_X_AXIS) ? trackPos.x : trackPos.y};
				const float thumbStart{trackMain + this->ThumbOffset()};

				this->ScrollTo
				(
					this->m_ScrollOffset + (
						this->m_Type == TYPE_X_AXIS
							? this->m_Size.x
							: this->m_Size.y
					) * (clickMain < thumbStart ? -1.f : 1.f)
				);
				return;
			}
		}

		if (!bInBounds)
			return;

		for (auto &entry : this->m_Widgets)
		{
			std::visit
			(
				[this, event](auto &&var) -> void
				{
					if constexpr (std::same_as<typename std::decay<decltype(var)>::type, std::unique_ptr<Widget>>)
					{
						if (!var) [[unlikely]]
							return;

						if (this->IntersectsViewport(*var))
							var->MouseButtonCallback(event);
					}
				},
				entry
			);
		}
	}

	void BoxLayout::KeyboardCallback(backend::event::Keyboard event) noexcept
	{
		for (auto &entry : this->m_Widgets)
		{
			std::visit
			(
				[event](auto &&var) -> void
				{
					if constexpr (std::same_as<typename std::decay<decltype(var)>::type, std::unique_ptr<Widget>>)
					{
						if (!var) [[unlikely]]
							return;
						var->KeyboardCallback(event);
					}
				},
				entry
			);
		}
	}
} /* disxx::ui */
