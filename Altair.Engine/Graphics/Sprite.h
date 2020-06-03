#ifndef __SPRITE_RENDER_REQUEST_H
#define __SPRITE_RENDER_REQUEST_H
#include "Color.h"

namespace Altair
{
	class Sprite
	{
	private:
		int32_t m_x, m_y;
		Color m_color;
		Color m_background_color;
		int32_t m_sprite_x, m_sprite_y;
	public:
		Sprite();
		Sprite(int32_t x, int32_t y, uint8_t sprite, Color color);
		Sprite(int32_t x, int32_t y, uint8_t sprite, uint16_t r, uint16_t g, uint16_t b);
		Sprite(int32_t x, int32_t y, uint32_t sprite_x, uint32_t sprite_y, Color color);
		Sprite(int32_t x, int32_t y, uint32_t sprite_x, uint32_t sprite_y, uint16_t r, uint16_t g, uint16_t b);
		int32_t get_x() const;
		int32_t get_y() const;
		int32_t get_sprite_x() const;
		int32_t get_sprite_y() const;
		Color get_color() const;
		Color get_background_color() const;
	};

	class Spriteable
	{
	public:
		virtual Sprite to_sprite(int32_t x, int32_t y) = 0;
		Spriteable() = default;
		virtual ~Spriteable() = default;
		Spriteable(const Spriteable&) = default;
		Spriteable(Spriteable&&) = default;
		Spriteable& operator =(const Spriteable&) = default;
		Spriteable& operator =(Spriteable&&) = default;
	};
}
#endif // !__SPRITE_RENDER_REQUEST_H
