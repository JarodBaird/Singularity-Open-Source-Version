#include "GeneratingGalaxy.h"
#include "../BaseStates/Menu/Menu.h"

#include "Singularity.Data/Space/SystemFactory.h"
#include "../Menus/MainMenu/MainMenu.h"
#include "../Saving/SavingGalaxy.h"

namespace Singularity
{
	GeneratingGalaxy::GeneratingGalaxy(unsigned int seed, GalaxyGenSettings settings)
	{
		m_title = "Generating Galaxy...";

		m_random = Altair::Random(seed);
		m_next_step = GenerationStep::CreateSpecies;
		m_settings = std::move(settings);
	}

	void GeneratingGalaxy::handle_key_event(Game* game, sf::Event::KeyEvent event)
	{
		if (m_next_step == GenerationStep::Finish)
		{
			if (event.code == sf::Keyboard::D)
			{
				game->pop_state();
				game->push_state(new MainMenu());
			}
			if (event.code == sf::Keyboard::Return)
			{
				game->model->galaxy_name = m_settings.galaxy_name;
				game->pop_state();
				game->push_state(new SavingGalaxy(game->model->galaxy_name));
			}
		}
	}

	void GeneratingGalaxy::update(Game* game)
	{
		switch (m_next_step)
		{
		case GenerationStep::CreateSpecies:
			{
			m_next_step = GenerationStep::CreatePlanets;
			break;
			}
		case GenerationStep::CreatePlanets:
			{
			int map_size = 75;
			int star_clusters = 8;
			switch (m_settings.size)
			{
			case GalaxySize::Dwarf:
				map_size = 50;
				star_clusters = 2;
				break;
			case GalaxySize::Small:
				map_size = 60;
				star_clusters = 4;
				break;
			case GalaxySize::Medium:
				map_size = 75;
				star_clusters = 8;
				break;
			case GalaxySize::Large:
				map_size = 100;
				star_clusters = 16;
				break;
			case GalaxySize::ExtraLarge:
				map_size = 125;
				star_clusters = 32;
				break;
			}

			SystemFactory generator(game->model->elements, game->model->compounds);
			for (int c = 0; c < star_clusters; c++)
			{
				const int32_t base_x = m_random.next_int(map_size);
				const int32_t base_y = m_random.next_int(map_size);
				const int32_t number_of_systems = m_random.next_int(5, 10);

				for (int n = 0; n < number_of_systems; n++)
				{
					const uint32_t delta_x = m_random.next_int(map_size / 4) - map_size / 8;
					const uint32_t delta_y = m_random.next_int(map_size / 4) - map_size / 8;

					const uint32_t x = base_x + delta_x;
					const uint32_t y = base_y + delta_y;

					std::string name = "C" + std::to_string(c) + " S" + std::to_string(n);

					game->model->starchart.push_back(generator.create(name, x, y));
				}
			}

			m_next_step = GenerationStep::InitializeAliens;
			break;
			}
		case GenerationStep::InitializeAliens:
			{
			//for (int i = 0; i < 5; i++) {
			//	Civilization* civ = new Civilization();
			//	game->model->aliens.push_back(civ);

			//	StarchartObject* system = nullptr;
			//	bool systemFound = false;
			//	do {
			//		StarchartObject* star = game->model->starchart[rand() % game->model->starchart.size()];
			//		system = star;

			//		std::vector<CelestialBody*> children = star->getChildren();
			//		if (children.size() > 0) {
			//			systemFound = true;
			//		}
			//	} while (!systemFound);

			//	system->addChild(body);

			//	bool cityHasSpawned = false;
			//	for (int j = 0; j < 100; j++) {
			//		const int x = rand() % 100;
			//		const int y = rand() % 50;

			//		if (body->getTerrainAt(x, y).getIsLand() && body->getStructure(x, y) == nullptr) {
			//			body->addStructure(new City(x, y));
			//			cityHasSpawned = true;
			//		}
			//	}

			//	civ->setCapital(body);
			//	Fleet* fleet = new Fleet(system->getX() + 1, system->getY());
			//	Entity* ship = new Entity();
			//	ship->setOwner(civ);
			//	fleet->addShip(ship);
			//	fleet->setOwner(civ);
			//	civ->addFleet(fleet);
			//	game->model->fleets.push_back(fleet);
			// }

			m_next_step = GenerationStep::Finish;
			break;
			}
		case GenerationStep::Finish: { break; }
		}
	}

	void GeneratingGalaxy::draw(Game* game)
	{
		switch (m_next_step)
		{
		default:
		case GenerationStep::Finish:
			game->draw(Altair::TextItem(0, 7, "Press <D> to discard.", Altair::Color::white));
			game->draw(Altair::TextItem(0, 6, "Press <return> to save.", Altair::Color::white));
			game->draw(Altair::TextItem(0, 3, "DONE!", Altair::Color::green));
		case GenerationStep::InitializeAliens:
			game->draw(Altair::TextItem(0, 2, "Initializing Aliens...", Altair::Color::yellow));
		case GenerationStep::CreatePlanets:
			game->draw(Altair::TextItem(0, 1, "Creating Planets...", Altair::Color::yellow));
			break;
		}
	}
}
