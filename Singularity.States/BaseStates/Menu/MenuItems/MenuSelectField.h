#ifndef __MENU_SELECT_FIELD_H
#define __MENU_SELECT_FIELD_H
#include <vector>
#include <string>

#include "MenuItem.h"

namespace Singularity
{
	class MenuSelectField final : public MenuItem
	{
	private:
		std::string m_label;
		std::vector<std::string> m_options;
		uint32_t m_selected_item;
	public:
		MenuSelectField();
		MenuSelectField(std::string label, std::vector<std::string> options);
		MenuSelectField(std::string label, std::vector<std::string> options, int32_t default_selection);
		void key_input(sf::Event::KeyEvent key) override;
		std::string get_value() override;
		Altair::TextItem to_text_item(int32_t x, int32_t y, bool selected) override;
	};
}
#endif // !__MENU_SELECT_FIELD_H
