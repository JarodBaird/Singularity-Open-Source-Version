#include "ColorTest.h"
#include "Altair.Engine/Graphics/Color.h"

namespace Singularity
{
	ColorTest::ColorTest()
	{
		m_title = "Current Color Palette";
		m_announcement = "Press <esc> to return.";
	}

	void ColorTest::handle_key_event(Game*, sf::Event::KeyEvent) { }

	void ColorTest::update(Game*) { }

	void ColorTest::draw(Game* game)
	{
		const int second_column = 20;

		auto colors = Altair::Color::get_all_colors();
		int index = 2;
		for (Altair::Color* color : colors)
		{
			int column = 0;
			if (index % 2 == 1) { column = second_column; }

			game->draw(Altair::TextItem(column, index / 2, color->get_name(), *color));

			index++;
		}
	}
}
