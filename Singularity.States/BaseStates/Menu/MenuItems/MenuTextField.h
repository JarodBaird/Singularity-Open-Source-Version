#ifndef __MENU_TEXT_FIELD_H
#define __MENU_TEXT_FIELD_H
#include "MenuItem.h"

namespace Singularity
{
	class MenuTextField final : public MenuItem
	{
	private:
		std::string m_value;
		std::string m_label;

		int m_last_update;

		bool m_show_cursor;

		void backspace();
		void push_char(char c);
	public:
		MenuTextField(std::string label = "", std::string default_value = "");
		void key_input(sf::Event::KeyEvent key) override;
		std::string get_value() override;
		Altair::TextItem to_text_item(int32_t x, int32_t y, bool selected) override;
	};
}
#endif // !__MENU_TEXT_FIELD_H
