#ifndef __CREDITS_H
#define __CREDITS_H
#include "Singularity.Data/Game.h"

namespace Singularity
{
	class Credits final : public Game::State
	{
	public:
		Credits();
		void handle_key_event(Game* game, sf::Event::KeyEvent key) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__CREDITS_H
