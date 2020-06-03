#ifndef __COLOR_H
#define __COLOR_H
#include <string>
#include <array>

#include "../FileSystem/FileReaders/SettingsReader.h"

namespace Altair
{
	class Color
	{
	private:
		std::string m_name;
		int16_t m_r, m_g, m_b;
	public:
		Color();
		Color(int32_t color);
		Color(std::string name, int16_t r, int16_t g, int16_t b);
		Color(int16_t r, int16_t g, int16_t b);
		std::string get_name() const;
		int16_t get_r() const;
		int16_t get_g() const;
		int16_t get_b() const;
		uint32_t to_int() const;

		static void set_colors(std::unique_ptr<SettingsReader> settings);
		static std::array<Color*, 18> get_all_colors();

		static Color black;
		static Color gray;
		static Color red;
		static Color maroon;
		static Color orange;
		static Color brown;
		static Color yellow;
		static Color olive;
		static Color lime;
		static Color green;
		static Color aqua;
		static Color teal;
		static Color blue;
		static Color navy;
		static Color fuchsia;
		static Color purple;
		static Color white;
		static Color silver;
	};
}
#endif // !__COLOR_H
