#ifndef __FLEET_H
#define __FLEET_H
#include <vector>
#include "Entity.h"
#include "../Requests/Request.h"
#include "../Civilization/Civilization.h"

namespace Singularity
{
	class Fleet final : public Entity
	{
	private:
		std::vector<Entity*> m_ships;
		Request* m_current_request;
		void wander();
	public:
		Fleet(int32_t x, int32_t y);
		~Fleet();
		Fleet(const Fleet&) = default;
		Fleet(Fleet&&) = default;
		Fleet& operator =(const Fleet&) = delete;
		Fleet& operator =(Fleet&&) = default;
		void add_ship(Entity* ship);
		void update() override;
	};
}
#endif // !__FLEET_H
