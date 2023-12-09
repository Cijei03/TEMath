#pragma once
#include <vector>
#include <string>

#include "TestDef.hpp"

class Mat3Test : public TestBase
{
public:
	static bool Multiplication();
	static bool Addition();
	static bool VectorMultiplication();
	static bool MatrixDeterminant();
	static bool MatrixInverse();
	static bool MatrixTranspose();

	Mat3Test() : TestBase("MATRIX 3")
	{
		this->LocalTests.push_back(TestData{ Multiplication, "Matrix-matrix multiplication" });
		this->LocalTests.push_back(TestData{ Addition, "Matrix-matrix addition" });
		this->LocalTests.push_back(TestData{ VectorMultiplication, "Matrix-vector multiplication" });
		this->LocalTests.push_back(TestData{ MatrixDeterminant, "Matrix determinant" });
		this->LocalTests.push_back(TestData{ MatrixTranspose, "Matrix transpose" });
		this->LocalTests.push_back(TestData{ MatrixInverse, "Matrix inverse" });		
	};
};