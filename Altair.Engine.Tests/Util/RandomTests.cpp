#include "CppUnitTest.h"
#include "../../Altair.Engine/Util/Random.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Altair;

namespace AltairEngineTests
{
	TEST_CLASS(RandomTests)
	{
	public:
		TEST_METHOD(GivenSeed)
		{
			std::unique_ptr<Random> random = std::make_unique<Random>(420);
			Assert::AreEqual(1355688881U, random->next_int());
		}

		TEST_METHOD(GivenStart)
		{
			std::unique_ptr<Random> expected_random = std::make_unique<Random>(69);
			std::unique_ptr<Random> random = std::make_unique<Random>(69, 100);
			for (int i = 0; i < 100; i++) { expected_random->next_int(); }

			Assert::AreEqual(expected_random->next_int(), random->next_int());
		}

		TEST_METHOD(LargeStart)
		{
			std::unique_ptr<Random> expected_random = std::make_unique<Random>(42069);
			std::unique_ptr<Random> random = std::make_unique<Random>(42069, 1000000);
			for (int i = 0; i < 1000000; i++) { expected_random->next_int(); }
			Assert::AreEqual(expected_random->next_int(), random->next_int());
		}
	};
}
