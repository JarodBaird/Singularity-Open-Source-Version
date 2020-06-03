#ifndef __CURSOR_H
#define __CURSOR_H
#include "../../../Altair.Engine/Graphics/Sprite.h"

namespace Singularity
{
	class Cursor final : public Altair::Spriteable
	{
	private:
		int32_t m_x;
		int32_t m_y;
	public:
		Cursor();
		Cursor(int32_t x, int32_t y);
		int32_t get_x() const;
		int32_t get_y() const;
		void set_x(int32_t x);
		void set_y(int32_t y);
		void move_up(int32_t delta);
		void move_right(int32_t delta);
		void move_down(int32_t delta);
		void move_left(int32_t delta);
		Altair::Sprite to_sprite();
		Altair::Sprite to_sprite(int32_t x, int32_t y) override;
	};
}
#endif // !__CURSOR_H
