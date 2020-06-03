#ifndef __ITEM_H
#define __ITEM_H
#include "Entity.h"
#include <string>

namespace Singularity
{
	class Item final : public Entity
	{
	public:
		Item(std::string name, double size, const std::vector<std::string>& tags);
		void update() override;
	};
}
#endif // !__ITEM_H
