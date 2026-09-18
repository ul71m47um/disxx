module disxx.ui.backend.event.MouseMotion;

import disxx.ui.utility.Vec;

namespace disxx::ui::backend::event
{
	MouseMotion::MouseMotion(utility::Vec2<float> position, bool bPassive) noexcept
		: m_Position{position}
		, m_bPassive{bPassive}
	{}
} /* disxx::ui::backend::event */
