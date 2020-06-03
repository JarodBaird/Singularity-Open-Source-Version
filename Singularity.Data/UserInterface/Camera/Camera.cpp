#include "Camera.h"

#include <climits>

#include "../../Settings/UniversalVariables.h"

namespace Singularity
{
	Camera::Camera()
	{
		m_x = 0;
		m_y = 0;
		m_max_x = INT_MAX;
		m_max_y = INT_MAX;

		m_camera_width = UniversalVariables::get_max_x() - 20;
		m_camera_height = UniversalVariables::get_max_y();
	}

	Camera::Camera(int32_t max_x, int32_t max_y)
	{
		m_x = 0;
		m_y = 0;
		m_max_x = max_x;
		m_max_y = max_y;

		m_camera_width = UniversalVariables::get_max_x() - 20;
		m_camera_height = UniversalVariables::get_max_y();
	}

	Camera::Camera(int32_t x, int32_t y, int32_t max_x, int32_t max_y)
	{
		m_x = x;
		m_y = y;
		m_max_x = max_x;
		m_max_y = max_y;

		m_camera_width = UniversalVariables::get_max_x() - 20;
		m_camera_height = UniversalVariables::get_max_y();
	}

	void Camera::move_up(int32_t speed)
	{
		m_y -= speed;
		if (m_y <= 0) { m_y = 0; }
	}

	void Camera::move_down(int32_t speed)
	{
		m_y += speed;
		const int32_t max_y = m_max_y - m_camera_height;
		if (m_y >= max_y)
		{
			if (max_y > 0) { m_y = max_y; }
			else { m_y = 0; }
		}
	}

	void Camera::move_left(int32_t speed)
	{
		m_x -= speed;
		if (m_x <= 0) { m_x = 0; }
	}

	void Camera::move_right(int32_t speed)
	{
		m_x += speed;
		const int32_t max_x = m_max_x - m_camera_width;
		if (m_x >= max_x)
		{
			m_x = max_x;
			if (max_x > 0) { m_x = max_x; }
			else { m_x = 0; }
		}
	}

	int32_t Camera::get_x() const { return m_x; }

	int32_t Camera::get_y() const { return m_y; }

	int32_t Camera::get_width() const { return m_camera_width; }

	int32_t Camera::get_height() const { return m_camera_height; }

	void Camera::set_x(int32_t x) { m_x = x; }

	void Camera::set_y(int32_t y) { m_y = y; }
}
