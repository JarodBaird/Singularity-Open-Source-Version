#include "RequestList.h"

namespace Singularity
{
	RequestList::RequestList() = default;

	void RequestList::add(Request* request) { requests.push(request); }

	Request* RequestList::get_first_completable(Entity* entity)
	{
		if (!requests.empty() && Request::can_complete(entity))
		{
			Request* top = requests.top();
			requests.pop();
			return top;
		}

		return nullptr;
	}
}
