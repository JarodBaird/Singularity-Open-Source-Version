#include "Chemical.h"

namespace Singularity
{
	Chemical::Chemical() = default;

	bool Chemical::has_tag(const std::string& tag) const { return m_tags.has_tag(tag); }

	std::string Chemical::get_name() const { return m_name; }
}
