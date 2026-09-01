module disxx.ui.backend.event.MouseButton;

import disxx.ui.utility.Vec;

namespace disxx::ui::backend::event
{
	MouseButton::MouseButton(utility::Vec<int> position, int button, int state) noexcept
		: m_Position{position}
		, m_Button{button}
		, m_State{state}
	{}
} /* disxx::ui::backend::event */
