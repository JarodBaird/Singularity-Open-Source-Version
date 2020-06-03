#include "CppUnitTest.h"
#include "../../Singularity.Data/UserInterface/Camera/Camera.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Singularity;

namespace SingularityDataTests
{
	TEST_CLASS(CameraTests)
	{
	public:
		TEST_METHOD(DefaultX)
		{
			const std::unique_ptr<Camera> c = std::make_unique<Camera>();
			Assert::AreEqual(0, c->get_x());
		}

		TEST_METHOD(DefaultY)
		{
			const std::unique_ptr<Camera> c = std::make_unique<Camera>();
			Assert::AreEqual(0, c->get_y());
		}

		TEST_METHOD(SetPositiveX)
		{
			std::unique_ptr<Camera> c = std::make_unique<Camera>();
			c->set_x(5);
			Assert::AreEqual(5, c->get_x());
		}

		TEST_METHOD(SetPositiveY)
		{
			std::unique_ptr<Camera> c = std::make_unique<Camera>();
			c->set_y(5);
			Assert::AreEqual(5, c->get_y());
		}

		TEST_METHOD(SetNegativeX)
		{
			std::unique_ptr<Camera> c = std::make_unique<Camera>();
			c->set_x(-5);
			Assert::AreEqual(-5, c->get_x());
		}

		TEST_METHOD(SetNegativeY)
		{
			std::unique_ptr<Camera> c = std::make_unique<Camera>();
			c->set_y(-5);
			Assert::AreEqual(-5, c->get_y());
		}
	};
}
