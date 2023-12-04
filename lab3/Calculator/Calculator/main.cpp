#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorController.h"

int main()
{
	Calculator calc;
	CalculatorController calcController(std::cin, std::cout, calc);
	calcController.GetStartCalculator();
}
