#pragma once
#include <vector>
#include <string>

#include "TestDef.hpp"

class Mat2Test : public TestBase
{
public:
	static bool Multiplication();
	static bool Addition();
	static bool VectorMultiplication();
	static bool MatrixTranspose();
	static bool MatrixDeterminant();
	static bool MatrixInverse();

	Mat2Test() : TestBase("MATRIX 2")
	{
		this->LocalTests.push_back(TestData{ Multiplication, "Matrix-matrix multiplication" });
		this->LocalTests.push_back(TestData{ Addition, "Matrix-matrix addition" });
		this->LocalTests.push_back(TestData{ VectorMultiplication, "Matrix-vector multiplication" });
		this->LocalTests.push_back(TestData{ MatrixTranspose, "Matrix-vector transpose" });
		this->LocalTests.push_back(TestData{ MatrixDeterminant, "Matrix determinant" });
		this->LocalTests.push_back(TestData{ MatrixInverse, "Matrix inverse" });
	};
};