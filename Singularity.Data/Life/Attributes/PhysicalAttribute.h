#ifndef __PHYSICAL_ATTRIBUTE_H
#define __PHYSICAL_ATTRIBUTE_H
#include <string>

namespace Singularity
{
	class PhysicalAttribute
	{
	private:
		std::string m_description;
	public:
		PhysicalAttribute();
		PhysicalAttribute(std::string description);

		std::string get_description() const;
	};
}
#endif // !__PHYSICAL_ATTRIBUTE_H
