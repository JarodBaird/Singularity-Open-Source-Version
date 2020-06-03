#ifndef __WINDOW_H
#define __WINDOW_H

#include <SFML/Window.hpp>

namespace Altair
{
	class Window final : public sf::Window
	{
	public:
		Window(uint32_t screen_width, uint32_t screen_height, bool full_screen);
	};
}
#endif // !__WINDOW_H
