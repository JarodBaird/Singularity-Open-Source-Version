#ifndef __WAVE_H
#define __WAVE_H
#include "Entity.h"

namespace Singularity
{
	class Wave final : public Entity
	{
	public:
		Wave();
		void update() override;
	};
}
#endif // !__WAVE_H
