#ifndef __SINGULARITY_GAME_H
#define __SINGULARITY_GAME_H
#include "Model.h"
#include "Altair.Engine/Game.h"
#include "Altair.Engine/Graphics/SpriteRenderer.h"

namespace Singularity
{
	class Game final : public Altair::Game<Game>
	{
	public:
		std::unique_ptr<Model> model;

		Game(State* start_state, State* pause_menu, std::unique_ptr<sf::Window> window);

		void update() override;
		void render() override;

		std::string serialize() override;
	};
}
#endif // !__SINGULARITY_GAME_H
