#include "CppUnitTest.h"

#include "../../Singularity.Data/Physics/Chemistry/Element.h"
#include "../../Altair.Engine/FileSystem/FileReaders/SettingsReader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Singularity;

namespace SingularityDataTests
{
	TEST_CLASS(ElementTests)
	{
	public:
		TEST_METHOD(Deserialize)
		{
			Altair::SettingsReader reader("Element.dat", "");
			const std::unique_ptr<Element> element = std::make_unique<Element>(reader);
			Assert::AreEqual(1ui16, element->get_atomic_number());
			Assert::AreEqual<std::string>("H", element->get_atomic_symbol());
			Assert::AreEqual<std::string>("Hydrogen", element->get_name());
		}
	};
}
