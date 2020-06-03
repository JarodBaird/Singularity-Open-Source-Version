#include "Cursor.h"
#include "Altair.Engine/Graphics/Sprite.h"

namespace Singularity
{
	Cursor::Cursor()
	{
		m_x = 0;
		m_y = 0;
	}

	Cursor::Cursor(int32_t x, int32_t y)
	{
		m_x = x;
		m_y = y;
	}

	int32_t Cursor::get_x() const { return m_x; }

	int32_t Cursor::get_y() const { return m_y; }

	void Cursor::set_x(int32_t x) { m_x = x; }

	void Cursor::set_y(int32_t y) { m_y = y; }

	void Cursor::move_up(int32_t delta) { m_y -= delta; }

	void Cursor::move_right(int32_t delta) { m_x += delta; }

	void Cursor::move_down(int32_t delta) { m_y += delta; }

	void Cursor::move_left(int32_t delta) { m_x -= delta; }

	Altair::Sprite Cursor::to_sprite() { return to_sprite(get_x(), get_y()); }

	Altair::Sprite Cursor::to_sprite(int32_t x, int32_t y) { return Altair::Sprite(x, y, 8, 5, Altair::Color::yellow); }
}
