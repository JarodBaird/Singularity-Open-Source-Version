#ifndef __ATTACK_REQUEST_H
#define __ATTACK_REQUEST_H
#include "../Request.h"

namespace Singularity
{
	class AttackRequest final : public Request
	{
	public:
		AttackRequest();
		void update(Entity* entity) override;
	};
}
#endif // !__ATTACK_REQUEST_H
