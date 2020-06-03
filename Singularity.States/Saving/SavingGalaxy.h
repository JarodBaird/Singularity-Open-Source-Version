#ifndef __SAVING_GALAXY_H
#define __SAVING_GALAXY_H

#include "Singularity.Data/Game.h"

namespace Singularity
{
	class SavingGalaxy final : public Game::State
	{
	private:
		enum class SaveState
		{
			MetaData,
			Starchart,
			Civilizations,
			Done
		};

		SaveState m_current_save_state;

		std::string m_folder_name;
		unsigned int m_current_system;
		static void save(const std::string& file_name, Altair::Serializable* contents);
		void create_metadata(Game* game) const;
		void create_system(StarchartObject* star) const;
		void create_civilization(Civilization* civ) const;
	public:
		SavingGalaxy(const std::string& galaxy_name);
		void handle_key_event(Game* game, sf::Event::KeyEvent event) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__SAVING_GALAXY_H
