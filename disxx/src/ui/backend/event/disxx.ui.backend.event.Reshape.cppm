module disxx.ui.backend.event.Reshape;

import disxx.ui.utility.Vec;

namespace disxx::ui::backend::event
{
	Reshape::Reshape(utility::Vec<int> position) noexcept
		: m_Position{position}
	{}
} /* disxx::ui::backend::event */
