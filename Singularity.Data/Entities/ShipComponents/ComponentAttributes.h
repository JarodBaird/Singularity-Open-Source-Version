#ifndef __COMPONENT_ATTRIBUTES_H
#define __COMPONENT_ATTRIBUTES_H

#include <vector>
#include <string>

namespace Singularity
{
	typedef double Tons;

	struct ComponentAttributes
	{
	public:
		ComponentAttributes();
		double crew;
		Tons storage;
		double thrust;
		std::vector<std::string> tags;
	};
}
#endif // !__COMPONENT_ATTRIBUTES_H
