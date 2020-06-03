#include "Fleet.h"

namespace Singularity
{
	Fleet::Fleet(int32_t x, int32_t y)
	{
		m_x = x;
		m_y = y;
		m_owner = nullptr;

		m_color = Altair::Color::blue;
		m_tile = 0x0b;

		m_ticks_since_last_update = 0;
		m_current_request = nullptr;
	}

	Fleet::~Fleet() { for (Entity* ship : m_ships) { delete ship; } }

	void Fleet::add_ship(Entity* ship) { m_ships.push_back(ship); }

	void Fleet::wander()
	{
		const int32_t r = rand() % 3;
		int32_t x = this->get_x();
		int32_t y = this->get_y();

		switch (r)
		{
		case 0:
			x++;
			break;
		case 1:
			x--;
			break;
		case 2:
			y++;
			break;
		case 3:
			y--;
			break;
		default:
			break;
		}

		this->move_towards(x, y);
	}

	void Fleet::update()
	{
		m_ticks_since_last_update++;

		if (m_current_request == nullptr)
		{
			// Attempt to get a request.
			m_current_request = nullptr;
			if (m_owner != nullptr)
			{
				m_current_request = m_owner->get_next_request(this);
				if (m_current_request != nullptr) { m_current_request->update(this); }
			}
			else { this->wander(); }
		}

		if (m_current_request != nullptr)
		{
			// Don't change this to an else.
			if (m_current_request->get_is_complete()) { m_current_request = nullptr; }
			else { m_current_request->update(this); }
		}
	}
}
