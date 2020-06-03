#include "FirstContactScreen.h"
#include "Singularity.Data/Game.h"

namespace Singularity
{
	FirstContactScreen::FirstContactScreen(Civilization* species_being_contacted)
	{
		m_species_being_contacted = species_being_contacted;
		m_title = "Plan First Contact";

		m_menu_items.push_back(std::make_unique<MenuItem>("Fireworks", [=](Game* game)
		{
			Relationship rel;
			bool likes_fireworks = false;
			if (rand() % 2 == 0) { likes_fireworks = true; }
			if (likes_fireworks) { rel = Relationship::Friendly; }
			else { rel = Relationship::Unfriendly; }
			game->model->player->set_relationship(m_species_being_contacted, rel);
			game->pop_state();
		}));

		m_menu_items.push_back(std::make_unique<MenuItem>("Sound", [=](Game* game)
		{
			Relationship rel;
			bool likes_fireworks = false;
			if (rand() % 2 == 0) { likes_fireworks = true; }
			if (likes_fireworks) { rel = Relationship::Friendly; }
			else { rel = Relationship::Unfriendly; }
			game->model->player->set_relationship(m_species_being_contacted, rel);
			game->pop_state();
		}));

		m_menu_items.push_back(std::make_unique<MenuItem>("Radio Transmission", [=](Game* game)
		{
			game->model->player->set_relationship(m_species_being_contacted, Relationship::Neutral);
			game->pop_state();
		}));

		m_menu_items.push_back(std::make_unique<MenuItem>("Invasion", [=](Game* game)
		{
			game->model->player->set_relationship(m_species_being_contacted, Relationship::War);
			game->pop_state();
		}));
	}

	void FirstContactScreen::handle_key_event(Game*, sf::Event::KeyEvent) { }

	void FirstContactScreen::update(Game*) { }

	void FirstContactScreen::draw(Game* game) { this->print_menu_items(game); }
}
