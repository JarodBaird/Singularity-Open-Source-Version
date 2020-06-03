#include "PhysicalAttribute.h"

namespace Singularity
{
	PhysicalAttribute::PhysicalAttribute() = default;

	PhysicalAttribute::PhysicalAttribute(std::string description) { m_description = std::move(description); }

	std::string PhysicalAttribute::get_description() const { return m_description; }
}
