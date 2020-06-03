#ifndef __CIVILIZATION_H
#define __CIVILIZATION_H
#include <map>

#include "../Space/Bodies/CelestialBody.h"
#include "Civilization.h"
#include "../Requests/RequestList.h"

namespace Singularity
{
	class Fleet;

	enum class Relationship
	{
		War = -3,
		Aggressive = -2,
		Unfriendly = -1,
		Uncontacted = 0,
		Neutral = 1,
		Friendly = 2,
		Alliance = 3
	};

	class Civilization final : public Altair::Serializable
	{
	private:
		std::string m_name;

		Altair::Color m_color;

		std::map<Civilization*, Relationship> m_relationships;
		CelestialBody* m_capital;

		uint64_t m_energy;
		std::vector<int> m_inventory;
		uint64_t m_food;

		std::vector<Fleet*> m_fleets;

		std::vector<StarchartObject*> m_revealed_systems;
		std::vector<StarchartObject*> m_claimed_systems;

		RequestList m_requests;
	public:
		Civilization();
		Civilization(Altair::SettingsReader reader, const std::vector<StarchartObject*>& starchart);
		void update();

		void set_relationship(Civilization* civilization, Relationship relationship);
		Relationship get_relationship(Civilization* civilization);

		void set_capital(CelestialBody* capital);
		CelestialBody* get_capital() const;

		uint64_t get_energy() const;
		void update_energy(int64_t delta);
		uint64_t get_food() const;
		void update_food(int64_t delta);
		std::string get_name() const;

		void reveal_system(StarchartObject* system);
		std::vector<StarchartObject*> get_revealed_systems() const;
		void claim_system(StarchartObject* system);
		std::vector<StarchartObject*> get_claimed_systems() const;

		void add_fleet(Fleet* fleet);
		std::vector<Fleet*> get_fleets() const;

		void add_request(Request* request);
		Request* get_next_request(Entity* entity);

		std::string serialize() override;
	};
}
#endif // !__CIVILIZATION_H
