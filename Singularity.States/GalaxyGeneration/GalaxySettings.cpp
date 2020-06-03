#include "GalaxySettings.h"
#include "Singularity.Data/Game.h"
#include "GeneratingGalaxy.h"
#include "Singularity.States/BaseStates/Menu/MenuItems/MenuSelectField.h"

namespace Singularity
{
	GalaxySettings::GalaxySettings()
	{
		m_title = "Galaxy Creation";

		Altair::Random r;

		std::string galaxy_name;

		switch (r.next_int(0, 3))
		{
		default:
		case 0:
			galaxy_name = "M" + std::to_string(r.next_int(1, 100));
			break;
		case 1:
			galaxy_name = "IC " + std::to_string(r.next_int(1, 5000));
			break;
		case 2:
			galaxy_name = "NGC " + std::to_string(r.next_int(1, 10000));
			break;
		}

		m_menu_items.push_back(std::make_unique<MenuTextField>("Name", galaxy_name));
		m_menu_items.push_back(std::make_unique<MenuTextField>("Seed", std::to_string(r.next_int())));

		m_menu_items.push_back(std::make_unique<MenuSelectField>("Galaxy Size",
		                                                         std::vector<std::string>{
			                                                         "Dwarf", "Small", "Medium", "Large", "RAM-Killer"
		                                                         }, 2));
		m_menu_items.push_back(std::make_unique<MenuSelectField>("History Length (Years)",
		                                                         std::vector<std::string>{
			                                                         "Very Short (5)", "Short (25)", "Medium (50)",
			                                                         "Long (75)", "Very Long (100)"
		                                                         }, 2));

		m_menu_items.push_back(std::make_unique<MenuItem>("Generate Galaxy", [=](Game* game)
		{
			GalaxyGenSettings generation_settings;

			generation_settings.galaxy_name = m_menu_items.at(0)->get_value();
			generation_settings.seed = static_cast<int>(std::hash<std::string>{}(m_menu_items.at(1)->get_value()));
			const std::string galaxy_size = m_menu_items.at(2)->get_value();
			if (galaxy_size == "RAM-Killer") { generation_settings.size = GalaxySize::ExtraLarge; }
			else if (galaxy_size == "Large") { generation_settings.size = GalaxySize::Large; }
			else if (galaxy_size == "Medium") { generation_settings.size = GalaxySize::Medium; }
			else if (galaxy_size == "Small") { generation_settings.size = GalaxySize::Small; }
			else { generation_settings.size = GalaxySize::Dwarf; }

			std::string history_length = m_menu_items.at(3)->get_value();
			if (galaxy_size == "Very Long (100)") { generation_settings.history_length = HistoryLength::VeryLong; }
			else if (galaxy_size == "Long (75)") { generation_settings.history_length = HistoryLength::Long; }
			else if (galaxy_size == "Medium (50)") { generation_settings.history_length = HistoryLength::Medium; }
			else if (galaxy_size == "Short (25)") { generation_settings.history_length = HistoryLength::Short; }
			else { generation_settings.history_length = HistoryLength::VeryShort; }

			game->model->seed = generation_settings.seed;

			game->pop_all_states();
			game->push_state(new GeneratingGalaxy(generation_settings.seed, generation_settings));
		}));
	}

	void GalaxySettings::update(Game*) {}

	void GalaxySettings::draw(Game* game) { this->print_menu_items(game); }
}
