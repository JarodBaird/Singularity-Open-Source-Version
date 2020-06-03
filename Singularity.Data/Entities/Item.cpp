#include "Item.h"

namespace Singularity
{
	Item::Item(std::string name, double size, const std::vector<std::string>& tags)
	{
		m_name = std::move(name);
		m_size = size;
		for (const std::string& tag : tags) { m_tags.add_tag(tag); }
	}

	void Item::update() { }
}
