#ifndef __SPRITE_LOAD_TEST_H
#define __SPRITE_LOAD_TEST_H
#include "Singularity.Data/Game.h"

namespace Singularity
{
	class SpriteLoadTest final : public Game::State
	{
	public:
		void handle_key_event(Game* game, sf::Event::KeyEvent key) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__SPRITE_LOAD_TEST_H
