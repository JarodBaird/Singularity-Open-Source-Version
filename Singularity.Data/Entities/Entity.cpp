#include "Entity.h"

namespace Singularity
{
	Entity::Entity()
	{
		m_tile = 0x00;
		m_size = 0;
		m_owner = nullptr;
		m_x = 0;
		m_y = 0;
		m_ticks_since_last_update = 0;
	}

	std::string Entity::get_name() const { return m_name; }

	double Entity::get_size() const { return m_size; }

	bool Entity::has_tag(const std::string& tag) const { return m_tags.has_tag(tag); }

	std::vector<std::string> Entity::get_tags() const { return m_tags.get_all_tags(); }

	bool Entity::can_merge(Entity* entity) const { return m_name == entity->get_name(); }

	void Entity::merge(Entity* entity)
	{
		for (const std::string& tag : entity->get_tags()) { if (!has_tag(tag)) { m_tags.add_tag(tag); } }

		m_size += entity->get_size();
	}

	Civilization* Entity::get_owner() const { return m_owner; }

	int32_t Entity::get_x() const { return m_x; }

	int32_t Entity::get_y() const { return m_y; }

	void Entity::move_towards(int32_t x, int32_t y)
	{
		const double slowest_speed = get_speed();
		if (m_ticks_since_last_update > slowest_speed)
		{
			const int32_t delta_x = x - get_x();
			const int32_t delta_y = y - get_y();
			if (delta_x != 0 || delta_y != 0)
			{
				if (abs(delta_x) > abs(delta_y))
				{
					if (delta_x > 0) { m_x++; }
					else if (delta_x < 0) { m_x--; }
				}
				else
				{
					if (delta_y > 0) { m_y++; }
					else if (delta_y < 0) { m_y--; }
				}
			}

			m_ticks_since_last_update = 0;
		}
	}

	double Entity::get_speed() { return 1.0 / 365; }

	Altair::Sprite Entity::to_sprite(int32_t x, int32_t y) { return Altair::Sprite(x, y, m_tile, m_color); }

	void Entity::update() { }
}
