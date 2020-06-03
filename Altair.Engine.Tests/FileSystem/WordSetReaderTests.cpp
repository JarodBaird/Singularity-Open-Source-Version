#include "CppUnitTest.h"
#include "../../Altair.Engine/FileSystem/FileReaders/WordSetReader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Altair;

namespace AltairEngineTests
{
	TEST_CLASS(WordSetReaderTests)
	{
	public:
		TEST_METHOD(EmptyFile)
		{
			const std::unique_ptr<WordSetReader> file_reader = std::make_unique<WordSetReader>("WordSet_Empty.txt");
			Assert::AreEqual<size_t>(0, file_reader->get_words().size());
		}

		TEST_METHOD(Read)
		{
			const std::unique_ptr<WordSetReader> file_reader = std::make_unique<WordSetReader>("WordSet_Normal.txt");
			Assert::AreEqual<size_t>(4, file_reader->get_words().size());
			Assert::AreEqual<std::string>("Test1", file_reader->get_words().at(0));
			Assert::AreEqual<std::string>("Test2", file_reader->get_words().at(1));
			Assert::AreEqual<std::string>("Test3", file_reader->get_words().at(2));
			Assert::AreEqual<std::string>("Test4", file_reader->get_words().at(3));
		}
	};
}
