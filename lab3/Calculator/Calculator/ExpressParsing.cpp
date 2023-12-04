#include "ExpressParsing.h"
#include <string>

ExpressParsing::ExpressParsing(const std::string& command, std::istream& in, std::ostream& out)
	: m_command(command)
	, m_in(in)
	, m_out(out)
{
}

bool ExpressParsing::ParseExpression()
{
	m_expression.command = GetCommand(m_command);
	switch (m_expression.command)
	{
	case ExpressParsing::Command::VAR:
		return ParseVar();
	case ExpressParsing::Command::LET:
		return ParseLet();
	case ExpressParsing::Command::FN:
		return ParseFN();
	case ExpressParsing::Command::PRINT:
		return ParsePrint();
	case ExpressParsing::Command::PRINTVARS:
		return ParsePrintVars(); // delete
	case ExpressParsing::Command::PRINTFNS:
		return ParsePrintFNS(); // hold on
	default:
		break;
	}

	return false;
}

ExpressParsing::Command ExpressParsing::GetCommand(const std::string& command)
{
	const std::map<std::string, ExpressParsing::Command> commands{
		{ "var", ExpressParsing::Command::VAR },
		{ "let", ExpressParsing::Command::LET },
		{ "fn", ExpressParsing::Command::FN },
		{ "print", ExpressParsing::Command::PRINT },
		{ "printvars", ExpressParsing::Command::PRINTVARS },
		{ "printfns", ExpressParsing::Command::PRINTFNS }
	};
	if (commands.contains(command))
	{
		return commands.at(command);
	}
	return ExpressParsing::Command::ERROR_COMMAND;
}

bool ExpressParsing::ParseVar()
{
	if (!(m_in >> m_expression.argName))
	{
		m_out << "Variable name reading ERROR" << std::endl;
		return false;
	}
	return true;
}

bool ExpressParsing::ParseLet()
{
	std::string str;
	if (!(m_in >> str))
	{
		m_out << "Expression reading ERROR" << std::endl;
		return false;
	}

	std::regex re(R"(([a-zA-Z0-9]+)(=)([a-zA-Z0-9]+)$)", std::regex_constants::icase);
	std::smatch match;

	if (std::regex_search(str, match, re) || match.size() != 4)
	{
		m_expression.argName = match[1];
		m_expression.firstArg = match[3];

		return true;
	}

	return false;
}

bool ExpressParsing::ParseFN()
{
	std::string str;
	if (!(m_in >> str))
	{
		m_out << "Expression reading ERROR_COMMAND" << std::endl;
		return false;
	}
	std::regex reg(R"(^([a-zA-Z0-9_]+)(=)([a-zA-Z0-9_]+)([+\-*\/])([a-zA-Z0-9_]+)$)", std::regex_constants::icase);
	std::cmatch result;

	if (!std::regex_match(str.c_str(), result, reg) || result.size() != 6)
	{
		m_out << "No valid expression ERROR_COMMAND" << std::endl;
		return false;
	}
	m_expression.argName = result[1];
	m_expression.firstArg = result[3];
	m_expression.operation = ParseOperation(result[4].str());
	m_expression.secondArg = result[5];
	return true;
}

bool ExpressParsing::ParsePrint()
{
	if (!(m_in >> m_expression.argName))
	{
		m_out << "Variable name reading ERROR_COMMAND" << std::endl;
		return false;
	}
	return true;
}

bool ExpressParsing::ParsePrintVars()
{
	return true;
}

bool ExpressParsing::ParsePrintFNS()
{
	return true;
}

Operations::Operation ExpressParsing::ParseOperation(const std::string& operation)
{
	const std::map<std::string, Operations::Operation> operations{
		{ "+", Operations::Operation::ADDITION },
		{ "-", Operations::Operation::SUBSTRACTION },
		{ "/", Operations::Operation::DIVISION },
		{ "*", Operations::Operation::MULTIPLICATION }
	};
	if (operations.contains(operation))
	{
		return operations.at(operation);
	}
	return Operations::Operation::NOTHING;
}
ExpressParsing::Expression ExpressParsing::GetExpression()
{
	return m_expression;
}
