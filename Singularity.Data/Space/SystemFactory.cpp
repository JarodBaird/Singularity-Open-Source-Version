#include "SystemFactory.h"

#include <utility>


#include "Altair.Engine/Graphics/Color.h"
#include "Bodies/Stars/Star.h"
#include "Bodies/Planets/Planet.h"
#include "Bodies/MinorPlanets/Comet.h"
#include "Bodies/MinorPlanets/Asteroid.h"
#include "Bodies/Stars/EnclosedStar.h"
#include "Bodies/Stars/EventHorizon.h"

namespace Singularity
{
	SystemFactory::SystemFactory(std::vector<Element*> elements, std::vector<Compound*> compounds)
		: m_planet_factory(elements, compounds), elements(std::move(elements)), compounds(std::move(compounds))
	{
		m_elements = elements;
		m_compounds = compounds;
	}

	StarchartObject* SystemFactory::create(const std::string& name, int x, int y)
	{
		const int r = m_random.next_int(100);
		if (r == 99) { return this->create_blackhole(name, x, y); }
		if (r == 98) { return this->create_rogue_planet(name, x, y); }
		if (r == 97) { return this->create_dyson_sphere(name, x, y); }

		return this->create_star(name, x, y);
	}

	StarchartObject* SystemFactory::create_blackhole(std::string name, int x, int y) const
	{
		StarchartObject* system = new StarchartObject(x, y, std::move(name));
		system->add_parent(new EventHorizon());
		return system;
	}

	StarchartObject* SystemFactory::create_rogue_planet(const std::string& name, int x, int y)
	{
		StarchartObject* system = new StarchartObject(x, y, name);

		system->add_parent(m_planet_factory.create_terrestrial(name));
		return system;
	}

	StarchartObject* SystemFactory::create_dyson_sphere(std::string name, int x, int y) const
	{
		StarchartObject* system = new StarchartObject(x, y, std::move(name));
		system->add_parent(new EnclosedStar());
		return system;
	}

	StarchartObject* SystemFactory::create_star(const std::string& name, int x, int y)
	{
		const int r = m_random.next_int(100);
		Altair::Color c;
		if (r < 76) { c = Altair::Color::red; }
		else if (r < 88) { c = Altair::Color::orange; }
		else if (r < 96) { c = Altair::Color::yellow; }
		else if (r < 99) { c = Altair::Color::white; }
		else { c = Altair::Color::blue; }

		StarchartObject* system = new StarchartObject(x, y, name);

		// Generate planets.
		const int number_of_planets = m_random.next_int(12);
		for (int i = 0; i < number_of_planets; i++)
		{
			const std::string planet_name = name + " " + static_cast<char>('a' + i);

			if (m_random.next_bool()) { system->add_child(m_planet_factory.create_terrestrial(planet_name)); }
			else { system->add_child(m_planet_factory.create_gas(planet_name)); }
		}

		// Generate comets.
		const int number_of_comets = m_random.next_int(20);
		for (int i = 0; i < number_of_comets; i++) { system->add_child(new Comet()); }

		// Generate asteroids.
		const int number_of_asteroids = m_random.next_int(20);
		for (int i = 0; i < number_of_asteroids; i++) { system->add_child(new Asteroid()); }

		system->add_parent(new Star(c));

		return system;
	}
}
