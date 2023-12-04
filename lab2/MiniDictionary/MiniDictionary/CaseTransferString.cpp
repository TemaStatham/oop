#include "CaseTransferString.h"

void TransformStringToLowerCase(std::string& str)
{
	//std::trasnsform(str.cbegin(), str.cend(), str.begin(), [](unsigned char ch) { return std::tolower(static_cast<unsigned char>(ch)); });
	for (char& ch : str)
	{
		ch = std::tolower(ch);//neopredelennoe povedenie
	}
}
