#include "CppUnitTest.h"
#include "../../Altair.Engine/FileSystem/FileReaders/SettingsReader.h"

#include <direct.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Altair;

namespace AltairEngineTests
{
	TEST_CLASS(SettingsReaderTests)
	{
	public:
		const std::string directory = "";

		TEST_METHOD(InvalidFile)
		{
			const std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>("DoesNotExist");
			Assert::AreEqual(file_reader->get_final_position(), 0U);
		}

		TEST_METHOD(EmptyFile)
		{
			const std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("Empty.cfg", directory);
			Assert::AreEqual(file_reader->get_final_position(), 0U);
		}

		TEST_METHOD(EmptyKey)
		{
			const std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>(
				"EmptyKeys.cfg", directory);
			Assert::AreEqual(file_reader->get_final_position(), 0U);
		}

		TEST_METHOD(ReadString)
		{
			const std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>(
				"Normal.cfg", directory);
			Assert::AreEqual<std::string>(file_reader->get("String"), "ARandomString");
		}

		TEST_METHOD(ReadEmptyString)
		{
			const std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>(
				"EmptyValues.cfg", directory);
			Assert::AreEqual<std::string>(file_reader->get("String"), "");
		}

		TEST_METHOD(ReadInt)
		{
			const std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>(
				"Normal.cfg", directory);
			Assert::AreEqual(file_reader->get_int("Int"), 42);
		}

		TEST_METHOD(ReadEmptyInt)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("EmptyValues.cfg", directory);
			Assert::AreEqual(file_reader->get_int("Int"), 0);
		}

		TEST_METHOD(ReadLargeInt)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("OutOfBounds.cfg", directory);
			Assert::AreEqual(file_reader->get_int("Int"), INT_MAX);
		}

		TEST_METHOD(ReadLong)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>("Normal.cfg", directory);
			Assert::AreEqual<int64_t>(file_reader->get_long("Long"), 3141592653);
		}

		TEST_METHOD(ReadEmptyLong)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("EmptyValues.cfg", directory);
			Assert::AreEqual<int64_t>(file_reader->get_long("Long"), 0);
		}

		TEST_METHOD(ReadLargeLong)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("OutOfBounds.cfg", directory);
			Assert::AreEqual<int64_t>(file_reader->get_long("Long"), LLONG_MAX);
		}

		TEST_METHOD(ReadDouble)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>("Normal.cfg", directory);
			Assert::AreEqual(file_reader->get_double("Double"), 3.14159);
		}

		TEST_METHOD(ReadEmptyDouble)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("EmptyValues.cfg", directory);
			Assert::AreEqual<double>(file_reader->get_double("Double"), 0);
		}

		TEST_METHOD(ReadLargeDouble)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("OutOfBounds.cfg", directory);
			Assert::AreEqual(file_reader->get_double("Double"), DBL_MAX);
		}

		TEST_METHOD(ReadWithoutDefault)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>(
				"WithDefault.cfg", directory, false);
			Assert::AreEqual<std::string>(file_reader->get("Val1"), "Changed");
			Assert::AreEqual<std::string>(file_reader->get("Val2"), "");
			Assert::AreEqual<std::string>(file_reader->get("Val3"), "New");
		}

		TEST_METHOD(DifferentFileExt)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader
			>("DiffFileExt.txt", directory);
			Assert::AreEqual<std::string>(file_reader->get("String"), "ARandomString3");
		}

		TEST_METHOD(NoFileExt)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>("NoFileExt", directory);
			Assert::AreEqual<std::string>(file_reader->get("String"), "ARandomString2");
		}

		TEST_METHOD(WithWhitespace)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>(
				"Whitespace.cfg", directory, false);
			Assert::AreEqual<std::string>(file_reader->get("Setting1"), "S1");
			Assert::AreEqual<std::string>(file_reader->get("Setting2"), "S2");
			Assert::AreEqual<std::string>(file_reader->get("Setting3"), "S3");
			Assert::AreEqual<std::string>(file_reader->get("Setting4"), "S4");
		}

		TEST_METHOD(Nested)
		{
			std::unique_ptr<SettingsReader> file_reader = std::make_unique<SettingsReader>(
				"Nested.cfg", directory, false);
			Assert::AreEqual<std::string>(file_reader->get("Setting1"), "S1");
			Assert::AreEqual<std::string>(file_reader->get("Setting6"), "S6");

			SettingsReader f2 = file_reader->get_sub_settings().at(0);
			Assert::AreEqual<std::string>(f2.get("Setting2"), "S2");
			Assert::AreEqual<std::string>(f2.get("Setting3"), "S3");
			Assert::AreEqual<std::string>(f2.get("Setting5"), "S5");

			SettingsReader f3 = f2.get_sub_settings().at(0);
			Assert::AreEqual<std::string>(f3.get("Setting4"), "S4");
		}
	};
}
