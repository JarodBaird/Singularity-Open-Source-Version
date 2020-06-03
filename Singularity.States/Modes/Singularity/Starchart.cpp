#include "Starchart.h"
#include "SolarSystem.h"
#include "PlanetTerrain.h"
#include "Singularity.Data/Requests/RequestTypes/SurveyRequest.h"
#include "Singularity.Data/Settings/UniversalVariables.h"
#include "Comms/CommsScreen.h"

namespace Singularity
{
	Starchart::Starchart(Camera* camera, Cursor* cursor)
	{
		m_paused = false;
		m_camera = camera;
		m_cursor = cursor;
	}

	void Starchart::handle_key_event(Game* game, sf::Event::KeyEvent event)
	{
		if (event.code == sf::Keyboard::C) { game->push_state(new CommsScreen(game)); }

		if (event.code == sf::Keyboard::S)
		{
			game->model->player->add_request(new SurveyRequest(m_cursor->get_x(), m_cursor->get_y()));
		}

		if (event.code == sf::Keyboard::Return)
		{
			for (StarchartObject* obj : game->model->player->get_revealed_systems())
			{
				if (obj->get_x() == m_cursor->get_x() && obj->get_y() == m_cursor->get_y())
				{
					if (obj->get_parent()->get_can_visit()) { game->push_state(new PlanetTerrain(obj->get_parent())); }
					else { game->push_state(new SolarSystem(obj)); }
				}
			}
		}

		const int max_x = UniversalVariables::get_max_x() - 21;
		const int max_y = UniversalVariables::get_max_y() - 1;

		int move_speed = 1;

		if (game->is_key_pressed(sf::Keyboard::LShift) || game->is_key_pressed(sf::Keyboard::RShift))
		{
			move_speed = 5;
		}

		if (event.code == sf::Keyboard::Up)
		{
			m_cursor->move_up(move_speed);
			if (m_cursor->get_y() < m_camera->get_y()) { m_camera->set_y(m_cursor->get_y()); }
		}
		if (event.code == sf::Keyboard::Down)
		{
			m_cursor->move_down(move_speed);
			if (m_cursor->get_y() > m_camera->get_y() + max_y) { m_camera->set_y(m_cursor->get_y() - max_y); }
		}
		if (event.code == sf::Keyboard::Left)
		{
			m_cursor->move_left(move_speed);
			if (m_cursor->get_x() < m_camera->get_x()) { m_camera->set_x(m_cursor->get_x()); }
		}
		if (event.code == sf::Keyboard::Right)
		{
			m_cursor->move_right(move_speed);
			if (m_cursor->get_x() > m_camera->get_x() + max_x) { m_camera->set_x(m_cursor->get_x() - max_x); }
		}
	}

	void Starchart::update(Game*) { }

	void Starchart::draw(Game* game)
	{
		const int screen_width = UniversalVariables::get_max_x() - 20;

		for (StarchartObject* body : game->model->player->get_revealed_systems())
		{
			const int x = body->get_x() - m_camera->get_x();
			const int y = body->get_y() - m_camera->get_y();
			if (x < screen_width) { game->draw(body->to_sprite(x, y)); }
		}

		for (Entity* entity : game->model->entities)
		{
			const int x = entity->get_x() - m_camera->get_x();
			const int y = entity->get_y() - m_camera->get_y();
			if (x < screen_width)
			{
				if (entity->get_owner() == game->model->player) { game->draw(entity->to_sprite(x, y)); }
				else
				{
					for (StarchartObject* owned_system : game->model->player->get_claimed_systems())
					{
						const int a = entity->get_x() - owned_system->get_x();
						const int b = entity->get_y() - owned_system->get_y();
						if (sqrt(a * a + b * b) < 10)
						{
							game->draw(entity->to_sprite(x, y));
							break;
						}
					}
				}
			}
		}

		const int cursor_x = m_cursor->get_x() - m_camera->get_x();
		const int cursor_y = m_cursor->get_y() - m_camera->get_y();

		game->draw(m_cursor->to_sprite(cursor_x, cursor_y));
	}
}
