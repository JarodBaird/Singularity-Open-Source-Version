#include <cmath>

#include "PlanetFactory.h"
#include "../../../Settings/TagConstants.h"
#include "../../../Terrain/MapTypes/MediumTerrainMap.h"
#include "../../../Terrain/TerrainFeatures/Natural/Forest.h"
#include "../../../Life/SpeciesFactory.h"

#include "Singularity.Data/Physics/Chemistry/Gigamole.h"

namespace Singularity
{
	PlanetFactory::PlanetFactory(const std::vector<Element*>& elements, const std::vector<Compound*>& compounds)
	{
		m_random = Altair::Random();

		for (Element* element : elements)
		{
			if (element->has_tag(TagConstants::forms_oceans)) { m_ocean_candidates.push_back(element); }

			if (element->has_tag(TagConstants::forms_atmospheres)) { m_atmosphere_candidates.push_back(element); }
		}

		for (Compound* compound : compounds)
		{
			if (compound->has_tag(TagConstants::forms_oceans)) { m_ocean_candidates.push_back(compound); }

			if (compound->has_tag(TagConstants::forms_atmospheres)) { m_atmosphere_candidates.push_back(compound); }
		}
	}

	Gigamoles PlanetFactory::generate_crust_amount(int atomic_number) const
	{
		const double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
		return Gigamoles{static_cast<uint64_t>((1 + r) * pow(10, 6) * pow(M_E, -0.116 * atomic_number))};
	}

	Gigamoles PlanetFactory::generate_atmosphere_amount() { return Gigamoles{static_cast<uint64_t>(rand()) % 500000}; }

	Gigamoles PlanetFactory::generate_ocean_amount() { return Gigamoles{static_cast<uint64_t>(rand()) % 5000}; }

	class HillData
	{
	private:
		uint32_t m_x, m_y;
		uint8_t m_height, m_slope;
	public:
		HillData()
		{
			m_x = 0;
			m_y = 0;
			m_height = 0;
			m_slope = 0;
		}

		HillData(int x, int y, uint8_t height, uint8_t slope)
		{
			m_x = x;
			m_y = y;
			m_height = height;
			m_slope = slope;
		}

		uint8_t get_height_at_point(uint32_t x, uint32_t y, uint32_t planet_width) const
		{
			uint32_t delta_x = x - m_x;
			if (delta_x >= planet_width / 2) { delta_x = x - m_x - planet_width; }
			else if (delta_x <= 0 - planet_width / 2) { delta_x = x - m_x + planet_width; }

			const uint32_t delta_y = y - m_y;
			const double distance = sqrt(delta_x * delta_x + delta_y * delta_y);

			const uint8_t delta = static_cast<uint8_t>(m_slope * distance);
			if (delta > m_height) { return 0; }

			return m_height - delta;
		}
	};

	GasPlanet* PlanetFactory::create_gas(std::string name) const
	{
		const int semimajor_axis = rand() % 50 + 1;

		return new GasPlanet(std::move(name), {semimajor_axis, 0, 0, 0});
	}

	Planet* PlanetFactory::create_terrestrial(std::string name)
	{
		std::unique_ptr<MediumTerrainMap> terrain = std::make_unique<MediumTerrainMap>();

		std::vector<HillData> hill_data;

		const int number_of_hills = rand() % 1000;
		hill_data.reserve(number_of_hills);

		const uint32_t map_width = terrain->get_map_width();
		const uint32_t map_height = terrain->get_map_height();

		for (int i = 1; i <= number_of_hills; i++)
		{
			uint32_t hill_x = static_cast<uint32_t>(rand()) % map_width;
			uint32_t hill_y = static_cast<uint32_t>(rand()) % map_height;
			uint8_t height = rand() % 10;
			uint8_t slope = rand() % 5;

			hill_data.emplace_back(hill_x, hill_y, height, slope);
		}

		for (uint32_t i = 0; i < map_height; i++)
		{
			for (uint32_t j = 0; j < map_width; j++)
			{
				uint8_t height = 0;

				for (HillData& h : hill_data) { height += h.get_height_at_point(j, i, map_width); }

				terrain->set_terrain_height(j, i, height);
				terrain->set_ocean_depth(j, i, 0);
			}
		}

		const int32_t semimajor_axis = rand() % 50 + 1;

		Planet* planet = new Planet(std::move(name), {semimajor_axis, 0, 0, 0}, std::move(terrain));

		Gigamoles total_atmosphere = Gigamoles{0};

		if (m_random.next_bool())
		{
			for (Chemical* chemical : m_atmosphere_candidates)
			{
				if (m_random.next_bool())
				{
					const Gigamoles partial_amount = generate_atmosphere_amount();
					total_atmosphere.value += partial_amount.value;
					planet->add_to_atmosphere(chemical, partial_amount);
				}
			}
		}

		const Altair::Color possible_colors[15] = {
			Altair::Color::silver,
			Altair::Color::red,
			Altair::Color::maroon,
			Altair::Color::orange,
			Altair::Color::yellow,
			Altair::Color::olive,
			Altair::Color::lime,
			Altair::Color::green,
			Altair::Color::aqua,
			Altair::Color::teal,
			Altair::Color::blue,
			Altair::Color::blue,
			Altair::Color::blue,
			Altair::Color::purple,
			Altair::Color::silver
		};
		const Altair::Color color = possible_colors[m_random.next_int(15)];

		Gigamoles total_ocean = Gigamoles{0};
		if (m_random.next_bool())
		{
			if (total_atmosphere.value > 10000 && !m_ocean_candidates.empty())
			{
				planet->set_ocean_type(m_ocean_candidates.at(rand() % m_ocean_candidates.size()));
				Gigamoles ocean_depth = generate_ocean_amount();
				total_ocean = ocean_depth;
				while (ocean_depth.value > 0)
				{
					const int x = rand() % planet->get_map_width();
					const int y = rand() % planet->get_map_height();

					planet->add_ocean(x, y);

					ocean_depth.value--;
				}
				planet->erode();
			}
		}

		// Generate aliens.
		if (total_ocean.value > 500)
		{
			// First generate the plants.
			if (m_random.next_bool())
			{
				Species* plant_species = SpeciesFactory::create(Species::Type::Plant, planet->get_ocean_type());

				int number_of_trees = 0;

				for (int x = 0; x < planet->get_map_width(); x++)
				{
					for (int y = 0; y < planet->get_map_height(); y++)
					{
						if (planet->get_terrain_at(x, y).get_is_land())
						{
							planet->set_structure(x, y, std::make_shared<Forest>(planet, plant_species));
							number_of_trees++;
						}
					}
				}

				if (number_of_trees > 0) { planet->set_is_starting_candidate(true); }
			}
		}

		return planet;
	}
}
