#include "CppUnitTest.h"
#include "../../Altair.Engine/WordSets/WordSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Altair;

namespace AltairEngineTests
{
	TEST_CLASS(WorkSetTests)
	{
	public:
		TEST_METHOD(DefaultCount)
		{
			const std::unique_ptr<WordSet> w = std::make_unique<WordSet>();

			Assert::AreEqual<size_t>(0, w->get_count());
		}

		TEST_METHOD(GetCount)
		{
			std::unique_ptr<WordSet> w = std::make_unique<WordSet>();
			w->add_word("Bad Religion");

			Assert::AreEqual<size_t>(1, w->get_count());
		}

		TEST_METHOD(AddDuplicateWords)
		{
			std::unique_ptr<WordSet> w = std::make_unique<WordSet>();
			w->add_word("NOFX");
			w->add_word("NOFX");

			Assert::AreEqual<size_t>(2, w->get_count());
		}

		TEST_METHOD(GetWordFromEmptySet)
		{
			std::unique_ptr<WordSet> w = std::make_unique<WordSet>();

			Assert::AreEqual<std::string>("", w->get_random_word());
		}

		TEST_METHOD(GetRandomWord)
		{
			std::unique_ptr<WordSet> w = std::make_unique<WordSet>();
			w->add_word("AFI");

			Assert::AreEqual<std::string>("AFI", w->get_random_word());
		}

		TEST_METHOD(GetRandomWordRemoval)
		{
			std::unique_ptr<WordSet> w = std::make_unique<WordSet>();
			w->add_word("Jarod");
			w->add_word("Baird");
			w->get_random_word(true);

			Assert::AreEqual<size_t>(1, w->get_count());
		}
	};
}
