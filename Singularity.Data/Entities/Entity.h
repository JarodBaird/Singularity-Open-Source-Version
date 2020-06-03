#ifndef __ENTITY_H
#define __ENTITY_H
#include <string>
#include <vector>

#include "../../Altair.Engine/Graphics/Sprite.h"
#include "../../Altair.Engine/FileSystem/Tags.h"

namespace Singularity
{
	class Civilization;

	class Entity : public Altair::Spriteable
	{
	protected:
		uint8_t m_tile;
		Altair::Color m_color;
		std::string m_name;
		double m_size;
		Altair::Tags m_tags;
		Civilization* m_owner;
		int32_t m_x;
		int32_t m_y;
		int32_t m_ticks_since_last_update;
	public:
		Entity();
		virtual ~Entity() = default;
		Entity(const Entity&) = default;
		Entity(Entity&&) = default;
		Entity operator =(const Entity&) = delete;
		Entity& operator =(Entity&&) = default;
		std::string get_name() const;
		double get_size() const;
		bool has_tag(const std::string& tag) const;
		std::vector<std::string> get_tags() const;
		bool can_merge(Entity* entity) const;
		void merge(Entity* entity);
		void move_towards(int32_t x, int32_t y);
		Civilization* get_owner() const;
		int32_t get_x() const;
		int32_t get_y() const;
		static double get_speed();
		Altair::Sprite to_sprite(int32_t x, int32_t y) override;
		virtual void update();
	};
}
#endif // !__ENTITY_H
