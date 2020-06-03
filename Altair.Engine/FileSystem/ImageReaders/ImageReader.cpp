#include "ImageReader.h"

namespace Altair
{
	ImageReader::ImageReader() { m_sprite_sheet.loadFromFile(R"(GameData\Assets\Textures\Sprites.png)"); }

	sf::Image ImageReader::get_sprite_sheet() const { return m_sprite_sheet; }
}
