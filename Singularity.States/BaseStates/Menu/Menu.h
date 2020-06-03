#ifndef __MENU_H
#define __MENU_H
#include <vector>
#include "Singularity.Data/Game.h"
#include "MenuItems/MenuTextField.h"

namespace Singularity
{
	class Menu : public Game::State
	{
	protected:
		std::vector<std::unique_ptr<MenuItem>> m_menu_items;
		unsigned int m_selected_item = 0;
		void move_cursor_up();
		void move_cursor_down();
		void print_menu_items(Game* game);
		void print_menu_items(Game* game, int starting_x, int starting_y);
	public:
		Menu();
		virtual ~Menu() = default;
		Menu(const Menu&) = default;
		Menu(Menu&&) = default;
		Menu& operator =(const Menu&) = default;
		Menu& operator =(Menu&&) = default;
		void handle_key_event(Game* game, sf::Event::KeyEvent event) override;
		unsigned int get_selected_index() const;
		std::string get_selected_value();
	};
}
#endif // !__MENU_H
