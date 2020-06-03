#include "SavingGalaxy.h"
#include <direct.h>
#include <fstream>
#include <filesystem>

#include "../Menus/MainMenu/MainMenu.h"
#include "Singularity.Data/Space/StarchartObject.h"

namespace Singularity
{
	SavingGalaxy::SavingGalaxy(const std::string& galaxy_name)
	{
		const std::string parent = "GameData\\Saves";
		std::filesystem::create_directory(parent);

		m_folder_name = parent + "\\" + galaxy_name;
		std::filesystem::create_directory(m_folder_name);

		m_current_system = 0;
		m_current_save_state = SaveState::MetaData;
	}

	void SavingGalaxy::save(const std::string& file_name, Altair::Serializable* contents)
	{
		std::ofstream file;
		file.open(file_name);
		const std::string serialized = contents->serialize();
		file.write(serialized.c_str(), serialized.size());
		file.close();
	}

	void SavingGalaxy::create_metadata(Game* game) const { this->save(m_folder_name + "\\Galaxy.dat", game); }

	void SavingGalaxy::create_system(StarchartObject* star) const
	{
		const std::string starchart_directory = m_folder_name + "\\Starchart\\";
		std::filesystem::create_directory(starchart_directory);
		const std::string star_directory = starchart_directory + star->get_name();
		std::filesystem::create_directory(star_directory);

		this->save(star_directory + "\\System.dat", star);

		CelestialBody* parent = star->get_parent();
		this->save(star_directory + "\\Parent.dat", parent);

		for (CelestialBody* body : star->get_children())
		{
			this->save(star_directory + "\\" + body->get_name() + ".dat", body);
		}
	}

	void SavingGalaxy::create_civilization(Civilization* civ) const
	{
		const std::string civ_directory = m_folder_name + "\\Civilizations\\";
		std::filesystem::create_directory(civ_directory);
		this->save(civ_directory + civ->get_name() + ".dat", civ);
	}

	void SavingGalaxy::handle_key_event(Game*, sf::Event::KeyEvent) { }

	void SavingGalaxy::update(Game* game)
	{
		switch (m_current_save_state)
		{
		case SaveState::MetaData:
			{
			create_metadata(game);
			m_current_save_state = SaveState::Starchart;
			break;
			}
		case SaveState::Starchart:
			{
			if (m_current_system >= game->model->starchart.size())
			{
				m_current_save_state = SaveState::Civilizations;
				m_current_system = 0;
			}
			else
			{
				StarchartObject* star = game->model->starchart.at(m_current_system);
				create_system(star);

				m_current_system++;
			}

			break;
			}
		case SaveState::Civilizations:
			{
			if (m_current_system >= game->model->aliens.size())
			{
				m_current_save_state = SaveState::Done;
				m_current_system = 0;
			}
			else
			{
				Civilization* civ = game->model->aliens.at(m_current_system);
				create_civilization(civ);

				m_current_system++;
			}

			break;
			}
		case SaveState::Done:
			{
			game->model->reset();

			game->pop_all_states();
			game->push_state(new MainMenu());
			break;
			}
		}
	}

	void SavingGalaxy::draw(Game* game)
	{
		std::string text = std::to_string(m_current_system) + "/" + std::to_string(game->model->starchart.size());
		text += " systems saved.";
		game->draw(Altair::TextItem(0, 0, text, Altair::Color::yellow));
	}
}
