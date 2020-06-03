#include "Civilization.h"
#include "../Space/StarchartObject.h"

namespace Singularity
{
	Civilization::Civilization()
	{
		m_capital = nullptr;
		m_energy = 1000000;
		m_food = 1000000;
		m_name = "Random Alien Civ " + std::to_string(rand() % 1000);
	}

	Civilization::Civilization(Altair::SettingsReader reader, const std::vector<StarchartObject*>& starchart)
	{
		m_capital = nullptr;
		m_name = reader.get("Name");
		m_energy = reader.get_long("Energy");
		m_food = reader.get_long("Food");

		const std::string system_name = reader.get("CapitalSystem");
		const std::string body_name = reader.get("CapitalPlanet");

		for (StarchartObject* s : starchart)
		{
			if (s->get_name() == system_name)
			{
				for (CelestialBody* b : s->get_children())
				{
					if (b->get_name() == body_name)
					{
						set_capital(b);
						break;
					}
				}
			}
		}
	}

	void Civilization::set_relationship(Civilization* civilization, Relationship relationship)
	{
		m_relationships[civilization] = relationship;
	}

	Relationship Civilization::get_relationship(Civilization* civilization) { return m_relationships[civilization]; }

	CelestialBody* Civilization::get_capital() const { return m_capital; }

	void Civilization::set_capital(CelestialBody* capital)
	{
		m_capital = capital;
		reveal_system(capital->get_system());
		claim_system(capital->get_system());
	}

	uint64_t Civilization::get_energy() const { return m_energy; }

	void Civilization::update_energy(int64_t delta) { m_energy += delta; }

	uint64_t Civilization::get_food() const { return m_food; }

	void Civilization::update_food(int64_t delta) { m_food += delta; }

	std::string Civilization::get_name() const { return m_name; }

	void Civilization::reveal_system(StarchartObject* system)
	{
		for (StarchartObject* obj : m_revealed_systems) { if (obj == system) { return; } }
		m_revealed_systems.push_back(system);
	}

	std::vector<StarchartObject*> Civilization::get_revealed_systems() const { return m_revealed_systems; }

	void Civilization::claim_system(StarchartObject* system) { m_claimed_systems.push_back(system); }

	std::vector<StarchartObject*> Civilization::get_claimed_systems() const { return m_claimed_systems; }

	void Civilization::add_fleet(Fleet* fleet) { m_fleets.push_back(fleet); }

	std::vector<Fleet*> Civilization::get_fleets() const { return m_fleets; }

	void Civilization::update()
	{
		m_energy--;
		m_food--;
	}

	void Civilization::add_request(Request* request) { m_requests.add(request); }

	Request* Civilization::get_next_request(Entity* entity) { return m_requests.get_first_completable(entity); }

	std::string Civilization::serialize()
	{
		begin_file();
		add_to_file("Name", m_name);
		add_to_file("Energy", m_energy);
		add_to_file("Food", m_food);
		add_to_file("CapitalSystem", m_capital->get_system()->get_name());
		add_to_file("CapitalPlanet", m_capital->get_name());

		for (StarchartObject* s : m_revealed_systems)
		{
			begin_child("RevealedSystem");
			add_to_file("Name", s->get_name());
			end_child();
		}

		for (StarchartObject* s : m_claimed_systems)
		{
			begin_child("ClaimedSystem");
			add_to_file("Name", s->get_name());
			end_child();
		}

		return end_file();
	}
}
