#include "Sprite.h"

namespace Altair
{
	Sprite::Sprite()
	{
		m_x = 0;
		m_y = 0;
		m_color = Color(0, 0, 0);
		m_background_color = Color(0, 0, 0);
		m_sprite_x = 0;
		m_sprite_y = 0;
	}

	Sprite::Sprite(int32_t x, int32_t y, uint8_t sprite, Color color)
	{
		m_x = x;
		m_y = y;

		m_sprite_x = sprite % 16;
		m_sprite_y = sprite / 16;

		m_color = std::move(color);
		m_background_color = Color(0, 0, 0);
	}

	Sprite::Sprite(int32_t x, int32_t y, uint8_t sprite, uint16_t r, uint16_t g, uint16_t b)
	{
		m_x = x;
		m_y = y;

		m_sprite_x = sprite % 16;
		m_sprite_y = sprite / 16;

		m_color = Color(r, g, b);
		m_background_color = Color(0, 0, 0);
	}

	Sprite::Sprite(int32_t x, int32_t y, uint32_t sprite_x, uint32_t sprite_y, Color color)
	{
		m_x = x;
		m_y = y;

		m_sprite_x = sprite_x;
		m_sprite_y = sprite_y;

		m_color = std::move(color);
		m_background_color = Color(0, 0, 0);
	}

	Sprite::Sprite(int32_t x, int32_t y, uint32_t sprite_x, uint32_t sprite_y, uint16_t r, uint16_t g, uint16_t b)
	{
		m_x = x;
		m_y = y;

		m_sprite_x = sprite_x;
		m_sprite_y = sprite_y;

		m_color = Color(r, g, b);
		m_background_color = Color(0, 0, 0);
	}

	int32_t Sprite::get_x() const { return m_x; }

	int32_t Sprite::get_y() const { return m_y; }

	int32_t Sprite::get_sprite_x() const { return m_sprite_x; }

	int32_t Sprite::get_sprite_y() const { return m_sprite_y; }

	Color Sprite::get_color() const { return m_color; }

	Color Sprite::get_background_color() const { return m_background_color; }
}
