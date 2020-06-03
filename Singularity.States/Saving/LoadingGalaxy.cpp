#include "LoadingGalaxy.h"
#include "Singularity.States/Modes/Singularity/PlanetTerrain.h"
#include "Singularity.States/Modes/Singularity/SolarSystem.h"
#include "SelectGameMode.h"
#include "Altair.Engine/FileSystem/DirectoryIterator.h"

namespace Singularity
{
	LoadingGalaxy::LoadingGalaxy(const std::string& galaxy_name)
	{
		m_number_of_stars = 0;
		m_galaxy_name = galaxy_name;
		m_folder_name = "GameData\\Saves\\" + galaxy_name;
		m_current_system = 0;
		m_current_load_state = LoadState::MetaData;
	}

	void LoadingGalaxy::handle_key_event(Game*, sf::Event::KeyEvent) {}

	void LoadingGalaxy::update(Game* game)
	{
		switch (this->m_current_load_state)
		{
		case LoadState::MetaData:
			{
			game->model->reset();

			game->model->galaxy_name = m_galaxy_name;

			Altair::SettingsReader metadata_reader("Galaxy.dat", m_folder_name);
			const std::string game_type = metadata_reader.get("GameType");
			game->model->game_type = GameType::None;
			if (game_type == "Singularity") { game->model->game_type = GameType::Singularity; }
			else if (game_type == "Civilian") { game->model->game_type = GameType::Civilian; }
			m_player_name = metadata_reader.get("Player");
			m_current_load_state = LoadState::Starchart;
			break;
			}
		case LoadState::Starchart:
			{
			const Altair::DirectoryIterator iter(m_folder_name + "\\Starchart");
			m_number_of_stars = iter.get_subdirectory_count();

			if (m_current_system < m_number_of_stars)
			{
				const std::string dir = iter.get_subdirectories().at(m_current_system);

				const Altair::SettingsReader system_reader("System.dat", m_folder_name + "\\Starchart\\" + dir);
				StarchartObject* obj = new StarchartObject(system_reader);

				const Altair::DirectoryIterator star_iter(m_folder_name + "\\Starchart\\" + dir);
				for (const std::string& child_file : star_iter.get_files())
				{
					if (child_file != "System.dat")
					{
						const Altair::SettingsReader child_reader(child_file, m_folder_name + "\\Starchart\\" + dir);

						if (child_file == "Parent.dat") { obj->add_parent(new CelestialBody(child_reader)); }
						else { obj->add_child(new CelestialBody(child_reader)); }
					}
				}

				game->model->starchart.push_back(obj);
				m_current_system++;
			}
			else
			{
				m_current_system = 0;
				m_current_load_state = LoadState::Civilizations;
			}
			break;
			}
		case LoadState::Civilizations:
			{
			const Altair::DirectoryIterator iter(m_folder_name + "\\Civilizations");
			m_number_of_stars = iter.get_file_count();
			if (m_current_system < m_number_of_stars)
			{
				const std::string current_civ = iter.get_files().at(m_current_system);
				const Altair::SettingsReader civ_reader(current_civ, m_folder_name + "\\Civilizations");
				Civilization* civ = new Civilization(civ_reader, game->model->starchart);
				if (civ->get_name() == m_player_name) { game->model->player = civ; }
				else { game->model->aliens.push_back(civ); }
				m_current_system++;
			}
			else { m_current_load_state = LoadState::Done; }

			break;
			}
		case LoadState::Done:
			{
			switch (game->model->game_type)
			{
			default:
			case GameType::Singularity:
				{
				game->pop_all_states();

				game->model->player = game->model->aliens.at(0);

				CelestialBody* homeworld = game->model->player->get_capital();

				game->push_state(new PlanetTerrain(homeworld));

				break;
				}
			case GameType::Civilian: { break; }
			case GameType::None:
				game->pop_state();
				game->push_state(new SelectGameMode());
				break;
			}
			break;
			}
		}
	}

	void LoadingGalaxy::draw(Game* game)
	{
		std::string text;
		switch (m_current_load_state)
		{
		case LoadState::Civilizations:
			text = std::to_string(this->m_current_system) + "/" + std::to_string(m_number_of_stars);
			text += " civilizations loaded.";
			game->draw(Altair::TextItem(0, 1, text, Altair::Color::yellow));
		case LoadState::Starchart:
			text = std::to_string(this->m_current_system) + "/" + std::to_string(m_number_of_stars);
			text += " systems loaded.";
			game->draw(Altair::TextItem(0, 0, text, Altair::Color::yellow));
		default: ;
		}
	}
}
