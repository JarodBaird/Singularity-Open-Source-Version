#include "MenuItem.h"

#include <utility>

namespace Singularity
{
	MenuItem::MenuItem() { m_disabled = false; }

	MenuItem::MenuItem(std::string text, std::function<void(Game*)> on_enter, bool disabled)
	{
		m_text = std::move(text);
		m_help_text = "";
		m_disabled = disabled;
		this->on_enter = std::move(on_enter);
	}

	MenuItem::MenuItem(const std::string& text, const std::string& help_text,
	                   const std::function<void(Game*)>& on_enter, bool disabled)
	{
		m_text = text;
		m_help_text = help_text;
		m_disabled = disabled;
		this->on_enter = on_enter;
	}

	std::string MenuItem::get_value() { return m_text; }

	void MenuItem::key_input(sf::Event::KeyEvent) { }

	void MenuItem::enter(Game* game) const { if (!m_disabled) { on_enter(game); } }

	Altair::TextItem MenuItem::to_text_item(int32_t x, int32_t y, bool selected)
	{
		Altair::Color c;
		if (m_disabled)
		{
			c = Altair::Color::gray;
			if (selected) { c = Altair::Color::red; }
		}
		else
		{
			c = Altair::Color::silver;
			if (selected) { c = Altair::Color::white; }
		}
		return Altair::TextItem(x, y, m_text, c);
	}
}
