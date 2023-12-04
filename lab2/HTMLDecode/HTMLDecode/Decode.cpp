#include "Decode.h"

const std::string startEntities = "&";

struct Entities
{
	std::string encode;
	std::string decode;
};

std::string DecodeEntities(const std::string& html, size_t& pos)
{
	const std::vector<Entities> entities{ {"\"", "&quot;"},
		{"'", "&apos;"}, {"<", "&lt;"}, {">", "&gt;"}, {"&", "&amp;"} };

	//todo : зачем нужен порядок
	for (size_t countEntites = 0; countEntites < entities.size(); countEntites++)
	{
		if (html.size() >= pos + entities[countEntites].decode.size())
		{
			//Todo: избавиться от извлечения подстроки (есть в строке метод compare)
			std::string trimmed = html.substr(pos, entities[countEntites].decode.size());

			if (trimmed == entities[countEntites].decode)
			{
				pos += entities[countEntites].decode.size();
				return entities[countEntites].encode;
			}
		}
	}

	pos++;

	return startEntities;
}

std::string HtmlDecode(std::string const& html)
{	
	size_t pos = 0;

	std::string result;

	while (pos < html.length())
	{
		size_t foundPos = html.find(startEntities, pos);
		result.append(html, pos, foundPos - pos);

		if (foundPos == std::string::npos)
		{
			break;
		}

		std::string replacementString = DecodeEntities(html, foundPos);

		result.append(replacementString);
		pos = foundPos;
	}

	return result;
}

void ProcessHtmlText(std::istream& in, std::ostream& out)
{
	std::string line;
	while (getline(in, line))
	{
		out << HtmlDecode(line) << "\n";
	}
}