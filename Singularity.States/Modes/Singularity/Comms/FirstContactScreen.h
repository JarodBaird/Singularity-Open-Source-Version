#ifndef __FIRST_CONTACT_SCREEN_H
#define __FIRST_CONTACT_SCREEN_H
#include "Singularity.Data/Civilization/Civilization.h"
#include "Singularity.States/BaseStates/Menu/Menu.h"

namespace Singularity
{
	class FirstContactScreen final : public Menu
	{
	private:
		Civilization* m_species_being_contacted;
	public:
		FirstContactScreen(Civilization* species_being_contacted);
		void handle_key_event(Game* game, sf::Event::KeyEvent event) override;
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__FIRST_CONTACT_SCREEN_H
