#include "CppUnitTest.h"

#include "../../Singularity.Data/Physics/Calendar/Calendar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Singularity;

namespace SingularityDataTests
{
	TEST_CLASS(CalendarTests)
	{
	public:

		TEST_METHOD(DefaultStarDate)
		{
			const std::unique_ptr<Calendar> c = std::make_unique<Calendar>();
			Assert::AreEqual<std::string>("0.0.0", c->get_star_date());
		}

		TEST_METHOD(DefaultSettings)
		{
			std::unique_ptr<Calendar> c = std::make_unique<Calendar>();
			for (int i = 0; i < 128; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.0.1", c->get_star_date());

			for (int i = 0; i < 128 * 29; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.1.0", c->get_star_date());

			for (int i = 0; i < 128 * 30 * 11; i++) { c->tick(); }
			Assert::AreEqual<std::string>("1.0.0", c->get_star_date());
		}

		TEST_METHOD(IncrementDay)
		{
			std::unique_ptr<Calendar> c = std::make_unique<Calendar>(CalendarSettings{30, 10, 10});
			for (int i = 0; i < 29; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.0.0", c->get_star_date());
			c->tick();
			Assert::AreEqual<std::string>("0.0.1", c->get_star_date());
		}

		TEST_METHOD(IncrementMonth)
		{
			std::unique_ptr<Calendar> c = std::make_unique<Calendar>(CalendarSettings{1, 30, 10});
			for (int i = 0; i < 29; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.0.29", c->get_star_date());
			c->tick();
			Assert::AreEqual<std::string>("0.1.0", c->get_star_date());
		}

		TEST_METHOD(IncrementYear)
		{
			std::unique_ptr<Calendar> c = std::make_unique<Calendar>(CalendarSettings{1, 1, 12});
			for (int i = 0; i < 11; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.11.0", c->get_star_date());
			c->tick();
			Assert::AreEqual<std::string>("1.0.0", c->get_star_date());
		}

		TEST_METHOD(StandardYear)
		{
			std::unique_ptr<Calendar> c = std::make_unique<Calendar>();
			for (int i = 0; i < 128 * 30 * 12 - 1; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.11.29", c->get_star_date());
			c->tick();
			Assert::AreEqual<std::string>("1.0.0", c->get_star_date());
		}

		TEST_METHOD(ZeroTickDays)
		{
			std::unique_ptr<Calendar> c = std::make_unique<Calendar>(CalendarSettings{0, 0, 12});
			for (int i = 0; i < 11; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.11.0", c->get_star_date());
			c->tick();
			Assert::AreEqual<std::string>("1.0.0", c->get_star_date());
		}

		TEST_METHOD(LongDays)
		{
			std::unique_ptr<Calendar> c = std::make_unique<Calendar>(CalendarSettings{1000, 10, 10});
			for (int i = 0; i < 999; i++) { c->tick(); }
			Assert::AreEqual<std::string>("0.0.0", c->get_star_date());
			c->tick();
			Assert::AreEqual<std::string>("0.0.1", c->get_star_date());
		}
	};
}
