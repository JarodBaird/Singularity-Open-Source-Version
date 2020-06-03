#ifndef __REQUEST_LIST_H
#define __REQUEST_LIST_H
#include <queue>
#include "Request.h"

namespace Singularity
{
	class RequestList
	{
	private:
		std::priority_queue<Request*> requests;
	public:
		RequestList();
		void add(Request* request);
		Request* get_first_completable(Entity* entity);
	};
}
#endif // !__REQUEST_LIST_H
