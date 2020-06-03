#include <cmath>

#include "CelestialBody.h"
#include "../../Terrain/MapTypes/LargeTerrainMap.h"
#include "../../Terrain/MapTypes/MediumTerrainMap.h"
#include "../../Terrain/MapTypes/SmallTerrainMap.h"
#include "../../Terrain/MapTypes/TinyTerrainMap.h"
#include "../../Terrain/TerrainFeatures/Natural/Forest.h"

namespace Singularity
{
	CelestialBody::CelestialBody()
	{
		m_name = "";
		m_system = nullptr;
		m_is_starting_candidate = false;
		m_sprite_x = 0;
		m_sprite_y = 0;
		m_orbit.eccentricity = 0.01;
		m_orbit.theta = 0;
		m_orbit.starting_position = static_cast<double>(rand() % 1000) / 1000 * M_PI * static_cast<double>(2);
	}

	CelestialBody::CelestialBody(Altair::SettingsReader file)
	{
		m_name = file.get("Name");
		m_system = nullptr;
		m_orbit.theta = file.get_double("Theta");
		m_orbit.semimajor_axis = file.get_int("SemiMajorAxis");
		m_orbit.starting_position = file.get_double("StartingPosition");
		m_sprite_x = file.get_short("SpriteX");
		m_sprite_y = file.get_short("SpriteY");
		m_land_color = Altair::Color(file.get_int("LandColor"));
		m_is_starting_candidate = file.get_bool("IsStartingCandidate");

		const std::string map_type = file.get("MapType");
		std::string map = file.get("Map");

		if (map_type == "Large") { m_terrain_map = std::make_unique<LargeTerrainMap>(map); }
		else if (map_type == "Small") { m_terrain_map = std::make_unique<SmallTerrainMap>(map); }
		else if (map_type == "Tiny") { m_terrain_map = std::make_unique<TinyTerrainMap>(map); }
		else if (map_type == "Medium") { m_terrain_map = std::make_unique<MediumTerrainMap>(map); }
		else { m_terrain_map = nullptr; }

		if (m_terrain_map != nullptr)
		{
			for (Altair::SettingsReader structure : file.get_sub_settings())
			{
				const std::shared_ptr<TerrainFeature> terrain_feature = std::make_unique<Forest>(this);
				const int x = structure.get_int("X");
				const int y = structure.get_int("Y");
				m_terrain_map->set_structure(x, y, terrain_feature);
			}
		}
	}

	CelestialBody::CelestialBody(std::string name, OrbitData orbit)
	{
		m_name = std::move(name);
		m_orbit = orbit;
		m_sprite_x = 0;
		m_sprite_y = 0;
		m_is_starting_candidate = false;
		m_system = nullptr;
	}

	int CelestialBody::get_distance_from_center() const
	{
		const double e = m_orbit.eccentricity;
		const double a = m_orbit.semimajor_axis;
		return static_cast<int>(a * (static_cast<double>(1) - e * e) /
			(static_cast<double>(1) + e * cos(m_orbit.theta + m_orbit.starting_position)));
	}

	int CelestialBody::get_map_height() const { return m_terrain_map->get_map_height(); }

	int CelestialBody::get_map_width() const { return m_terrain_map->get_map_width(); }

	bool CelestialBody::get_can_visit() const
	{
		if (m_terrain_map == nullptr) { return false; }
		return true;
	}

	Altair::Sprite CelestialBody::to_sprite(int x, int y)
	{
		return Altair::Sprite(x, y, m_sprite_x, m_sprite_y, m_land_color);
	}

	int CelestialBody::get_x() const
	{
		return static_cast<int>(get_distance_from_center() * cos(m_orbit.theta + m_orbit.starting_position));
	}

	int CelestialBody::get_y() const
	{
		return static_cast<int>(get_distance_from_center() * sin(m_orbit.theta + m_orbit.starting_position));
	}

	StarchartObject* CelestialBody::get_system() const { return m_system; }

	void CelestialBody::set_system(StarchartObject* system) { m_system = system; }

	std::string CelestialBody::get_name() const { return m_name; }

	void CelestialBody::set_name(std::string name) { m_name = std::move(name); }

	void CelestialBody::update()
	{
		for (Population* pop : m_populations) { pop->update(); }

		for (const std::shared_ptr<TerrainFeature>& feature : m_structures) { feature->update(); }

		for (Entity* entity : m_entities) { entity->update(); }

		double period = static_cast<double>(m_orbit.semimajor_axis) / 5;

		period = period * 128 * 32 * 16;

		const double delta = 2 * M_PI * m_orbit.semimajor_axis / (period * get_distance_from_center());

		m_orbit.theta -= delta;
	}

	unsigned long long CelestialBody::get_total_population()
	{
		unsigned long long total = 0;
		for (Population* pop : m_populations) { total += pop->get_population(); }
		return total;
	}

	Tile CelestialBody::get_terrain_at(int x, int y) const
	{
		const unsigned char height = m_terrain_map->get_terrain_height(x, y);

		Altair::Color c;
		bool is_land;
		if (m_terrain_map->get_ocean_depth(x, y) > 0)
		{
			c = Altair::Color::blue;
			is_land = false;
		}
		else
		{
			c = m_land_color;
			is_land = true;
		}
		return Tile(height, is_land, get_structure(x, y), c);
	}

	std::shared_ptr<TerrainFeature> CelestialBody::get_structure(int x, int y) const
	{
		return m_terrain_map->get_structure(x, y);
	}

	std::vector<std::shared_ptr<TerrainFeature>> CelestialBody::get_structures() const { return m_structures; }

	void CelestialBody::set_structure(int x, int y, const std::shared_ptr<TerrainFeature>& structure)
	{
		for (const std::shared_ptr<TerrainFeature>& s : m_structures) { if (s == structure) { return; } }
		m_structures.push_back(structure);

		return m_terrain_map->set_structure(x, y, structure);
	}

	void CelestialBody::add_ocean(int x, int y) const
	{
		m_terrain_map->set_ocean_depth(x, y, m_terrain_map->get_ocean_depth(x, y) + 1);
	}

	void CelestialBody::erode() const { m_terrain_map->erode(); }

	bool CelestialBody::get_is_starting_candidate() const { return m_is_starting_candidate; }

	void CelestialBody::set_is_starting_candidate(bool is_starting_candidate)
	{
		m_is_starting_candidate = is_starting_candidate;
	}

	Item* CelestialBody::mine() { return new Item("Ore", 0.001, {"Ore"}); }

	std::string CelestialBody::serialize()
	{
		begin_file();
		add_to_file("Name", m_name);
		add_to_file("Theta", m_orbit.theta);
		add_to_file("SemiMajorAxis", m_orbit.semimajor_axis);
		add_to_file("StartingPosition", m_orbit.starting_position);
		add_to_file("SpriteX", m_sprite_x);
		add_to_file("SpriteY", m_sprite_y);
		add_to_file("LandColor", static_cast<int>(m_land_color.to_int()));
		add_to_file("IsStartingCandidate", m_is_starting_candidate);
		if (m_terrain_map != nullptr)
		{
			add_to_file("MapType", m_terrain_map->get_map_type());
			add_to_file("Map", m_terrain_map->serialize());
			for (uint32_t x = 0; x < m_terrain_map->get_map_width(); x++)
			{
				for (uint32_t y = 0; y < m_terrain_map->get_map_height(); y++)
				{
					std::shared_ptr<TerrainFeature> feature = m_terrain_map->get_structure(x, y);
					if (feature != nullptr)
					{
						begin_child("Structure");
						add_to_file("X", x);
						add_to_file("Y", y);
						end_child();
					}
				}
			}
		}

		return end_file();
	}
}
