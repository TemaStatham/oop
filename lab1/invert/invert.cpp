#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

const int numberOfParams = 2, matrixSize = 3;

using Mat3x3 = std::array<std::array<double, matrixSize>, matrixSize>;

struct MainArguments
{
	MainArguments(){};

	MainArguments(std::string _matrixFile)
		: matrixFile(_matrixFile){};

	std::string matrixFile;
};

std::optional<MainArguments> InitMainArguments(int& argc, char* argv[])
{
	if (argc != numberOfParams)
	{
		std::cout << "Invalid argument count\n"
				  << "invert.exe <matrix file1>\n";
		return std::nullopt;
	}

	MainArguments arguments(argv[1]);

	return arguments;
}

std::optional<Mat3x3> ReadMatrixFromFile(std::ifstream& inputFile)
{
	Mat3x3 matrix;

	for (size_t i = 0; i < matrixSize; i++)
	{
		for (size_t j = 0; j < matrixSize; j++)
		{
			if (inputFile.eof())
			{
				std::cout << "Error matrix is not full\n";
				return std::nullopt;
			}

			if (inputFile.fail())
			{
				std::cout << "Error matrix has a not number\n";
				return std::nullopt;
			}

			inputFile >> matrix[i][j];
		}
	}

	return matrix;
}

int main(int argc, char* argv[])
{
	const auto args = InitMainArguments(argc, argv);

	if (!args.has_value())
	{
		return 0;
	}

	std::ifstream inputFile;
	inputFile.open(args->matrixFile);

	if (!inputFile.is_open())
	{
		std::cout << "Error " << args->matrixFile << " didnt open\n";
		return 0;
	}

	auto matrix = ReadMatrixFromFile(inputFile);

	if (!matrix.has_value())
	{
		return 1;
	}

	return 0;
}
