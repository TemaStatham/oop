#include <fstream>
#include <iostream>
#include <optional>
#include <string>

const int numberOfParams = 5;

struct MainArguments
{
	MainArguments(){};

	MainArguments(std::string _inputFile, std::string _outputFile,
		std::string _searchString, std::string _replacementString)
		: inputFile(_inputFile)
		, outputFile(_outputFile)
		, searchString(_searchString)
		, replacementString(_replacementString){};

	std::string inputFile;
	std::string outputFile;
	std::string searchString;
	std::string replacementString;
};

std::optional<MainArguments> InitMainArguments(int& argc, char* argv[])
{
	if (argc != numberOfParams)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return std::nullopt;
	}

	MainArguments arguments(argv[1], argv[2], argv[3], argv[4]);

	return arguments;
}

bool CheckFileToOpen(std::ifstream& inputFile, std::ofstream& outputFile,
	const std::optional<MainArguments>& arguments)
{
	if (!inputFile.is_open())
	{
		std::cout << "Unable to open input file " << arguments->inputFile << "\n";
		return false;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Unable to open output file " << arguments->outputFile << "\n";
		return false;
	}

	return true;
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;

	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);

		if (foundPos == std::string::npos)
		{
			break;
		}

		result.append(replacementString);
		pos = foundPos + searchString.length();
	}

	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int main(int argc, char* argv[])
{
	const auto arguments = InitMainArguments(argc, argv);

	if (!arguments.has_value())
	{
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(arguments->inputFile);

	std::ofstream outputFile;
	outputFile.open(arguments->outputFile);

	if (!CheckFileToOpen(inputFile, outputFile, arguments))
	{
		return 0;
	}

	CopyStreamWithReplacement(inputFile, outputFile, arguments->searchString, arguments->replacementString);

	inputFile.close();
	outputFile.close();

	return 0;
}
