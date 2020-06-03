#include "Tags.h"

namespace Altair
{
	bool Tags::has_tag(const std::string& tag) const
	{
		for (const std::string& t : m_tags) { if (t == tag) { return true; } }
		return false;
	}

	void Tags::add_tag(std::string tag) { if (!has_tag(tag)) { m_tags.push_back(std::move(tag)); } }

	std::vector<std::string> Tags::get_all_tags() const { return m_tags; }
}
