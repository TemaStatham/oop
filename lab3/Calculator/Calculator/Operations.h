#pragma once
#include "stdafx.h"

class Operations
{
public:
	enum class Operation
	{
		ADDITION,
		SUBSTRACTION,
		DIVISION,
		MULTIPLICATION,
		NOTHING,
	};

	double PerfomOperation(Operation operation, double firstVal, double secValue);

private:
	double Addition(double firstVal, double secondVal);
	double Substraction(double firstVal, double secondVal);
	double Division(double firstVal, double secondVal);
	double Multiplication(double firstVal, double secondVal);
};