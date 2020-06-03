#include "MenuSelectField.h"

#include <SFML/Graphics.hpp>
#include <utility>

namespace Singularity
{
	MenuSelectField::MenuSelectField() { m_selected_item = 0; }

	MenuSelectField::MenuSelectField(std::string label, std::vector<std::string> options)
	{
		m_label = std::move(label);
		m_options = std::move(options);
		m_selected_item = 0;
	}

	MenuSelectField::MenuSelectField(std::string label, std::vector<std::string> options, int32_t default_selection)
	{
		m_label = std::move(label);
		m_options = std::move(options);
		m_selected_item = default_selection;
	}

	void MenuSelectField::key_input(sf::Event::KeyEvent key)
	{
		if (key.code == sf::Keyboard::Left) { if (m_selected_item > 0) { m_selected_item--; } }
		if (key.code == sf::Keyboard::Right) { if (m_selected_item < m_options.size() - 1) { m_selected_item++; } }
	}

	std::string MenuSelectField::get_value() { return m_options.at(m_selected_item); }

	Altair::TextItem MenuSelectField::to_text_item(int32_t x, int32_t y, bool selected)
	{
		std::string str = m_label + ": ";

		uint32_t selected_option_start = 0;
		uint32_t selected_option_end = 0;

		for (uint32_t i = 0; i < m_options.size(); i++)
		{
			if (i == m_selected_item) { selected_option_start = static_cast<uint32_t>(str.size()); }
			str += m_options.at(i) + " ";
			if (i == m_selected_item) { selected_option_end = static_cast<uint32_t>(str.size()); }
		}

		if (selected)
		{
			const size_t size = m_label.size();

			return Altair::TextItem(x, y, str, {
				                        {0, Altair::Color::white}, {size + 2, Altair::Color::gray},
				                        {selected_option_start, Altair::Color::white},
				                        {selected_option_end, Altair::Color::gray}
			                        });
		}

		return Altair::TextItem(x, y, str, {
			                        {0, Altair::Color::gray}, {selected_option_start, Altair::Color::white},
			                        {selected_option_end, Altair::Color::gray}
		                        });
	}
}
