#include "CppUnitTest.h"
#include "../../Altair.Engine/WordSets/WordBank.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Altair;

namespace AltairEngineTests
{
	TEST_CLASS(WorkBankTests)
	{
	public:
		TEST_METHOD(GenerateEmptyString)
		{
			std::unique_ptr<WordBank> w = std::make_unique<WordBank>();
			const std::string word = w->generate_string("");
			Assert::AreEqual<std::string>("", word);
		}

		TEST_METHOD(GenerateRawString)
		{
			std::unique_ptr<WordBank> w = std::make_unique<WordBank>();
			const std::string word = w->generate_string("Raw string with only characters");
			Assert::AreEqual<std::string>("Raw string with only characters", word);
		}

		TEST_METHOD(GenerateString)
		{
			std::unique_ptr<WordBank> w = std::make_unique<WordBank>();
			w->add_word_to_set("AmericanMaleName", "Jarod");
			w->add_word_to_set("AmericanLastName", "Baird");

			const std::string word = w->generate_string("{AmericanMaleName} {AmericanLastName}");

			Assert::AreEqual<std::string>("Jarod Baird", word);
		}

		TEST_METHOD(InvalidWordSet)
		{
			std::unique_ptr<WordBank> w = std::make_unique<WordBank>();

			const std::string word = w->generate_string("{AmericanState}");

			Assert::AreEqual<std::string>("", word);
		}

		TEST_METHOD(GenerateMalformedString)
		{
			std::unique_ptr<WordBank> w = std::make_unique<WordBank>();

			const std::string word = w->generate_string("{{{}{}}{{{}");

			Assert::AreEqual<std::string>("", word);
		}
	};
}
