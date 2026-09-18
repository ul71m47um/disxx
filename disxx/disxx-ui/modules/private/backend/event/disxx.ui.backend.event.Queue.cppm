export module disxx.ui.backend.event.Queue;

export import disxx.ui.backend.event.MouseMotion;
export import disxx.ui.backend.event.MouseButton;
export import disxx.ui.backend.event.Keyboard;
export import disxx.ui.backend.event.Reshape;
import disxx.utility.Overload;

export import std;

export namespace disxx::ui::backend::event
{
	/*
	 * Queue, that store events's data
	 */
	class __attribute__((visibility("default"))) [[nodiscard]] Queue
	{
	  public:
	 	using EventData = std::variant
		<
			MouseMotion,
			MouseButton,
			Keyboard,
			Reshape
		>;

	  private:
		std::queue<EventData> m_EventsData{};

	  public:
		explicit Queue(void) noexcept = default;

		Queue(const Queue &) noexcept = default;
		Queue &operator=(const Queue &) noexcept = default;

		inline void Push(EventData) noexcept;
		inline EventData Pop(void) noexcept;

		template <typename ...Args>
		inline void Visit(disxx::utility::Overload<Args...> &&) noexcept;
	};

	inline void Queue::Push(EventData data) noexcept { this->m_EventsData.push(data); }
	inline Queue::EventData Queue::Pop(void) noexcept
	{
		const auto event{this->m_EventsData.front()};
		this->m_EventsData.pop();
		return event;
	}

	template <typename ...Args>
	inline void Queue::Visit(disxx::utility::Overload<Args...> &&callbacks) noexcept
	{
		while (!this->m_EventsData.empty())
		{
			std::visit
			(
				callbacks,
				this->m_EventsData.front()
			);
			
			this->m_EventsData.pop();
		}
	}
} /* disxx::ui::backend::event */
