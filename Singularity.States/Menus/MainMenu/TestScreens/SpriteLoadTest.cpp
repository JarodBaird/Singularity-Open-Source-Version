#include "SpriteLoadTest.h"

namespace Singularity
{
	void SpriteLoadTest::handle_key_event(Game*, sf::Event::KeyEvent) { }

	void SpriteLoadTest::update(Game*) { }

	void SpriteLoadTest::draw(Game* game)
	{
		auto colors = Altair::Color::get_all_colors();
		for (int x = 0; x < 500; x++)
		{
			for (int y = 0; y < 250; y++)
			{
				game->draw(Altair::Sprite(x, y, x % 16, y % 16, *colors[((x + y) % colors.size())]));
			}
		}
	}
}
