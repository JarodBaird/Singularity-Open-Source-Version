#include "CppUnitTest.h"
#include <vector>
#include "../../Singularity.Data/Physics/Chemistry/Compound.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Singularity;

namespace SingularityDataTests
{
	std::vector<Element*> elements = {
		new Element(1, "H", "Hydrogen", 1.008),
		new Element(6, "C", "Carbon", 12.011),
		new Element(7, "N", "Nitrogen", 14.007),
		new Element(8, "O", "Oxygen", 15.999),
		new Element(16, "S", "Sulfur", 32.06)
	};

	TEST_CLASS(CompoundTests)
	{
	public:
		TEST_METHOD(GetComplexity1)
		{
			const std::unique_ptr<Compound> c = std::make_unique<Compound>(
				"Dihydrogen Monoxide", "Water", "H2O", elements);

			Assert::AreEqual(10U, c->get_complexity());
		}

		TEST_METHOD(GetComplexity2)
		{
			const std::unique_ptr<Compound> c = std::make_unique<Compound>("Carbon Dioxide", "CO2", elements);

			Assert::AreEqual(22U, c->get_complexity());
		}

		TEST_METHOD(GetComplexity3)
		{
			const std::unique_ptr<Compound> c = std::make_unique<Compound>("Carbon Monoxide", "CO", elements);

			Assert::AreEqual(14U, c->get_complexity());
		}

		TEST_METHOD(GetComplexity4)
		{
			const std::unique_ptr<Compound> c = std::make_unique<Compound>(
				"Adalimumab", "C6428H9912N1694O1987S46", elements);

			Assert::AreEqual(76970U, c->get_complexity());
		}
	};
}
