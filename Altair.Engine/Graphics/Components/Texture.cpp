#include "Texture.h"
#include "../../FileSystem/ImageReaders/ImageReader.h"
#include <GL/glew.h>

namespace Altair
{
	Texture::Texture()
	{
		const ImageReader reader = ImageReader();
		const sf::Image sprite_sheet = reader.get_sprite_sheet();
		const sf::Uint8* pixel_pointer = sprite_sheet.getPixelsPtr();
		const sf::Vector2u image_size = sprite_sheet.getSize();

		m_width = image_size.x;
		m_height = image_size.y;

		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixel_pointer);
		glBindTexture(GL_TEXTURE_2D, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		m_texture_id = result;
	}

	void Texture::bind() const { glBindTexture(GL_TEXTURE_2D, m_texture_id); }

	void Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

	uint32_t Texture::get_width() const { return m_width; }
	uint32_t Texture::get_height() const { return m_height; }
}
