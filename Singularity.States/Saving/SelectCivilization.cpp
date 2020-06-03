#include "SelectCivilization.h"
#include "Singularity.States/Modes/Singularity/PlanetTerrain.h"
#include "Singularity.States/Modes/Singularity/SolarSystem.h"
#include "Singularity.Data/Terrain/TerrainFeatures/Artificial/City.h"
#include "Singularity.Data/Terrain/TerrainFeatures/Artificial/Mine.h"

namespace Singularity
{
	SelectCivilization::SelectCivilization()
	{
		m_title = "Pick a Starting Planet";
		m_menu_items_generated = false;
	}

	void SelectCivilization::update(Game* game)
	{
		if (!m_menu_items_generated)
		{
			for (StarchartObject* star : game->model->starchart)
			{
				for (CelestialBody* body : star->get_children())
				{
					if (body->get_is_starting_candidate())
					{
						m_candidates.push_back(body);
						m_menu_items.push_back(std::make_unique<MenuItem>(body->get_name(), [=](Game* g)
						{
							CelestialBody* selected_planet = m_candidates.at(this->get_selected_index());

							Civilization* civ = new Civilization();
							civ->set_capital(selected_planet);

							g->model->aliens.push_back(civ);
							g->model->player = civ;

							Altair::Random r = Altair::Random();

							// Generate cities.
							int number_of_cities = 0;
							while (number_of_cities < 100)
							{
								const int x = r.next_int(selected_planet->get_map_width());
								const int y = r.next_int(selected_planet->get_map_height());
								const bool is_land = selected_planet->get_terrain_at(x, y).get_is_land();

								if (is_land)
								{
									selected_planet->set_structure(
										x, y, std::make_shared<City>(selected_planet, g->model->player));
									number_of_cities++;
								}
							}

							int number_of_mines = 0;
							while (number_of_mines < 100)
							{
								const int x = r.next_int(selected_planet->get_map_width());
								const int y = r.next_int(selected_planet->get_map_height());
								const bool is_land = selected_planet->get_terrain_at(x, y).get_is_land();

								if (is_land)
								{
									selected_planet->set_structure(
										x, y, std::make_shared<Mine>(selected_planet, g->model->player));
									number_of_mines++;
								}
							}

							g->pop_all_states();
							g->push_state(new PlanetTerrain(selected_planet));
						}));
					}
				}
			}
			m_menu_items_generated = true;
		}
	}

	void SelectCivilization::draw(Game* game) { this->print_menu_items(game); }
}
