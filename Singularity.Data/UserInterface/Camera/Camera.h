#ifndef __CAMERA_H
#define __CAMERA_H

#include <cstdint>

namespace Singularity
{
	class Camera
	{
	private:
		int32_t m_x;
		int32_t m_y;
		int32_t m_max_x;
		int32_t m_max_y;
		int32_t m_camera_height;
		int32_t m_camera_width;
	public:
		Camera();
		Camera(int32_t max_x, int32_t max_y);
		Camera(int32_t x, int32_t y, int32_t max_x, int32_t max_y);
		void move_up(int32_t speed = 1);
		void move_down(int32_t speed = 1);
		void move_left(int32_t speed = 1);
		void move_right(int32_t speed = 1);
		int32_t get_x() const;
		int32_t get_y() const;
		int32_t get_width() const;
		int32_t get_height() const;
		void set_x(int x);
		void set_y(int y);
	};
}
#endif // !__CAMERA_H
