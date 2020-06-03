#include "AttackRequest.h"

namespace Singularity
{
	AttackRequest::AttackRequest() : Request({ActionType::Attack}, 0) {}

	void AttackRequest::update(Entity*) { }
}
