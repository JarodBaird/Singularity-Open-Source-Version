#include "Window.h"

#include <GL/glew.h>

namespace Altair
{
	Window::Window(uint32_t screen_width, uint32_t screen_height, bool full_screen)
		: sf::Window(sf::VideoMode(screen_width, screen_height), "OpenGL",
		             full_screen ? sf::Style::None : sf::Style::Default) { glewInit(); }
}
