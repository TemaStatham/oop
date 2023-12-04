#pragma once
#include "stdafx.h"
#include "Calculator.h"
#include "ExpressParsing.h"
#include "Operations.h"

class CalculatorController
{
public:
	CalculatorController(std::istream& input, std::ostream& output, Calculator& calc);
	void GetStartCalculator();

private:
	std::istream& m_in;
	std::ostream& m_out;
	Calculator& m_calc;

	void RunCommand(const ExpressParsing::Expression& exp);
	void CreateVar(const std::string& varName);
	void LetVarValue(const std::string& varName, const std::string& val);
	void CreateFunc(const ExpressParsing::Expression& exp);
	void Print(const std::string& varName);
	void PrintVars();
	void PrintFuncs();

	std::string TransformOperationToString(Operations::Operation operation);
};
