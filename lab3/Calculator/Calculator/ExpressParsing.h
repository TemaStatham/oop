#pragma once
#include "stdafx.h"
#include "Calculator.h"
// expression sdelat
class ExpressParsing
{
public:
	ExpressParsing(const std::string& command, std::istream& in, std::ostream& output);

	enum class Command
	{
		VAR,
		LET,
		FN,
		PRINT,
		PRINTVARS,
		ERROR_COMMAND,
		PRINTFNS,
	};

	struct Expression
	{
		Command command;
		std::string argName; // identifyname
		std::string firstArg;
		std::string secondArg;
		Operations::Operation operation;
	};

	bool ParseExpression();
	Expression GetExpression();

private:
	const std::string& m_command;
	std::istream& m_in;
	std::ostream& m_out;
	Expression m_expression = { Command::ERROR_COMMAND };

	Command GetCommand(const std::string& command);

	bool ParseVar();
	bool ParseLet();
	bool ParseFN();
	bool ParsePrint();
	bool ParsePrintVars();
	bool ParsePrintFNS();

	Operations::Operation ParseOperation(const std::string& operation);
};