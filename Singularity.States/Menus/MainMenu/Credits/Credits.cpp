#include "Credits.h"

namespace Singularity
{
	Credits::Credits()
	{
		m_title = "Credits";
		m_announcement = "Press <esc> to return.";
	}

	void Credits::handle_key_event(Game*, sf::Event::KeyEvent) { }

	void Credits::update(Game*) { }

	void Credits::draw(Game* game)
	{
		game->draw(Altair::TextItem(0, 2, "Copyright (c) 2017. All rights reserved by Jarod Baird.",
		                            Altair::Color::white));
		game->draw(Altair::TextItem(0, 3, "All music composed and produced by Kevin MacLeod.", Altair::Color::white));
		game->draw(Altair::TextItem(
			0, 4, "Audio and window management made using Simple and Fast Multimedia Library (sfml).",
			Altair::Color::white));
		game->draw(
			Altair::TextItem(0, 5, "Graphics made using OpenGL Extension Wrangler (glew).", Altair::Color::white));

		game->draw(Altair::TextItem(0, 7, "Users of this software are free to modify the GameData folder.",
		                            Altair::Color::white));

		game->draw(Altair::TextItem(0, 9, "Dedicated to Sierra", Altair::Color::white));
		game->draw(Altair::Sprite(20, 9, 0, 1, Altair::Color::red));
		game->draw(Altair::Sprite(21, 9, 3, 0, Altair::Color::red));
		game->draw(Altair::Sprite(22, 9, 1, 1, Altair::Color::red));
	}
}
