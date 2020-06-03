#ifndef __MENU_ITEM_H
#define __MENU_ITEM_H
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

#include "Altair.Engine/Graphics/TextItem.h"

namespace Singularity
{
	class Game;

	class MenuItem
	{
	private:
		std::string m_text;
		std::string m_help_text;
		std::function<void(Game*)> on_enter;
	protected:
		bool m_disabled;
	public:
		MenuItem();
		MenuItem(std::string text, std::function<void(Game*)> on_enter, bool disabled = false);
		MenuItem(const std::string& text, const std::string& help_text = "",
		         const std::function<void(Game*)>& on_enter = nullptr,
		         bool disabled = false);
		virtual ~MenuItem() = default;
		MenuItem(const MenuItem&) = default;
		MenuItem(MenuItem&&) = default;
		MenuItem& operator =(const MenuItem&) = default;
		MenuItem& operator =(MenuItem&&) = default;
		void enter(Game* game) const;
		virtual std::string get_value();
		virtual void key_input(sf::Event::KeyEvent key);
		virtual Altair::TextItem to_text_item(int x, int y, bool selected);
	};
}
#endif // !__MENU_ITEM_H
