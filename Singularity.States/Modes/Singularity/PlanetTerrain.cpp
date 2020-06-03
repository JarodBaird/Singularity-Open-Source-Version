#include "PlanetTerrain.h"
#include "Singularity.Data/Game.h"
#include "Singularity.Data/Terrain/TerrainFeatures/Artificial/Mine.h"
#include "Singularity.Data/Terrain/TerrainFeatures/Artificial/Refinery.h"
#include "Singularity.Data/Terrain/TerrainFeatures/Artificial/City.h"
#include "Singularity.Data/Terrain/TerrainFeatures/Artificial/Generator.h"
#include "Singularity.Data/Terrain/TerrainFeatures/Artificial/Farm.h"
#include "Singularity.Data/Settings/UniversalVariables.h"
#include "SolarSystem.h"
#include "Starchart.h"

namespace Singularity
{
	PlanetTerrain::PlanetTerrain(CelestialBody* current_body)
	{
		m_paused = false;
		m_current_body = current_body;
		m_cursor = Cursor();
		m_camera = Camera(current_body->get_map_width(), current_body->get_map_height());
		m_state = State::None;
	}

	void PlanetTerrain::handle_key_event(Game* game, sf::Event::KeyEvent event)
	{
		int move_speed = 1;
		if (event.shift) { move_speed = 5; }

		switch (event.code)
		{
		case sf::Keyboard::Space:
			{
			game->model->is_paused = !game->model->is_paused;
			break;
			}
		case sf::Keyboard::F:
			{
			if (m_state == State::Designating)
			{
				const int x = m_cursor.get_x();
				const int y = m_cursor.get_y();

				m_current_body->set_structure(x, y, std::make_shared<Farm>(m_current_body, game->model->player));
			}
			break;
			}
		case sf::Keyboard::M:
			{
			if (m_state == State::Designating)
			{
				const int x = m_cursor.get_x();
				const int y = m_cursor.get_y();

				m_current_body->set_structure(x, y, std::make_shared<Mine>(m_current_body, game->model->player));
			}
			break;
			}
		case sf::Keyboard::R:
			{
			if (m_state == State::Designating)
			{
				const int x = m_cursor.get_x();
				const int y = m_cursor.get_y();

				m_current_body->set_structure(x, y, std::make_shared<Refinery>(m_current_body, game->model->player));
			}
			break;
			}
		case sf::Keyboard::Y:
			{
			if (m_state == State::Designating)
			{
				const int x = m_cursor.get_x();
				const int y = m_cursor.get_y();

				m_current_body->set_structure(x, y, std::make_shared<City>(m_current_body, game->model->player));
			}
			break;
			}
		case sf::Keyboard::G:
			{
			if (m_state == State::Designating)
			{
				const int x = m_cursor.get_x();
				const int y = m_cursor.get_y();

				m_current_body->set_structure(x, y, std::make_shared<Generator>(m_current_body, game->model->player));
			}
			break;
			}

		case sf::Keyboard::Up:
			{
			if (m_state == State::Designating || m_state == State::Inspecting) { m_cursor.move_up(move_speed); }
			else { m_camera.move_up(move_speed); }
			break;
			}

		case sf::Keyboard::Down:
			{
			if (m_state == State::Designating || m_state == State::Inspecting) { m_cursor.move_down(move_speed); }
			else { m_camera.move_down(move_speed); }
			break;
			}

		case sf::Keyboard::Left:
			{
			if (m_state == State::Designating || m_state == State::Inspecting) { m_cursor.move_left(move_speed); }
			else { m_camera.move_left(move_speed); }
			break;
			}

		case sf::Keyboard::Right:
			{
			if (m_state == State::Designating || m_state == State::Inspecting) { m_cursor.move_right(move_speed); }
			else { m_camera.move_right(move_speed); }
			break;
			}
		case sf::Keyboard::S:
			{
			game->push_state(new SolarSystem(m_current_body->get_system()));
			break;
			}
		case sf::Keyboard::C:
			{
			game->push_state(new Starchart(new Camera(), new Cursor()));
			break;
			}
		case sf::Keyboard::K:
			{
			if (m_state == State::None)
			{
				m_state = State::Inspecting;
				m_cursor.set_x(m_camera.get_x());
				m_cursor.set_y(m_camera.get_y());
				m_substates_enabled = true;
			}
			break;
			}
		case sf::Keyboard::D:
			{
			if (m_state == State::None)
			{
				m_state = State::Designating;
				m_cursor.set_x(m_camera.get_x());
				m_cursor.set_y(m_camera.get_y());
				m_substates_enabled = true;
			}
			break;
			}
		case sf::Keyboard::Escape:
			{
			m_state = State::None;
			m_substates_enabled = false;
			break;
			}
		default: ;
		}
	}

	void PlanetTerrain::update(Game*) { }

	void PlanetTerrain::draw(Game* game)
	{
		const int32_t camera_width = m_camera.get_width();
		const int32_t camera_height = m_camera.get_height();
		const int32_t camera_x = m_camera.get_x();
		const int32_t camera_y = m_camera.get_y();

		const std::vector<Altair::ColorSplit> menu_colors = {
			{0, Altair::Color::green},
			{4, Altair::Color::white}
		};

		for (int x = m_camera.get_x(); x < camera_width + camera_x; x++)
		{
			for (int y = m_camera.get_y(); y < camera_height + camera_y; y++)
			{
				if (x < m_current_body->get_map_width() && y < m_current_body->get_map_height())
				{
					Tile val = m_current_body->get_terrain_at(x, y);

					const int32_t sprite_x = x - camera_x;
					const int32_t sprite_y = y - camera_y;

					game->draw(val.to_sprite(sprite_x, sprite_y));
				}
			}
		}

		if (m_state == State::Designating || m_state == State::Inspecting)
		{
			game->draw(m_cursor.to_sprite(m_cursor.get_x() - m_camera.get_x(), m_cursor.get_y() - m_camera.get_y()));
		}
		if (m_state == State::Designating)
		{
			game->draw(Altair::TextItem(camera_width + 1, 1, "[m] Mine", menu_colors));
			game->draw(Altair::TextItem(camera_width + 1, 2, "[r] Refinery", menu_colors));
			game->draw(Altair::TextItem(camera_width + 1, 3, "[y] City", menu_colors));
			game->draw(Altair::TextItem(camera_width + 1, 4, "[g] Generator", menu_colors));
			game->draw(Altair::TextItem(camera_width + 1, 5, "[f] Farm", menu_colors));
		}
		else if (m_state == State::Inspecting)
		{
			std::shared_ptr<TerrainFeature> structure = m_current_body->
				get_structure(m_cursor.get_x(), m_cursor.get_y());
			if (structure == nullptr)
			{
				game->draw(Altair::TextItem(camera_width + 1, 1, "No Structure", Altair::Color::white));
			}
			else
			{
				game->draw(Altair::TextItem(camera_width + 1, 1, structure->get_name(), Altair::Color::white));
				std::vector<std::string> description = structure->get_description();
				for (size_t i = 0; i < description.size(); i++)
				{
					int32_t y = static_cast<int32_t>(i) + 3;
					game->draw(Altair::TextItem(camera_width + 1, y, description.at(i), Altair::Color::white));
				}
			}
		}
		else if (m_state == State::None)
		{
			const uint32_t menu_x = camera_width + 1;
			game->draw(Altair::TextItem(menu_x, 4, "[k] Look", menu_colors));
			game->draw(Altair::TextItem(menu_x, 5, "[d] Designate", menu_colors));
			game->draw(Altair::TextItem(menu_x, 6, "[s] Solar System", menu_colors));
			game->draw(Altair::TextItem(menu_x, 7, "[c] Starchart", menu_colors));

			const std::string energy = "Energy: " + std::to_string(game->model->player->get_energy());
			const std::string food = "Food: " + std::to_string(game->model->player->get_food());

			game->draw(Altair::TextItem(menu_x, 1, energy, Altair::Color::yellow));
			game->draw(Altair::TextItem(menu_x, 2, food, Altair::Color::green));
		}

		if (game->model->is_paused)
		{
			const uint32_t bottom_of_screen = UniversalVariables::get_max_y() - 1;
			const Altair::TextItem paused_sprite = Altair::TextItem(0, bottom_of_screen, "PAUSED", Altair::Color::red);
			game->draw(paused_sprite);
		}
	}
}
