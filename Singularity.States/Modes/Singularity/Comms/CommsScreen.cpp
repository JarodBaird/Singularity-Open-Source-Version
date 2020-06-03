#include "Singularity.Data/Game.h"
#include "CommsScreen.h"
#include "FirstContactScreen.h"

namespace Singularity
{
	CommsScreen::CommsScreen(Game* game)
	{
		for (Civilization* a : game->model->aliens)
		{
			m_menu_items.push_back(std::make_unique<MenuItem>(a->get_name(), [=](Game* g)
			{
				Civilization* alien = g->model->aliens.at(m_selected_item);
				const Relationship rel = g->model->player->get_relationship(alien);
				if (rel == Relationship::Uncontacted) { g->push_state(new FirstContactScreen(alien)); }
			}));
		}
	}

	void CommsScreen::update(Game*) {}

	void CommsScreen::draw(Game* game)
	{
		for (unsigned int i = 0; i < game->model->aliens.size(); i++)
		{
			std::string text;
			Altair::Color text_color = Altair::Color::white;
			Relationship rel = game->model->player->get_relationship(game->model->aliens.at(i));
			switch (rel)
			{
			case Relationship::War:
				text = "War!";
				text_color = Altair::Color::maroon;
				break;
			case Relationship::Aggressive:
				text = "Aggressive";
				text_color = Altair::Color::red;
				break;
			case Relationship::Unfriendly:
				text = "Unfriendly";
				text_color = Altair::Color::orange;
				break;
			case Relationship::Uncontacted:
				text = "No established language!";
				text_color = Altair::Color::white;
				break;
			case Relationship::Neutral:
				text = "Neutral";
				text_color = Altair::Color::white;
				break;
			case Relationship::Friendly:
				text = "Friendly";
				text_color = Altair::Color::green;
				break;
			case Relationship::Alliance:
				text = "Alliance";
				text_color = Altair::Color::blue;
				break;
			}
			game->draw(Altair::TextItem(0, i, "Alien",
			                            i == m_selected_item ? Altair::Color::yellow : Altair::Color::white));
			game->draw(Altair::TextItem(25, i, text, i == m_selected_item ? Altair::Color::yellow : text_color));
		}
	}
}
