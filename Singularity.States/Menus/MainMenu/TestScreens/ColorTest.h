#ifndef __COLOR_TEST_SCREEN_H
#define __COLOR_TEST_SCREEN_H

#include "Singularity.Data/Game.h"

namespace Singularity
{
	class ColorTest final : public Game::State
	{
	public:
		ColorTest();
		void handle_key_event(Game* game, sf::Event::KeyEvent key) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__COLOR_TEST_SCREEN_H
