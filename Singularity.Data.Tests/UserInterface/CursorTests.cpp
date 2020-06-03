#include "CppUnitTest.h"
#include "../../Singularity.Data/UserInterface/Cursor/Cursor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Singularity;

namespace SingularityDataTests
{
	TEST_CLASS(CursorTests)
	{
	public:
		TEST_METHOD(OriginConstructor)
		{
			const std::unique_ptr<Cursor> c = std::make_unique<Cursor>(0, 0);
			Assert::AreEqual(0, c->get_x());
			Assert::AreEqual(0, c->get_y());
		}

		TEST_METHOD(NonOriginConstructor)
		{
			const std::unique_ptr<Cursor> c = std::make_unique<Cursor>(10, 35);
			Assert::AreEqual(10, c->get_x());
			Assert::AreEqual(35, c->get_y());
		}

		TEST_METHOD(SetX)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(0, 0);
			c->set_x(5);
			Assert::AreEqual(5, c->get_x());
		}

		TEST_METHOD(SetY)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(0, 0);
			c->set_y(7);
			Assert::AreEqual(7, c->get_y());
		}

		TEST_METHOD(MoveUpPositive)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_up(2);
			Assert::AreEqual(-1, c->get_y());
			Assert::AreEqual(1, c->get_x());
		}

		TEST_METHOD(MoveUpNegative)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_up(-2);
			Assert::AreEqual(3, c->get_y());
			Assert::AreEqual(1, c->get_x());
		}

		TEST_METHOD(MoveDownPositive)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_down(2);
			Assert::AreEqual(3, c->get_y());
			Assert::AreEqual(1, c->get_x());
		}

		TEST_METHOD(MoveDownNegative)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_down(-2);
			Assert::AreEqual(-1, c->get_y());
			Assert::AreEqual(1, c->get_x());
		}

		TEST_METHOD(MoveLeftPositive)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_left(2);
			Assert::AreEqual(1, c->get_y());
			Assert::AreEqual(-1, c->get_x());
		}

		TEST_METHOD(MoveLeftNegative)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_left(-2);
			Assert::AreEqual(1, c->get_y());
			Assert::AreEqual(3, c->get_x());
		}

		TEST_METHOD(MoveRightPositive)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_right(2);
			Assert::AreEqual(1, c->get_y());
			Assert::AreEqual(3, c->get_x());
		}

		TEST_METHOD(MoveRightNegative)
		{
			std::unique_ptr<Cursor> c = std::make_unique<Cursor>(1, 1);
			c->move_right(-2);
			Assert::AreEqual(1, c->get_y());
			Assert::AreEqual(-1, c->get_x());
		}
	};
}
