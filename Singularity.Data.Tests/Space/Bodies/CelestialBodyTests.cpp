#include "CppUnitTest.h"
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#elif
#include <unistd.h>
#endif

#include "../../../Singularity.Data/Terrain/MapTypes/LargeTerrainMap.h"
#include "../../../Singularity.Data/Space/Bodies/CelestialBody.h"
#include "../../../Singularity.Data/Physics/Chemistry/Compound.h"
#include "../../../Altair.Engine/Graphics/Color.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Singularity;

class MockCelestialBody final : public CelestialBody
{
public:
	MockCelestialBody()
	{
		m_terrain_map = std::make_unique<LargeTerrainMap>();
		m_land_color = Altair::Color::orange;
		m_ocean = std::vector<ChemicalComposition>();
		ChemicalComposition comp;
		comp.element = new Compound("Water", "H2O",
		                            std::vector<Element*>{
			                            new Element(1, "H", "Hydrogen", 1.0),
			                            new Element(8, "O", "Oxygen", 16.0)
		                            }
		);
		comp.amount = 100;
		m_ocean.push_back(comp);

		for (int x = 0; x < m_terrain_map->get_map_width(); x++)
		{
			for (int y = 0; y < m_terrain_map->get_map_height(); y++)
			{
				m_terrain_map->set_terrain_height(x, y, static_cast<int>(x + y));
				// Produces a wide range of terrain heights.
			}
		}
	}
};

class MockStructure final : public TerrainFeature
{
public:
	MockStructure(CelestialBody* parent_body) : TerrainFeature(parent_body) {}

	void update() override {}
};

namespace SingularityDataTests
{
	TEST_CLASS(CelestialBodyTests)
	{
		//TEST_METHOD(Serialize) {
		//	std::unique_ptr<Singularity::CelestialBody> c1 = std::make_unique<MockCelestialBody>();
		//	Altair::SettingsReader fileReader;
		//	fileReader.parse_to_settings(c1->serialize(), 0);
		//	std::unique_ptr<Singularity::CelestialBody> c2 = std::make_unique<Singularity::CelestialBody>(fileReader);
		//	for (int x = 0; x < 256; x++) {
		//		for (int y = 0; y < 128; y++) {
		//			std::cout << x;
		//			std::cout << y;
		//			int h1 = c1->get_terrain_at(x, y).get_height();
		//			int h2 = c2->get_terrain_at(x, y).get_height();
		//			Assert::AreEqual(h1, h2);
		//		}
		//	}
		//}

		//TEST_METHOD(SetTerrainFeature) {
		//	std::unique_ptr<Singularity::CelestialBody> c = std::make_unique<MockCelestialBody>();
		//	std::shared_ptr<MockStructure> structure = std::make_shared<MockStructure>(nullptr);
		//	c->set_structure(1, 1, structure);
		//	Assert::AreEqual<std::shared_ptr<TerrainFeature>>(structure, c->get_structure(1, 1));
		//}
	};
}
