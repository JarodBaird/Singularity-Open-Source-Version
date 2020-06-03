#include "CppUnitTest.h"
#include "../../Altair.Engine/Graphics/TextItem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Altair;

namespace AltairEngineTests
{
	TEST_CLASS(TextItemTests)
	{
	public:
		TEST_METHOD(GetX)
		{
			const std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", Color::white);

			Assert::AreEqual(15, t->get_x());
		}

		TEST_METHOD(GetY)
		{
			const std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", Color::white);

			Assert::AreEqual(12, t->get_y());
		}

		TEST_METHOD(GetEmptyText)
		{
			const std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "", Color::white);

			Assert::AreEqual<std::string>("", t->get_display_text());
		}

		TEST_METHOD(GetText)
		{
			const std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", Color::white);

			Assert::AreEqual<std::string>("Test Text", t->get_display_text());
		}

		TEST_METHOD(GetSingleColor)
		{
			std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", Color::yellow);

			Assert::AreEqual(Color::yellow.to_int(), t->get_color(-1).to_int());
			Assert::AreEqual(Color::yellow.to_int(), t->get_color(0).to_int());
			Assert::AreEqual(Color::yellow.to_int(), t->get_color(100).to_int());
		}

		TEST_METHOD(NoColors)
		{
			std::vector<ColorSplit> colors;
			std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", colors);

			Assert::AreEqual(Color::white.to_int(), t->get_color(-1).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(0).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(100).to_int());
		}

		TEST_METHOD(GetMultipleColors)
		{
			std::vector<ColorSplit> colors;
			colors.push_back(ColorSplit{0, Color::white});
			colors.push_back(ColorSplit{5, Color::yellow});

			std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", colors);

			Assert::AreEqual(Color::white.to_int(), t->get_color(-1).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(0).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(4).to_int());
			Assert::AreEqual(Color::yellow.to_int(), t->get_color(5).to_int());
			Assert::AreEqual(Color::yellow.to_int(), t->get_color(6).to_int());
			Assert::AreEqual(Color::yellow.to_int(), t->get_color(100).to_int());
		}

		TEST_METHOD(GetMultipleUnorderedColors)
		{
			std::vector<ColorSplit> colors;
			colors.push_back(ColorSplit{6, Color::white});
			colors.push_back(ColorSplit{3, Color::green});
			colors.push_back(ColorSplit{5, Color::yellow});
			colors.push_back(ColorSplit{0, Color::red});

			std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", colors);

			Assert::AreEqual(Color::white.to_int(), t->get_color(-1).to_int());
			Assert::AreEqual(Color::red.to_int(), t->get_color(0).to_int());
			Assert::AreEqual(Color::red.to_int(), t->get_color(2).to_int());
			Assert::AreEqual(Color::green.to_int(), t->get_color(3).to_int());
			Assert::AreEqual(Color::green.to_int(), t->get_color(4).to_int());
			Assert::AreEqual(Color::yellow.to_int(), t->get_color(5).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(6).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(7).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(100).to_int());
		}

		TEST_METHOD(NoFirstColor)
		{
			std::vector<ColorSplit> colors;
			colors.push_back(ColorSplit{3, Color::yellow});
			colors.push_back(ColorSplit{5, Color::green});

			std::unique_ptr<TextItem> t = std::make_unique<TextItem>(15, 12, "Test Text", colors);

			Assert::AreEqual(Color::white.to_int(), t->get_color(0).to_int());
			Assert::AreEqual(Color::white.to_int(), t->get_color(2).to_int());
			Assert::AreEqual(Color::yellow.to_int(), t->get_color(3).to_int());
		}
	};
}
