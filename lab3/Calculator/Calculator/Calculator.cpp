#include "Calculator.h"

bool Calculator::CreateVariable(const VarName& variable)
{
	if (IsExistVarInVars(variable))
	{
		return false;
	}

	if (IsExistFuncInFuncs(variable))
	{
		return false;
	}

	if (!IsValidVariableName(variable))
	{
		return false;
	}

	m_vars.emplace(variable, NOT_A_NUMBER);
	return true;
}

bool Calculator::CreateFunction(const VarName& funcName, const Func& func)
{
	if (IsExistVarInVars(funcName))
	{
		return false;
	}

	if (IsExistFuncInFuncs(funcName))
	{
		return false;
	}

	if (!IsValidVariableName(funcName))
	{
		return false;
	}

	CreateVariable(func.firstVar);
	CreateVariable(func.secondVar);

	m_funcs.emplace(funcName, func);
	return true;
}

bool Calculator::SetVariableToValue(const VarName& variable, const VarName& val)
{
	CreateVariable(variable);

	if (!IsValidVariableName(variable))
	{
		return false;
	}

	if (IsDouble(val))
	{
		try
		{
			m_vars[variable] = std::stod(val);
			return true;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "ERROR_COMMAND: " << e.what() << std::endl;
			return false;
		}
	}

	return false;
}

Calculator::Value Calculator::CalculateResultOfFunction(const Func& func) const
{
	Operations op;

	Value FIRST_VALUE = GetValueOfVariable(func.firstVar);
	Value SECOND_VALUE = GetValueOfVariable(func.secondVar);

	if (std::isnan(FIRST_VALUE))
	{
		FIRST_VALUE = GetValueInFunc(func.firstVar);
	}

	if (std::isnan(SECOND_VALUE))
	{
		SECOND_VALUE = GetValueInFunc(func.secondVar);
	}

	if (std::isnan(FIRST_VALUE) || std::isnan(SECOND_VALUE))
	{
		return NOT_A_NUMBER;
	}

	return op.PerfomOperation(func.operation, FIRST_VALUE, SECOND_VALUE);
}

Calculator::Variables Calculator::GetVariables() const
{
	return m_vars;
}

Calculator::Funcs Calculator::GetFuncs() const
{
	return m_funcs;
}

Calculator::Value Calculator::GetValueOfVariable(const VarName& var) const
{
	if (IsDouble(var))
	{
		try
		{
			return std::stod(var);
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "ERROR_COMMAND: " << e.what() << std::endl;
			return NOT_A_NUMBER;
		}
	}

	auto it = m_vars.find(var);
	if (it == m_vars.end())
	{
		return NOT_A_NUMBER;
	}
	return it->second;
}

Calculator::Func Calculator::GetFuncOfFuncName(const VarName& funcName) const
{
	auto it = m_funcs.find(funcName);
	if (it != m_funcs.end())
	{
		return it->second;
	}
	return NULLABLE_FUNC;
}

bool Calculator::IsExistVarInVars(const VarName& variable) const
{
	auto it = m_vars.find(variable);
	if (it != m_vars.end())
	{
		return true;
	}
	return false;
}

bool Calculator::IsExistFuncInFuncs(const VarName& variable) const
{
	auto it = m_funcs.find(variable);
	if (it != m_funcs.end())
	{
		return true;
	}
	return false;
}

bool Calculator::IsValidVariableName(const VarName& variable) const
{
	const auto regexStr = R"(^[a-zA-Z_][a-zA-Z0-9_]*$)";
	const std::regex r(regexStr, std::regex::icase);
	return std::regex_match(variable, r);
}

bool Calculator::IsDouble(const VarName& var) const
{
	const std::string regexStr = R"(^[-+]?[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?$)";
	const std::regex regex(regexStr);
	return std::regex_match(var, regex);
}

Calculator::Value Calculator::GetValueInFunc(const VarName& funcName) const
{
	Func func = GetFuncOfFuncName(funcName);
	if (FuncIsNullable(func))
	{
		return NOT_A_NUMBER;
	}

	return CalculateResultOfFunction(func);
}

bool Calculator::FuncIsNullable(const Func& func) const
{
	return (func.firstVar == NULLABLE_FUNC.firstVar
		&& func.secondVar == NULLABLE_FUNC.secondVar
		&& func.operation == NULLABLE_FUNC.operation);
}
