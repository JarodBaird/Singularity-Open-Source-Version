#ifndef __IMAGE_READER_H
#define __IMAGE_READER_H

#include <SFML/Graphics.hpp>

namespace Altair
{
	class ImageReader
	{
	private:
		sf::Image m_sprite_sheet;
	public:
		ImageReader();
		sf::Image get_sprite_sheet() const;
	};
}
#endif // !__IMAGE_READER_H
