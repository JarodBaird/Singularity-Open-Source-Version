#ifndef __TILE_H
#define __TILE_H

#include "../../Altair.Engine/Graphics/Sprite.h"
#include "TerrainFeatures/TerrainFeature.h"
#include <memory>

namespace Singularity
{
	class Tile final : public Altair::Spriteable
	{
	private:
		std::shared_ptr<TerrainFeature> m_structure;
		unsigned char m_height;
		Altair::Color m_color;
		bool m_is_land;
	public:
		Tile();
		Tile(unsigned char height, bool is_land, std::shared_ptr<TerrainFeature> structure);
		Tile(unsigned char height, bool is_land, std::shared_ptr<TerrainFeature> structure, Altair::Color color);

		unsigned char get_height() const;
		bool get_is_land() const;

		Altair::Sprite to_sprite(int x, int y) override;
	};
}
#endif // !__TILE_H
