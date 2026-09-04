module disxx.ui.SourceEditor;

import disxx.ui.backend.opengl.Renderer;
import disxx.ui.backend.glut.Context;
import disxx.ui.renderable.Rectangle;
import disxx.ui.renderable.Text;
import disxx.ui.utility.Vec;

namespace
{
	// I confused these values... And I'm too lazy
	// to fix them
	constexpr auto CHAR_WIDTH = 15ul;
	constexpr auto CHAR_HEIGHT = 9ul;

	constexpr auto CORNER_WIDTH = 20.f;
	constexpr auto CORNER_HEIGHT = 20.f;

	constexpr auto SKIP_PER_SCROLL = 3ul;
} /* */

namespace disxx::ui
{
	SourceEditor::SourceEditor(void) noexcept
		: Widget{}
		, m_Lines{}
		, m_LastMouseX{0.f}
		, m_LastMouseY{0.f}
		, m_ScrollX{0.f}
		, m_ScrollY{0.f}
		, m_MaxScrollX{0.f}
		, m_MaxScrollY{0.f}
		, m_VerticalSliderHeight{0.f}
		, m_HorizontalSliderWidth{0.f}
		, m_bActiveVertical{false}
		, m_bActiveHorizontal{false}
	{
		this->m_Lines.emplace_back("");
		this->ComputeMaxScroll();
	}

	SourceEditor::SourceEditor(float x, float y, float width, float height) noexcept
		: Widget{x, y, width, height}
       	, m_Lines{} 
		, m_LastMouseX{0.f}
        , m_LastMouseY{0.f}
		, m_ScrollX{0.f}
        , m_ScrollY{0.f}
        , m_MaxScrollX{0.f}
        , m_MaxScrollY{0.f}
        , m_VerticalSliderHeight{0.f}
        , m_HorizontalSliderWidth{0.f}
		, m_bActiveVertical{false}
		, m_bActiveHorizontal{false}
	{
		this->m_Lines.emplace_back("");
		this->ComputeMaxScroll();
	}

	SourceEditor::SourceEditor(const SourceEditor &other) noexcept
		: Widget{other}
		, m_Lines{other.m_Lines}
        , m_LastMouseX{other.m_LastMouseX}
        , m_LastMouseY{other.m_LastMouseY}
		, m_ScrollX{other.m_ScrollX}
		, m_ScrollY{other.m_ScrollY}
        , m_MaxScrollX{other.m_MaxScrollX}
        , m_MaxScrollY{other.m_MaxScrollY}
        , m_VerticalSliderHeight{other.m_VerticalSliderHeight}
        , m_HorizontalSliderWidth{other.m_HorizontalSliderWidth}
		, m_bActiveVertical{other.m_bActiveVertical}
		, m_bActiveHorizontal{other.m_bActiveHorizontal}
	{}

	SourceEditor &SourceEditor::operator=(const SourceEditor &other) noexcept
	{
		if (this != &other) [[likely]]
		{
			Widget::operator=(other);
			this->m_Lines = other.m_Lines;
			this->m_LastMouseX = other.m_LastMouseX;
			this->m_LastMouseY = other.m_LastMouseY;
			this->m_ScrollX = other.m_ScrollX;
			this->m_ScrollY = other.m_ScrollY;	
			this->m_MaxScrollX = other.m_MaxScrollX;
			this->m_MaxScrollY = other.m_MaxScrollY;	
			this->m_VerticalSliderHeight = other.m_VerticalSliderHeight;
			this->m_HorizontalSliderWidth = other.m_HorizontalSliderWidth;
			this->m_bActiveVertical = other.m_bActiveVertical;
			this->m_bActiveHorizontal = other.m_bActiveHorizontal;
		}

		return *this;
	}

	void SourceEditor::ComputeMaxScroll(void) noexcept
	{
		this->m_MaxScrollY = std::max(0.f, static_cast<float>(this->m_Lines.size() * CHAR_WIDTH - (this->m_Size.y - CORNER_HEIGHT * 2.f) + 5.f));
		this->m_ScrollY = std::max(0.f, std::min(this->m_ScrollY, this->m_MaxScrollY));

		this->m_MaxScrollX = 0.f;
		for (const auto &line : this->m_Lines)
			if (auto realText{utility::ColorTag{}.RemoveTags(line)}; realText.size() * CHAR_HEIGHT + 5 > this->m_MaxScrollX)
				this->m_MaxScrollX = std::max(0.f, realText.size() * CHAR_HEIGHT + 5.f - (this->m_Size.x - CORNER_WIDTH * 2.f));

		this->m_VerticalSliderHeight = (this->m_Size.y - CORNER_HEIGHT * 2.f) * ((this->m_Size.y - CORNER_HEIGHT * 2.f)
			/ static_cast<float>(this->m_Lines.size() * CHAR_WIDTH));
		this->m_VerticalSliderHeight = std::max(30.f, std::min(this->m_VerticalSliderHeight, this->m_Size.y - CORNER_HEIGHT * 2.f));

		this->m_HorizontalSliderWidth = (this->m_Size.x - CORNER_WIDTH * 2.f) * ((this->m_Size.x - CORNER_WIDTH * 2.f) / (this->m_MaxScrollX + (this->m_Size.x - CORNER_WIDTH * 2.f)));
		this->m_HorizontalSliderWidth = std::max(30.f, std::min(this->m_HorizontalSliderWidth, this->m_Size.x - CORNER_WIDTH * 2.f));
	}

	std::unique_ptr<Widget> SourceEditor::Clone(void) const noexcept
	{ return std::make_unique<std::decay<decltype(*this)>::type>(*this); }

	void SourceEditor::Resize(utility::Vec2<float> size) noexcept
	{
		Widget::Resize(utility::Vec2<float>{size});
		this->ComputeMaxScroll();
	}

	void SourceEditor::MouseButtonCallback(backend::event::MouseButton event) noexcept
	{
		const auto [x, y]{event.GetPosition()};
		if (!(x >= this->m_Position.x && x <= this->m_Position.x + this->m_Size.x && y >= this->m_Position.y && y <= this->m_Position.y + this->m_Size.y))
			return;

		// Mouse clicked	
		if (const auto button{event.GetButton()}, state{event.GetState()}; button == 0 && state == 0)
		{
			// The verticall scrollbar has been dragged
			const auto localX{static_cast<float>(x) - this->m_Position.x}, localY{static_cast<float>(y) - this->m_Position.y};
			if (localX >= this->m_Size.x - CORNER_WIDTH && localX < this->m_Size.x && localY > CORNER_HEIGHT && localY < this->m_Size.y)
			{
				this->m_bActiveVertical = true;
				this->m_LastMouseY = y;
			}
			// The horizontal scrollbar has been dragged
			else if (localX >= 0 && localX < this->m_Size.x - CORNER_WIDTH && localY >= 0)
			{
				this->m_bActiveHorizontal = true;
				this->m_LastMouseX = x;
			}
		}
		// Mouse released
		else if (button == 0 && state == 1)
		{
			this->m_bActiveVertical = false;
			this->m_bActiveHorizontal = false;
		}
		// Mouse wheel (doesn't really work)
		else if (button == 3 || button == 4)
		{
			this->m_ScrollY += CHAR_HEIGHT * SKIP_PER_SCROLL * (button == 3 ? 1 : -1);
			this->m_ScrollY = std::max(0.f, std::min(this->m_ScrollY, this->m_MaxScrollY));
		}
	}

	void SourceEditor::MouseMotionCallback(backend::event::MouseMotion event) noexcept
	{
		if (event.Passive())
			return;

		const auto [x, y]{event.GetPosition()};
		if (this->m_bActiveVertical)
		{
			float delta{y - this->m_LastMouseY};
			this->m_LastMouseY = y;

			this->m_ScrollY += delta * (this->m_MaxScrollY / (this->m_Size.y - CORNER_HEIGHT * 2.f));
			this->m_ScrollY = std::max(0.f, std::min(this->m_ScrollY, this->m_MaxScrollY));
		}
		else if (this->m_bActiveHorizontal)
		{
			float delta{x - this->m_LastMouseX};
            this->m_LastMouseX = x;

  	        this->m_ScrollX += delta * (this->m_MaxScrollX / (this->m_Size.x - CORNER_WIDTH * 2.f));
			this->m_ScrollX = std::max(0.f, std::min(this->m_ScrollX, this->m_MaxScrollX));
		}
	}
	
	void SourceEditor::Render(void) const noexcept
	{
		if (!this->m_bVisible)
			return;

		// Render the text area
		utility::ColorTag tag{};
        for (const auto i : std::views::iota(0ul, this->m_Lines.size()))
        {
            if (float lineY{this->m_Size.y - CORNER_HEIGHT * 2.f - i * CHAR_WIDTH + this->m_ScrollY}; (lineY < 0.f) || (lineY > this->m_Size.y - CORNER_HEIGHT * 2.f))
                continue;

			// The line without color tags
            const auto &realText{tag.RemoveTags(this->m_Lines[i])};
            for (auto pos{0ul}; const auto &[text, color] : tag.Parse(this->m_Lines[i]).value())
            {
				// Indexes to walk through the line
                const auto renderStart{std::max(pos, static_cast<unsigned long>(std::max(0.f, this->m_ScrollX / CHAR_HEIGHT)))};
                const auto renderEnd
				{
					std::min
					(
						pos + text.size(),
						std::min
						(
							realText.size(),
							renderStart + static_cast<unsigned long>((this->m_Size.x - CORNER_WIDTH * 2.f) / CHAR_HEIGHT)
						)
					)
				};

				renderable::Text txt{};
				txt.Replace
				(
					utility::Vec2<float>
					{
						std::max(1.f, 5.f - this->m_ScrollX + static_cast<float>(renderStart) * CHAR_HEIGHT),
						this->m_Position.y + this->m_Size.y - i * CHAR_WIDTH + this->m_ScrollY
					}
				);
				txt.SetColor
				(
					utility::Vec3<float>
					{
						color.at(0),
						color.at(1),
						color.at(2)
					}
				);
       		
				std::string str{};
				if (renderStart < renderEnd) [[likely]]
					for (const auto j : std::views::iota(renderStart, renderEnd))
           				str += realText.at(j);
				txt.SetText(str);
                s_pRenderer->Push(std::make_unique<renderable::Text>(txt));

				pos += text.size();
        	}
        }
	
		// Render the vertical scrollbar
		if (this->m_MaxScrollY > 0)
		{
			float pos{(this->m_ScrollY / this->m_MaxScrollY) * (this->m_Size.y - CORNER_HEIGHT * 2.f - this->m_VerticalSliderHeight)};
			pos = std::max(0.f, std::min(pos, this->m_Size.y - CORNER_HEIGHT * 2.f - this->m_VerticalSliderHeight) - 20.f) + 20.f;

			// Frame
			renderable::Rectangle frame{};
			frame.Replace(utility::Vec2<float>{this->m_Position.x + this->m_Size.x - CORNER_WIDTH, this->m_Position.y + CORNER_HEIGHT});
			frame.Resize(utility::Vec2<float>{CORNER_WIDTH, this->m_Size.y - CORNER_HEIGHT});
			frame.SetColor(utility::Vec3<float>{0.35f, 0.35f, 0.35f});
			s_pRenderer->Push(std::make_unique<renderable::Rectangle>(frame));

			// Upper arrow
			renderable::Text upperText{"^"};
			upperText.Replace(utility::Vec2<float>{this->m_Position.x + this->m_Size.x - 15.f, this->m_Position.y + this->m_Size.y - 15.f});
			upperText.SetColor(utility::Vec3<float>{1.f, 1.f, 1.f});
			s_pRenderer->Push(std::make_unique<renderable::Text>(upperText));

			// Lower arrow
			renderable::Text lowerText{"v"};
			lowerText.Replace(utility::Vec2<float>{this->m_Position.x + this->m_Size.x - 15.f, this->m_Position.y + CORNER_HEIGHT + 5.f});
			lowerText.SetColor(utility::Vec3<float>{1.f, 1.f, 1.f});
			s_pRenderer->Push(std::make_unique<renderable::Text>(lowerText));
			
			// Scrollbar itself
			renderable::Rectangle vScrollbar{};
			vScrollbar.Replace(utility::Vec2<float>{this->m_Position.x + this->m_Size.x - CORNER_WIDTH, this->m_Position.y + this->m_Size.y - this->m_VerticalSliderHeight - pos});
			vScrollbar.Resize(utility::Vec2<float>{CORNER_WIDTH, this->m_VerticalSliderHeight});
			vScrollbar.SetColor(utility::Vec3<float>{0.3f, 0.3f, 0.3f});
			s_pRenderer->Push(std::make_unique<renderable::Rectangle>(vScrollbar));
		}

		// Render the horizontal scrollbar
		if (this->m_MaxScrollX > 0)
		{
			float pos{(this->m_ScrollX / this->m_MaxScrollX) * (this->m_Size.x - CORNER_WIDTH * 2.f - this->m_HorizontalSliderWidth)};
			pos = std::max(0.f, std::min(pos, this->m_Size.x - CORNER_WIDTH * 2.f - this->m_HorizontalSliderWidth) - 20.f) + 20.f;

			// Frame
			renderable::Rectangle frame{};
			frame.Replace(utility::Vec2<float>{this->m_Position.x, this->m_Position.y});
			frame.Resize(utility::Vec2<float>{this->m_Size.x - CORNER_WIDTH, CORNER_HEIGHT});
			frame.SetColor(utility::Vec3<float>{0.35f, 0.35f, 0.35f});
			s_pRenderer->Push(std::make_unique<renderable::Rectangle>(frame));

			// Left arrow
			renderable::Text leftText{"<"};
			leftText.Replace(utility::Vec2<float>{this->m_Position.x + 5.f, this->m_Position.y + 5.f});
			leftText.SetColor(utility::Vec3<float>{1.f, 1.f, 1.f});
			s_pRenderer->Push(std::make_unique<renderable::Text>(leftText));
			
			// Right arrow
			renderable::Text rightText{">"};
			rightText.Replace(utility::Vec2<float>{this->m_Position.x + this->m_Size.x - 20.f - CORNER_WIDTH + 5.f, this->m_Position.y + 5.f});
			rightText.SetColor(utility::Vec3<float>{1.f, 1.f, 1.f});
			s_pRenderer->Push(std::make_unique<renderable::Text>(rightText));

			// Scrollbar itself
			renderable::Rectangle hScrollbar{};
			hScrollbar.Replace(utility::Vec2<float>{this->m_Position.x + pos, this->m_Position.y});
			hScrollbar.Resize(utility::Vec2<float>{this->m_HorizontalSliderWidth, CORNER_HEIGHT});
			hScrollbar.SetColor(utility::Vec3<float>{0.3f, 0.3f, 0.3f});
			s_pRenderer->Push(std::make_unique<renderable::Rectangle>(hScrollbar));
		}

		this->s_pRenderer->Render();
	}
} /* disxx::ui */
