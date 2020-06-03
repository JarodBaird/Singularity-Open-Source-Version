#include "Tile.h"

#include <utility>
#include "TerrainFeatures/TerrainFeature.h"

namespace Singularity
{
	Tile::Tile() : Tile(0, true, nullptr, Altair::Color::white) { }

	Tile::Tile(unsigned char height, bool is_land, std::shared_ptr<TerrainFeature> structure) : Tile(
		height, is_land, std::move(structure), Altair::Color::white) { }

	Tile::Tile(unsigned char height, bool is_land, std::shared_ptr<TerrainFeature> structure, Altair::Color color)
	{
		m_height = height;
		m_structure = std::move(structure);
		m_color = std::move(color);
		m_is_land = is_land;
	}

	unsigned char Tile::get_height() const { return m_height; }

	bool Tile::get_is_land() const { return m_is_land; }

	Altair::Sprite Tile::to_sprite(int x, int y)
	{
		if (m_structure != nullptr)
		{
			const unsigned char sprite = m_structure->get_sprite();
			return Altair::Sprite(x, y, sprite % 16, sprite / 16, m_structure->get_color());
		}
		if (m_is_land) { return Altair::Sprite(x, y, 2, 2, m_color); }
		return Altair::Sprite(x, y, 7, 15, m_color);
	}
}
