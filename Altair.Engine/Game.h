#ifndef __GAME_H
#define __GAME_H
#include <chrono>

#include "FileSystem/FileReaders/FileReader.h"
#include "Graphics/SpriteRenderer.h"
#include "Audio/MusicPlayer.h"
#include "Graphics/Sprite.h"
#include "Graphics/TextItem.h"

namespace Altair
{
	template <class T>
	class Game : public Serializable
	{
	public:
		class State
		{
		protected:
			bool m_paused;
			std::string m_title;
			std::string m_announcement;
			bool m_substates_enabled;
		public:
			State();
			virtual ~State() = default;
			State(const State&) = default;
			State(State&&) = default;
			State& operator =(const State&) = default;
			State& operator =(State&&) = default;
			std::string get_title() const;
			std::string get_announcement() const;

			virtual void handle_key_event(T* game, sf::Event::KeyEvent key) = 0;
			virtual void update(T* game) = 0;
			virtual void draw(T* game) = 0;

			bool is_paused() const;
			bool has_substates() const;
		};

	protected:
		std::vector<State*> m_states;
		SpriteRenderer m_sprite_renderer;
		MusicPlayer m_music_player;
		bool m_running;
		double m_fps;

		State* m_start_state;
		State* m_pause_menu;
		std::unique_ptr<sf::Window> m_window;
		std::chrono::system_clock::time_point m_clock;
		bool m_keys[1024]{};
	public:
		Game(uint32_t max_x, uint32_t max_y, uint32_t sprite_width, uint32_t sprite_height, uint32_t tile_size,
		     uint32_t screen_width, uint32_t screen_height);

		void push_state(State* state);
		void pop_state();
		void pop_all_states();

		void quit();

		bool is_running() const;

		bool is_key_pressed(sf::Keyboard::Key keycode);

		void begin();

		void handle_key_event(sf::Event event, T* game);
		virtual void update() = 0;
		virtual void render() = 0;
		void draw(Sprite sprite);
		void draw(TextItem text);
	};

	template <class T>
	Game<T>::Game(uint32_t max_x, uint32_t max_y, uint32_t sprite_width, uint32_t sprite_height, uint32_t tile_size,
	              uint32_t screen_width, uint32_t screen_height)
		: m_sprite_renderer(max_x, max_y, sprite_width, sprite_height, tile_size, screen_width, screen_height)
	{
		m_start_state = nullptr;
		m_pause_menu = nullptr;
		m_running = true;
		m_fps = 0;
	}

	template <class T>
	void Game<T>::push_state(State* state) { m_states.push_back(state); }

	template <class T>
	void Game<T>::pop_state()
	{
		State* state = m_states.back();
		m_states.pop_back();
		if (state != m_pause_menu)
		{
			// Don't delete the pause menu.
			delete state;
		}
	}

	template <class T>
	void Game<T>::pop_all_states() { while (m_states.size() > 0) { pop_state(); } }

	template <class T>
	void Game<T>::quit() { m_running = false; }

	template <class T>
	bool Game<T>::is_running() const { return m_running; }

	template <class T>
	bool Game<T>::is_key_pressed(sf::Keyboard::Key keycode) { return m_keys[keycode]; }

	template <class T>
	void Game<T>::begin()
	{
		const int32_t ticks_per_second = 20;
		const int32_t skip_ticks = 1000 / ticks_per_second;
		const int32_t max_frameskip = 5;

		std::chrono::system_clock::time_point next_game_tick = std::chrono::system_clock::now();

		// Game loop.
		while (is_running())
		{
			int loops = 0;

			while (std::chrono::system_clock::now() > next_game_tick && loops < max_frameskip)
			{
				update();

				next_game_tick += std::chrono::milliseconds(skip_ticks);
				loops++;
			}

			render();
		}
	}

	template <class T>
	void Game<T>::handle_key_event(sf::Event event, T* game)
	{
		sf::Event::KeyEvent key = event.key;

		if (event.type == sf::Event::KeyPressed)
		{
			m_keys[key.code] = true;
			if (key.code == sf::Keyboard::Escape && !m_states.back()->has_substates())
			{
				if (m_states.size() > 1) { pop_state(); }
				else { push_state(m_pause_menu); }
			}
			else { m_states.back()->handle_key_event(game, key); }
		}
		else if (event.type == sf::Event::KeyReleased) { m_keys[key.code] = false; }
		else if (event.type == sf::Event::Closed) { quit(); }
	}

	template <class T>
	void Game<T>::draw(Sprite sprite) { m_sprite_renderer.render(sprite); }

	template <class T>
	void Game<T>::draw(TextItem text) { m_sprite_renderer.render(text); }

	template <class T>
	Game<T>::State::State()
	{
		m_paused = false;
		m_title = "";
		m_announcement = "";
		m_substates_enabled = false;
	}

	template <class T>
	std::string Game<T>::State::get_title() const { return m_title; }

	template <class T>
	std::string Game<T>::State::get_announcement() const { return m_announcement; }

	template <class T>
	bool Game<T>::State::is_paused() const { return m_paused; }

	template <class T>
	bool Game<T>::State::has_substates() const { return m_substates_enabled; }
}

#endif // !__GAME_H
