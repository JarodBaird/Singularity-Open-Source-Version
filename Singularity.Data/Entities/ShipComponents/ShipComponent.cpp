#include "ShipComponent.h"

namespace Singularity
{
	ShipComponent::ShipComponent()
	{
		m_component_type = ComponentType::Drive;
		m_attributes = ComponentAttributes();
	}

	ComponentAttributes ShipComponent::get_attributes() const { return m_attributes; }
}
