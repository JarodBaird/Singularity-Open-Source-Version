#ifndef __SHIP_COMPONENT_H
#define __SHIP_COMPONENT_H
#include <string>
#include "ComponentAttributes.h"

namespace Singularity
{
	enum class ComponentType
	{
		Drive,
		Subsystem,
		Sensor,
		CrewBay,
		CargoBay,
		Generator
	};

	class ShipComponent
	{
	private:
		ComponentType m_component_type;
		std::string m_name;
		ComponentAttributes m_attributes;
	public:
		ShipComponent();
		ComponentAttributes get_attributes() const;
	};
}
#endif // !__SHIP_COMPONENT_H
