#include <vector>
#include <thread>
#include <sstream>
#include <iomanip>

#include "Altair.Engine/FileSystem/ImageReaders/ImageReader.h"
#include "Altair.Engine/FileSystem/DirectoryIterator.h"
#include "Game.h"

#include "Altair.Engine/Graphics/Color.h"
#include "Settings/UniversalVariables.h"
#include "Settings/GalacticVariables.h"
#include "Model.h"
#include "Civilization/Civilization.h"
#include "Space/StarchartObject.h"

namespace Singularity
{
	Game::Game(State* start_state, State* pause_menu, std::unique_ptr<sf::Window> window)
		: Altair::Game<Game>(UniversalVariables::get_max_x(), UniversalVariables::get_max_y(),
		                     UniversalVariables::sprite_width, UniversalVariables::sprite_height,
		                     UniversalVariables::tile_size,
		                     UniversalVariables::screen_width, UniversalVariables::screen_height)
	{
		m_start_state = start_state;
		m_pause_menu = pause_menu;
		m_window = std::move(window);

		Altair::Color::set_colors(std::make_unique<Altair::SettingsReader>("Colors.cfg"));

		Altair::SettingsReader physics_reader = Altair::SettingsReader("Physics.cfg", "GameData\\Raws");
		GalacticVariables::speed_of_light = physics_reader.get_int("SpeedOfLight");

		model = std::make_unique<Model>();
		model->calendar = new Calendar(
			CalendarSettings{
				physics_reader.get_uint("TicksPerDay"),
				physics_reader.get_uint("DaysPerMonth"),
				physics_reader.get_uint("MonthsPerYear")
			}
		);

		const std::string elements_directory = "GameData\\Raws\\Elements";
		const Altair::DirectoryIterator element_iterator(elements_directory);
		for (const std::string& file : element_iterator.get_files())
		{
			const Altair::SettingsReader reader(file, elements_directory);
			model->elements.push_back(new Element(reader));
		}

		const std::string compounds_directory = "GameData\\Raws\\Compounds";
		const Altair::DirectoryIterator compound_iterator(compounds_directory);
		for (const std::string& file : compound_iterator.get_files())
		{
			const Altair::SettingsReader reader(file, compounds_directory);
			model->compounds.push_back(new Compound(reader, model->elements));
		}

		push_state(m_start_state);

		m_running = true;

		m_music_player.set_volume(UniversalVariables::music_volume);
		m_music_player.play();
	}

	void Game::update()
	{
		// Handle input.
		sf::Event window_event{};
		while (m_window->pollEvent(window_event)) { handle_key_event(window_event, this); }

		State* current_state = m_states.back();
		if (model != nullptr && !current_state->is_paused() && !model->is_paused)
		{
			model->calendar->tick();

			for (StarchartObject* starchart_obj : model->starchart) { starchart_obj->update(); }

			for (Entity* entity : model->entities)
			{
				entity->update();
				if (entity->get_owner() != nullptr)
				{
					for (StarchartObject* starchart_obj : model->starchart)
					{
						const int a = entity->get_x() - starchart_obj->get_x();
						const int b = entity->get_y() - starchart_obj->get_y();
						if (sqrt(a * a + b * b) < 10)
						{
							entity->get_owner()->reveal_system(starchart_obj);
							break;
						}
					}
				}
			}

			for (Civilization* civ : model->aliens) { civ->update(); }

			if (model->player != nullptr) { model->player->update(); }
		}
		current_state->update(this);
	}

	void Game::render()
	{
		Altair::SpriteRenderer::clear_screen();

		m_sprite_renderer.begin();

		m_states.back()->draw(this);

		const std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();

		const std::chrono::duration<double, std::milli> delta_time = end_time - m_clock;

		m_clock = end_time;

		const int bottom_of_screen = UniversalVariables::get_max_y() - 1;

		Altair::TextItem title_sprite = Altair::TextItem(0, 0, m_states.back()->get_title(), Altair::Color::blue);
		m_sprite_renderer.render(title_sprite);
		Altair::TextItem announcement_sprite = Altair::TextItem(0, bottom_of_screen,
		                                                        m_states.back()->get_announcement(),
		                                                        Altair::Color::white);
		m_sprite_renderer.render(announcement_sprite);

		if (UniversalVariables::show_fps)
		{
			const double fps = 1000 / delta_time.count();
			m_fps = (fps + 99 * m_fps) / 100;
			std::stringstream stream;
			stream << std::fixed << std::setprecision(0) << m_fps;
			const std::string fps_string = "FPS: " + stream.str();
			const int fps_length = static_cast<int>(fps_string.size());

			Altair::TextItem fps_sprite = Altair::TextItem(UniversalVariables::get_max_x() - fps_length,
			                                               bottom_of_screen, fps_string, Altair::Color::white);
			m_sprite_renderer.render(fps_sprite);
		}

		Altair::SpriteRenderer::end();
		m_sprite_renderer.draw();

		// Swap buffers.
		m_window->display();
	}

	std::string Game::serialize()
	{
		begin_file();
		if (model->player != nullptr) { add_to_file("Player", model->player->get_name()); }
		std::string game_type;
		switch (model->game_type)
		{
		default:
		case GameType::None:
			game_type = "None";
			break;
		case GameType::Singularity:
			game_type = "Singularity";
			break;
		case GameType::Civilian:
			game_type = "Civilian";
			break;
		}
		add_to_file("GameType", game_type);
		return end_file();
	}
}
