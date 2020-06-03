#ifndef __TERRAIN_FEATURE_H
#define __TERRAIN_FEATURE_H
#include "../../Entities/Entity.h"

namespace Singularity
{
	class Request;
	class CelestialBody;

	class TerrainFeature
	{
	protected:
		long long m_storage_capacity;
		unsigned char m_sprite;
		Altair::Color m_color;
		CelestialBody* m_parent_body;
		std::vector<Entity*> m_inventory;
		std::string m_name;
	public:
		TerrainFeature(CelestialBody* celestial_body);
		virtual ~TerrainFeature() = default;
		TerrainFeature(const TerrainFeature&) = default;
		TerrainFeature(TerrainFeature&&) = default;
		TerrainFeature& operator =(const TerrainFeature&) = delete;
		TerrainFeature& operator =(TerrainFeature&&) = default;
		virtual void update() = 0;
		virtual Altair::Color get_color();
		virtual unsigned char get_sprite();
		std::string get_name() const;
		std::vector<Entity*> get_inventory() const;
		Entity* remove_inventory(Entity* entity);
		virtual std::vector<std::string> get_description();
	};
}
#endif // !__TERRAIN_FEATURE_H
