#include <iostream>

#include "Tests.hpp"
#include "OutputColor.hpp"

void TestFeature(const TestData& test)
{
	auto result = test.ptr();
	std::cout << testEntry << test.TestName << ": ";
	if (!result)
		std::cout << testFailed << "FAILED" << std::endl;
	else
		std::cout << testSucceed << "OK" << std::endl;

	std::cout << testEntry;
}

void RenderTestTitle(const std::string& Title)
{
	std::cout << testTitle << "\n" << "TESTING " << Title << std::endl;
}

void ExecuteTests(TestBase* Tests)
{
	RenderTestTitle(Tests->Title);
	for (const auto& Test : Tests->LocalTests)
	{
		TestFeature(Test);
	}
}

int main()
{
	std::cout << testEntry << "Starting TEMath unit tests.." << std::endl;
	
	ExecuteTests(static_cast<TestBase*>(std::make_unique<Vec2Test>().get()));
	ExecuteTests(static_cast<TestBase*>(std::make_unique<Vec3Test>().get()));
	ExecuteTests(static_cast<TestBase*>(std::make_unique<Vec4Test>().get()));
	ExecuteTests(static_cast<TestBase*>(std::make_unique<Mat2Test>().get()));
	ExecuteTests(static_cast<TestBase*>(std::make_unique<Mat3Test>().get()));
	ExecuteTests(static_cast<TestBase*>(std::make_unique<Mat4Test>().get()));

	return 0;
}