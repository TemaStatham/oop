#include "ExpandProcess.h"

bool CheckValidPos(const std::vector<PositionUntouched>& positionsUntouched, size_t newPos)
{
	for (auto pos : positionsUntouched)
	{
		if (pos.first > newPos && pos.second < newPos)
		{
			return false;
		}
	}
	return true;
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString,
	std::vector<PositionUntouched>& positionsUntouched)
{
	size_t pos = 0;

	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);

		if (!CheckValidPos(positionsUntouched, foundPos))
		{
			continue;
		}

		if (foundPos == std::string::npos)
		{
			break;
		}

		positionsUntouched.push_back({ pos, foundPos });

		result.append(replacementString);
		pos = foundPos + searchString.length();
	}

	return result;
}

std::string ExpandTemplate(std::string const& tpl,
	std::map<std::string, std::string> const& params)
{
	std::string result = tpl;

	std::vector<PositionUntouched> positionsUntouched;

	for (auto it = params.rbegin(); it != params.rend(); ++it)
	{
		result = ReplaceString(result, it->second, it->first, positionsUntouched);
	}

	return result;
}

bool ExpandProcess(Arguments& args)
{
	std::ifstream in(args.inputFileName);
	std::ofstream out(args.outputFileName);

	if (!in.is_open() || !out.is_open())
	{
		return false;
	}

	std::string tpl;

	while (getline(in, tpl))
	{
		out << ExpandTemplate(tpl, args.params) << '\n';
	}

	return true;
}