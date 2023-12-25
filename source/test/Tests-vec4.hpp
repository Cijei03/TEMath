#pragma once
#include <vector>
#include <string>

#include "TestDef.hpp"

class Vec4Test : public TestBase
{
public:
	static bool Multiplication();
	static bool Addition();
	static bool Condition();

	Vec4Test() : TestBase("VECTOR 4")
	{
		this->LocalTests.push_back(TestData{ Multiplication, "Vector-vector multiplication" });
		this->LocalTests.push_back(TestData{ Addition, "Vector-vector addition" });
		this->LocalTests.push_back(TestData{ Condition, "Vector-vector condition" });
	}
};