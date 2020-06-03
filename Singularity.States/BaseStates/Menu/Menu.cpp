#include "Menu.h"

namespace Singularity
{
	Menu::Menu() = default;

	void Menu::move_cursor_up() { if (m_selected_item > 0) { m_selected_item--; } }

	void Menu::move_cursor_down() { if (m_selected_item < m_menu_items.size() - 1) { m_selected_item++; } }

	void Menu::print_menu_items(Game* game) { this->print_menu_items(game, 0, 1); }

	void Menu::print_menu_items(Game* game, int starting_x, int starting_y)
	{
		for (uint32_t i = 0; i < m_menu_items.size(); i++)
		{
			const Altair::TextItem item = m_menu_items.at(i)->to_text_item(
				starting_x, starting_y + static_cast<int32_t>(i),
				i == m_selected_item);
			game->draw(item);
		}
	}

	void Menu::handle_key_event(Game* game, sf::Event::KeyEvent event)
	{
		if (event.code == sf::Keyboard::Return) { m_menu_items.at(m_selected_item)->enter(game); }
		else if (event.code == sf::Keyboard::Up) { this->move_cursor_up(); }
		else if (event.code == sf::Keyboard::Down) { this->move_cursor_down(); }
		else { m_menu_items.at(m_selected_item)->key_input(event); }
	}

	unsigned int Menu::get_selected_index() const { return m_selected_item; }

	std::string Menu::get_selected_value() { return m_menu_items.at(m_selected_item)->get_value(); }
}
