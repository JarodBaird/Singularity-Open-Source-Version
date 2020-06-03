#ifndef __STARCHART_SCREEN_H
#define __STARCHART_SCREEN_H

#include "Singularity.Data/Game.h"
#include "Singularity.Data/UserInterface/Camera/Camera.h"
#include "Singularity.Data/UserInterface/Cursor/Cursor.h"

namespace Singularity
{
	class Starchart final : public Game::State
	{
	private:
		Camera* m_camera;
		Cursor* m_cursor;
	public:
		Starchart(Camera* camera, Cursor* cursor);
		void handle_key_event(Game* game, sf::Event::KeyEvent event) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__STARCHART_SCREEN_H
