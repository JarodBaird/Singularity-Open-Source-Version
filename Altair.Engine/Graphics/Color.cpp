#include "Color.h"
#include <array>

namespace Altair
{
	Color Color::black = Color("Black", 0, 0, 0);
	Color Color::gray = Color("Gray", 0, 0, 0);
	Color Color::red = Color("Red", 0, 0, 0);
	Color Color::maroon = Color("Maroon", 0, 0, 0);
	Color Color::orange = Color("Orange", 0, 0, 0);
	Color Color::brown = Color("Brown", 0, 0, 0);
	Color Color::yellow = Color("Yellow", 0, 0, 0);
	Color Color::olive = Color("Olive", 0, 0, 0);
	Color Color::lime = Color("Lime", 0, 0, 0);
	Color Color::green = Color("Green", 0, 0, 0);
	Color Color::aqua = Color("Aqua", 0, 0, 0);
	Color Color::teal = Color("Teal", 0, 0, 0);
	Color Color::blue = Color("Blue", 0, 0, 0);
	Color Color::navy = Color("Navy", 0, 0, 0);
	Color Color::fuchsia = Color("Fuchsia", 0, 0, 0);
	Color Color::purple = Color("Purple", 0, 0, 0);
	Color Color::white = Color("White", 0, 0, 0);
	Color Color::silver = Color("Silver", 0, 0, 0);

	Color::Color()
	{
		m_r = 0;
		m_g = 0;
		m_b = 0;
	}

	Color::Color(int32_t color)
	{
		m_r = color & 0xFF;
		m_g = color >> 8 & 0xFF;
		m_b = color >> 16;
	}

	Color::Color(int16_t r, int16_t g, int16_t b)
	{
		m_r = r;
		m_g = g;
		m_b = b;
	}

	Color::Color(std::string name, int16_t r, int16_t g, int16_t b)
	{
		m_name = std::move(name);
		m_r = r;
		m_g = g;
		m_b = b;
	}

	void Color::set_colors(std::unique_ptr<SettingsReader> settings)
	{
		std::array<Color*, 18> colors = get_all_colors();

		for (Color* color : colors)
		{
			std::string color_name = color->get_name();

			const int16_t r = settings->get_short(color_name + "_R");
			const int16_t g = settings->get_short(color_name + "_G");
			const int16_t b = settings->get_short(color_name + "_B");

			color->m_r = r;
			color->m_g = g;
			color->m_b = b;
		}
	}

	std::array<Color*, 18> Color::get_all_colors()
	{
		const std::array<Color*, 18> colors =
		{
			&red, &maroon, &orange, &brown, &yellow, &olive, &lime, &green, &aqua,
			&teal, &blue, &navy, &fuchsia, &purple, &white, &silver, &gray, &black
		};
		return colors;
	}

	std::string Color::get_name() const { return m_name; }

	int16_t Color::get_r() const { return m_r; }

	int16_t Color::get_g() const { return m_g; }

	int16_t Color::get_b() const { return m_b; }

	uint32_t Color::to_int() const { return m_b << 16 | m_g << 8 | m_r; }
}
