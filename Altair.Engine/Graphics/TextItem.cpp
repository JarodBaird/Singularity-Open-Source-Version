#include "TextItem.h"

#include <algorithm>
#include <utility>

#include "Color.h"

namespace Altair
{
	TextItem::TextItem(int32_t x, int32_t y, std::string text, Color color)
	{
		m_x = x;
		m_y = y;
		m_display_text = std::move(text);
		m_colors.push_back(ColorSplit{0, std::move(color)});
	}

	TextItem::TextItem(int32_t x, int32_t y, std::string text, std::vector<ColorSplit> colors): colors(
		std::move(colors))
	{
		m_x = x;
		m_y = y;
		m_display_text = std::move(text);
		for (const ColorSplit& color : colors) { m_colors.push_back(color); }
		std::sort(m_colors.begin(), m_colors.end(),
		          [](ColorSplit& i, ColorSplit& j) { return i.position < j.position; });
	}

	std::string TextItem::get_display_text() const { return m_display_text; }

	int32_t TextItem::get_x() const { return m_x; }

	int32_t TextItem::get_y() const { return m_y; }

	Color TextItem::get_color(uint64_t position)
	{
		if (m_colors.size() == 1) { return m_colors.at(0).color; }

		if (!m_colors.empty() && position >= 0)
		{
			for (uint32_t i = 0; i < m_colors.size(); i++)
			{
				if (m_colors.at(i).position > position)
				{
					if (i == 0) { return Color::white; }
					return m_colors.at(i - 1).color;
				}
			}
			return m_colors.back().color;
		}

		return Color::white;
	}
}
