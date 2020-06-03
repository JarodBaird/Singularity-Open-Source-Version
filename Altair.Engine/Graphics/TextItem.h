#ifndef __TEXT_ITEM_H
#define __TEXT_ITEM_H
#include <string>
#include <vector>
#include "Color.h"

namespace Altair
{
	struct ColorSplit
	{
	public:
		uint64_t position;
		Color color;
	};

	class TextItem
	{
	private:
		int32_t m_x, m_y;
		std::string m_display_text;
		std::vector<ColorSplit> m_colors;
		std::vector<ColorSplit> colors;
	public:
		TextItem(int32_t x, int32_t y, std::string text, Color color);
		TextItem(int32_t x, int32_t y, std::string text, std::vector<ColorSplit> colors);
		std::string get_display_text() const;
		int32_t get_x() const;
		int32_t get_y() const;
		Color get_color(uint64_t position);
	};
}
#endif // !__TEXT_ITEM_H
