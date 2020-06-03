#ifndef __REQUEST_H
#define __REQUEST_H
#include <vector>
#include "ActionType.h"

namespace Singularity
{
	class Entity;

	class Request
	{
	private:
		std::vector<ActionType> m_required_actions;
		bool m_is_complete = false;
		int m_priority = 0;
	public:
		Request();
		Request(std::vector<ActionType> required_actions, int priority);
		virtual ~Request() = default;
		Request(const Request&) = default;
		Request(Request&&) = default;
		Request& operator =(const Request&) = delete;
		Request& operator =(Request&&) = default;
		void mark_complete();
		int get_priority() const;
		bool get_is_complete() const;
		static bool can_complete(Entity* entity);
		virtual void update(Entity* entity) = 0;
	};
}
#endif // !__REQUEST_H
