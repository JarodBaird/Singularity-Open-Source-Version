#ifndef __CELESTIAL_BODY_H
#define __CELESTIAL_BODY_H

#include "../../../Altair.Engine/Graphics/Sprite.h"
#include "../../../Altair.Engine/FileSystem/FileReaders/SettingsReader.h"
#include "../../Terrain/TerrainFeatures/TerrainFeature.h"
#include "../../Terrain/Tile.h"
#include "../../Terrain/Population.h"
#include "../../Terrain/TerrainMap.h"
#include "../../Entities/Item.h"

#include <memory>

#include "Singularity.Data/Physics/Chemistry/Chemical.h"
#include "Singularity.Data/Physics/Chemistry/Gigamole.h"

namespace Singularity
{
	class StarchartObject;

	class CelestialBody : public Altair::Spriteable, public Altair::Serializable
	{
	protected:
		struct OrbitData
		{
			int semimajor_axis;
			double eccentricity;
			double theta;
			double starting_position;
		};

		std::unique_ptr<TerrainMap> m_terrain_map;
		std::vector<std::shared_ptr<TerrainFeature>> m_structures;

		Altair::Color m_land_color; // Default land color

		short m_sprite_x;
		short m_sprite_y;

		bool m_is_starting_candidate;

		std::string m_name;

		OrbitData m_orbit{};

		std::vector<Population*> m_populations;

		StarchartObject* m_system;

		int get_distance_from_center() const;

		std::vector<Entity*> m_entities;

		struct ChemicalComposition
		{
			Chemical* element;
			Gigamoles amount;
		};

		std::vector<ChemicalComposition> m_composition;
		std::vector<ChemicalComposition> m_ocean;
		std::vector<ChemicalComposition> m_atmosphere;
	public:
		CelestialBody();
		CelestialBody(Altair::SettingsReader file);
		CelestialBody(std::string name, OrbitData orbit);

		int get_map_width() const;
		int get_map_height() const;

		bool get_can_visit() const;

		Tile get_terrain_at(int x, int y) const;
		std::shared_ptr<TerrainFeature> get_structure(int x, int y) const;
		std::vector<std::shared_ptr<TerrainFeature>> get_structures() const;
		void set_structure(int x, int y, const std::shared_ptr<TerrainFeature>& structure);

		void add_ocean(int x, int y) const;
		void erode() const;

		Altair::Sprite to_sprite(int x, int y) override;
		int get_x() const;
		int get_y() const;

		StarchartObject* get_system() const;
		void set_system(StarchartObject* system);

		std::string get_name() const;
		void set_name(std::string name);

		bool get_is_starting_candidate() const;
		void set_is_starting_candidate(bool is_starting_candidate);

		static Item* mine();

		void update();

		unsigned long long get_total_population();

		std::string serialize() override;
	};
}
#endif // !__CELESTIAL_BODY_H
