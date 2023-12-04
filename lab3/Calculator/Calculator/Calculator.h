#pragma once
#include "stdafx.h"
#include "Operations.h"

class Calculator
{
public:
	struct Func;

	using VarName = std::string;
	using Value = double;
	using Variables = std::map<VarName, Value>;
	using Funcs = std::map<VarName, Func>;

	struct Func
	{
		VarName firstVar;
		VarName secondVar;
		Operations::Operation operation;
	};

	const Func NULLABLE_FUNC = { "NULLABLE\n", "NULLABLE\n", Operations::Operation::NOTHING };

	bool CreateVariable(const VarName& variable);
	bool CreateFunction(const VarName& funcName, const Func& func);
	bool SetVariableToValue(const VarName& variable, const VarName& val); // translate normalno sdelat

	Value CalculateResultOfFunction(const Func& func) const;

	Variables GetVariables() const;
	Funcs GetFuncs() const;
	Value GetValueOfVariable(const VarName& var) const;
	Func GetFuncOfFuncName(const VarName& funcName) const; // get func by name

	bool FuncIsNullable(const Func& func) const; // is func null

private:
	bool IsExistVarInVars(const VarName& variable) const; // is var exist
	bool IsExistFuncInFuncs(const VarName& variable) const; // is func exist
	bool IsValidVariableName(const VarName& variable) const;
	bool IsDouble(const VarName& var) const;

	Value GetValueInFunc(const VarName& funcName) const;

	Variables m_vars;
	Funcs m_funcs;
};