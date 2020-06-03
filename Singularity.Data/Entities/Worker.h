#ifndef __WORKER_H
#define __WORKER_H
#include "Entity.h"
#include "../Space/Bodies/CelestialBody.h"

namespace Singularity
{
	class Worker final : public Entity
	{
	private:
		CelestialBody* m_body;
	public:
		Worker(Civilization* owner, CelestialBody* body);
		void update() override;
	};
}
#endif // !__WORKER_H
