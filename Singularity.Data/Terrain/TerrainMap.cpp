#include "TerrainMap.h"

#include <utility>

namespace Singularity
{
	TerrainMap::TerrainTile::TerrainTile()
	{
		land_height = 0;
		ocean_depth = 0;
		structure = nullptr;
	}

	TerrainMap::TerrainMap(uint32_t height, std::string map_type, std::string map)
	{
		m_height = height;
		m_width = height * 2;
		m_map_type = std::move(map_type);

		m_map = std::vector<TerrainTile>(get_number_of_tiles());
		for (uint32_t x = 0; x < m_width; x++)
		{
			for (uint32_t y = 0; y < m_height; y++)
			{
				TerrainTile tile;
				tile.land_height = 5;
				if (!map.empty())
				{
					const uint32_t index = 2 * to_index(x, y);
					tile.land_height = map.at(index) + 128;
					tile.ocean_depth = map.at(index + 1) + 128;
				}
				tile.structure = nullptr;
				m_map.at(x * m_height + y) = tile;
			}
		}
	}

	uint32_t TerrainMap::to_index(uint32_t x, uint32_t y) const
	{
		x %= get_map_width();

		return x * m_height + y;
	}

	std::string TerrainMap::get_map_type() const { return m_map_type; }

	uint32_t TerrainMap::get_map_width() const { return m_width; }

	uint32_t TerrainMap::get_map_height() const { return m_height; }

	uint32_t TerrainMap::get_number_of_tiles() const { return m_width * m_height; }

	uint8_t TerrainMap::get_terrain_height(uint32_t x, uint32_t y) { return m_map[this->to_index(x, y)].land_height; }

	void TerrainMap::set_terrain_height(uint32_t x, uint32_t y, uint8_t height)
	{
		height = height % 128;
		m_map[this->to_index(x, y)].land_height = height;
	}

	unsigned char TerrainMap::get_ocean_depth(uint32_t x, uint32_t y) { return m_map[this->to_index(x, y)].ocean_depth; }

	void TerrainMap::set_ocean_depth(uint32_t x, uint32_t y, uint8_t depth)
	{
		depth = depth % 128;
		m_map[this->to_index(x, y)].ocean_depth = depth;
	}

	uint16_t TerrainMap::get_total_height(uint32_t x, uint32_t y)
	{
		const TerrainTile tile = m_map[to_index(x, y)];
		return tile.land_height + tile.ocean_depth;
	}

	std::shared_ptr<TerrainFeature> TerrainMap::get_structure(uint32_t x, uint32_t y)
	{
		return m_map[this->to_index(x, y)].structure;
	}

	void TerrainMap::set_structure(uint32_t x, uint32_t y, std::shared_ptr<TerrainFeature> structure)
	{
		m_map[this->to_index(x, y)].structure = std::move(structure);
	}

	void TerrainMap::erode()
	{
		bool eroding = true;
		uint32_t number_of_runs = 0;

		while (eroding && number_of_runs < 1000)
		{
			eroding = false;
			for (uint32_t x = 0; x < this->get_map_width(); x++)
			{
				for (uint32_t y = 0; y < this->get_map_height(); y++)
				{
					const bool result = erode(x, y);
					if (result) { eroding = true; }
				}
			}
			number_of_runs++;
		}
	}

	bool TerrainMap::erode(uint32_t x, uint32_t y)
	{
		const unsigned char ocean_depth = this->get_ocean_depth(x, y);
		if (ocean_depth == 0) { return false; }

		const int h = this->get_total_height(x, y);

		for (int32_t dx = -1; dx <= 1; dx++)
		{
			for (int32_t dy = -1; dy <= 1; dy++)
			{
				if (dx != 0 && dy != 0)
				{
					// If not the center.
					if (y + dy >= 0 && y + dy < this->get_map_height())
					{
						const int32_t adjacent_height = this->get_total_height(x + dx, y + dy);

						if (adjacent_height + 1 < h)
						{
							this->set_ocean_depth(x, y, ocean_depth - 1);
							this->set_ocean_depth(x + dx, y + dy, this->get_ocean_depth(x, y) + 1);
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	std::string TerrainMap::serialize()
	{
		std::string file;
		for (uint32_t i = 0; i < this->get_number_of_tiles(); i++)
		{
			file += std::to_string(m_map[i].land_height - 128);
			file += std::to_string(m_map[i].ocean_depth - 128);
		}
		return file;
	}
}
