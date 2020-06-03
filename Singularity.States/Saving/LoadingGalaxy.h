#ifndef __LOADING_GALAXY_H
#define __LOADING_GALAXY_H

#include "Singularity.Data/Game.h"

namespace Singularity
{
	class LoadingGalaxy final : public Game::State
	{
	private:
		enum class LoadState
		{
			MetaData,
			Starchart,
			Civilizations,
			Done
		};

		LoadState m_current_load_state;

		std::string m_galaxy_name;
		std::string m_folder_name;
		size_t m_number_of_stars;
		size_t m_current_system;

		std::string m_player_name;
	public:
		LoadingGalaxy(const std::string& galaxy_name);
		void handle_key_event(Game* game, sf::Event::KeyEvent event) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__LOADING_GALAXY_H
