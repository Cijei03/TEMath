#pragma once
#include <iostream>

export module Test;

export using TestPtr = bool(*)();

export struct Test
{
	TestPtr ptr;
	std::string TestName;
};