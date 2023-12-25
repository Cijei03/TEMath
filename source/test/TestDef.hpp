#pragma once
#include <vector>
#include <string>

using TestPtr = bool(*)();

struct TestData
{
	TestPtr ptr;
	std::string TestName;
};

class TestBase
{
public:
	std::vector<TestData> LocalTests;

	std::string Title;

	TestBase(const std::string& Title);
};