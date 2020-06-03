#include "Request.h"

namespace Singularity
{
	Request::Request() = default;

	Request::Request(std::vector<ActionType> required_actions, int priority)
	{
		m_priority = priority;
		m_required_actions = std::move(required_actions);
	}

	void Request::mark_complete() { m_is_complete = true; }

	int Request::get_priority() const { return m_priority; }

	bool Request::get_is_complete() const { return m_is_complete; }

	bool Request::can_complete(Entity*) { return true; }
}
