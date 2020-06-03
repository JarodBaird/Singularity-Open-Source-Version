#ifndef __GENERATING_SCREEN_H
#define __GENERATING_SCREEN_H
#include "GalaxyGenSettings.h"

#include "Singularity.Data/Game.h"

namespace Singularity
{
	enum class GenerationStep
	{
		CreateSpecies,
		CreatePlanets,
		InitializeAliens,
		Finish
	};

	class GeneratingGalaxy final : public Game::State
	{
	private:
		Altair::Random m_random;
		GenerationStep m_next_step;
		GalaxyGenSettings m_settings;
	public:
		GeneratingGalaxy(unsigned int seed, GalaxyGenSettings settings);

		void handle_key_event(Game* game, sf::Event::KeyEvent event) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__GENERATING_SCREEN_H
