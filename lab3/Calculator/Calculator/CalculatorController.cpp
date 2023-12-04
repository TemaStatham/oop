#include "CalculatorController.h"

CalculatorController::CalculatorController(std::istream& input, std::ostream& output, Calculator& calc)
	: m_in(input)
	, m_out(output)
	, m_calc(calc)
{
}

void CalculatorController::GetStartCalculator()
{
	while (true)
	{
		std::string command;
		if (!(m_in >> command))
		{
			m_out << "ERROR start" << std::endl;
			return;
		}
		ExpressParsing expParsing(command, m_in, m_out); // sozdat 1 raz
		if (!expParsing.ParseExpression())
		{
			m_out << "ERROR parse" << std::endl;
			continue;
		}
		ExpressParsing::Expression exp = expParsing.GetExpression();
		RunCommand(exp);
	}
}

void CalculatorController::RunCommand(const ExpressParsing::Expression& exp)
{
	switch (exp.command)
	{
	case ExpressParsing::Command::VAR:
		CreateVar(exp.argName);
		break;
	case ExpressParsing::Command::LET:
		LetVarValue(exp.argName, exp.firstArg); //
		break;
	case ExpressParsing::Command::FN:
		CreateFunc(exp);
		break;
	case ExpressParsing::Command::PRINT:
		Print(exp.argName);
		break;
	case ExpressParsing::Command::PRINTFNS:
		PrintFuncs();
		break;
	case ExpressParsing::Command::PRINTVARS:
		PrintVars();
		break;
	case ExpressParsing::Command::ERROR_COMMAND:
		break;
	default:
		break;
	}
}

void CalculatorController::CreateVar(const std::string& varName)
{
	if (!m_calc.CreateVariable(varName))
	{
		m_out << "ERROR_COMMAND create variable" << std::endl;
	}
}

void CalculatorController::LetVarValue(const std::string& varName, const std::string& val)
{
	if (!m_calc.SetVariableToValue(varName, val))
	{
		m_out << "ERROR_COMMAND set variable" << std::endl;
	}
}

void CalculatorController::CreateFunc(const ExpressParsing::Expression& exp)
{
	if (!m_calc.CreateFunction(exp.argName, { exp.firstArg, exp.secondArg, exp.operation }))
	{
		m_out << "ERROR_COMMAND create function" << std::endl;
	}
}

void CalculatorController::Print(const std::string& varName)
{
	double value = m_calc.GetValueOfVariable(varName);
	if (!std::isnan(value))
	{
		m_out << value << std::endl;
		return;
	}
	Calculator::Func func = m_calc.GetFuncOfFuncName(varName);
	if (m_calc.FuncIsNullable(func))
	{
		return;
	}
	m_out << m_calc.CalculateResultOfFunction(func) << std::endl;
}

void CalculatorController::PrintVars()
{
	auto vars = m_calc.GetVariables();
	for (auto var : vars)
	{
		m_out << var.first << ':' << var.second << std::endl;
	}
}

void CalculatorController::PrintFuncs()
{
	auto funcs = m_calc.GetFuncs();
	for (const auto& func : funcs)
	{
		m_out << func.first << ':' << m_calc.CalculateResultOfFunction(func.second) << std::endl;
	}
}

std::string CalculatorController::TransformOperationToString(Operations::Operation operation)
{
	switch (operation)
	{
	case Operations::Operation::ADDITION:
		return "+";
	case Operations::Operation::SUBSTRACTION:
		return "-";
	case Operations::Operation::DIVISION:
		return "/";
	case Operations::Operation::MULTIPLICATION:
		return "*";
	case Operations::Operation::NOTHING:
		return "Nothing";
	default:
		return "ERROR_COMMAND transform operation to string";
	}
	return std::string();
}
