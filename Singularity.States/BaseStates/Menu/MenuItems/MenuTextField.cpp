#include "MenuTextField.h"

namespace Singularity
{
	MenuTextField::MenuTextField(std::string label, std::string default_value)
	{
		m_show_cursor = false;
		m_label = std::move(label);
		m_value = std::move(default_value);
		m_last_update = 0;
	}

	void MenuTextField::key_input(sf::Event::KeyEvent key)
	{
		if (key.code == sf::Keyboard::BackSpace) { backspace(); }
		else if (key.code >= sf::Keyboard::A && key.code <= sf::Keyboard::Z)
		{
			if (key.shift) { push_char(static_cast<char>('A' + key.code)); }
			else { push_char(static_cast<char>('a' + key.code)); }
		}
		else if (key.code >= sf::Keyboard::Num0 && key.code <= sf::Keyboard::Num9)
		{
			push_char(static_cast<char>('0' + key.code - sf::Keyboard::Num0));
		}
		else if (key.code == sf::Keyboard::Space) { push_char(' '); }
	}

	void MenuTextField::backspace() { if (!m_value.empty()) { m_value.pop_back(); } }

	void MenuTextField::push_char(char c) { m_value.push_back(c); }

	std::string MenuTextField::get_value() { return m_value; }

	Altair::TextItem MenuTextField::to_text_item(int x, int y, bool selected)
	{
		m_last_update++;
		if (m_last_update > 1000)
		{
			m_show_cursor = !m_show_cursor;
			m_last_update = 0;
		}

		std::string text = m_label + ": " + m_value;
		if (m_show_cursor && selected) { text += "_"; }

		Altair::Color c = Altair::Color::gray;
		if (selected) { c = Altair::Color::white; }
		return Altair::TextItem(x, y, text, c);
	}
}
