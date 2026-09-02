module disxx.ui.backend.event.Reshape;

import disxx.ui.utility.Vec;

namespace disxx::ui::backend::event
{
	Reshape::Reshape(utility::Vec2<float> size) noexcept
		: m_Size{size}
	{}
} /* disxx::ui::backend::event */
