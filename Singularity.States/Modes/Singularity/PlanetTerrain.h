#ifndef __PLANET_TERRAIN_SCREEN_H
#define __PLANET_TERRAIN_SCREEN_H
#include "Singularity.Data/Game.h"

#include "Singularity.Data/UserInterface/Cursor/Cursor.h"
#include "Singularity.Data/UserInterface/Camera/Camera.h"
#include "Singularity.Data/Space/Bodies/CelestialBody.h"

namespace Singularity
{
	class PlanetTerrain final : public Game::State
	{
	private:
		enum class State
		{
			None,
			Designating,
			Inspecting
		};

		CelestialBody* m_current_body;
		Cursor m_cursor;
		Camera m_camera;
		State m_state;
	public:
		PlanetTerrain(CelestialBody* current_body);
		void handle_key_event(Game* game, sf::Event::KeyEvent event) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__PLANET_TERRAIN_SCREEN_H
