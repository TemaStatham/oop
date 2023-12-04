#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

//Todo: констатныти надо с большой буквы и ниж подчеркавнеие

const int numberOfParams = 3;////Todo: удалить
const size_t matrixSize = 3;

using Mat3x3 = std::array<std::array<double, matrixSize>, matrixSize>;

struct MainArguments
{
	MainArguments(){};

	MainArguments(std::string _matrixFile1, std::string _matrixFile2)
		: matrixFile1(_matrixFile1)
		, matrixFile2(_matrixFile2){};

	std::string matrixFile1;
	std::string matrixFile2;
};

std::optional<MainArguments> ParseMainArguments(int& argc, char* argv[]);
Mat3x3 MultiplyMatrix(const Mat3x3& matrix1, const Mat3x3& matrix2);
Mat3x3 ReadMatrixFromFile(std::ifstream& inputFile, bool& wasError);
void PrintMatrix(const Mat3x3& matrix);

//Todo: упроститить функцию менй
int main(int argc, char* argv[])
{
	const auto arguments = ParseMainArguments(argc, argv);

	bool wasError = false;//Todo: переменные следует обьявлять коло ее нач использования

	if (!arguments.has_value())
	{
		return 1;
	}

	//Todo: сделать функцию для инициализации ивстрим
	std::ifstream inputFile1;
	inputFile1.open(arguments->matrixFile1);

	if (!inputFile1.is_open())
	{
		std::cout << "Error " << arguments->matrixFile1 << " didnt open\n";
		return 1;
	}

	std::ifstream inputFile2;
	inputFile2.open(arguments->matrixFile2);

	if (!inputFile2.is_open())
	{
		std::cout << "Error " << arguments->matrixFile2 << " didnt open\n";
		return 1;
	}

	const Mat3x3 matrix1 = ReadMatrixFromFile(inputFile1, wasError);

	if (wasError)
	{
		return 1;
	}

	//PrintMatrix(matrix1);

	const Mat3x3 matrix2 = ReadMatrixFromFile(inputFile2, wasError);

	if (wasError)
	{
		return 1;
	}

	//PrintMatrix(matrix2);

	const Mat3x3 multmatrix = MultiplyMatrix(matrix1, matrix2);

	PrintMatrix(multmatrix);

	return 0;
}

std::optional<MainArguments> ParseMainArguments(int& argc, char* argv[])
{
	if (argc != numberOfParams)
	{
		std::cout << "Invalid argument count\n"
				  << "multmatrix.exe <matrix file1> <matrix file2>\n";
		return std::nullopt;
	}

	MainArguments arguments(argv[1], argv[2]);

	return arguments;
}

Mat3x3 ReadMatrixFromFile(std::ifstream& inputFile, bool& wasError)
{
	//Todo: проинициализироват вас ерор тут
	Mat3x3 matrix{ { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } } };

	for (size_t row = 0; row < matrixSize; row++)
	{
		for (size_t column = 0; column < matrixSize; column++)
		{
			if (inputFile.eof())
			{
				std::cout << "Error matrix is not full\n";
				wasError = true;
				return matrix;
			}

			if (inputFile.fail())
			{
				std::cout << "Error matrix has a not number\n";
				wasError = true;
				return matrix;
			}

			inputFile >> matrix[row][column];
		}
	}

	return matrix;
}

Mat3x3 MultiplyMatrix(const Mat3x3& matrix1, const Mat3x3& matrix2)
{
	Mat3x3 multmatrix{};

	for (size_t row = 0; row < matrixSize; row++)
	{
		for (size_t column = 0; column < matrixSize; column++)
		{
			for (size_t i = 0; i < matrixSize; i++)
			{
				multmatrix[row][column] += matrix1[row][i] * matrix2[i][column];
			}
		}
	}

	return multmatrix;
}

void PrintMatrix(const Mat3x3& matrix)
{
	std::cout << std::fixed;

	for (size_t row = 0; row < matrixSize; row++)
	{
		for (size_t column = 0; column < matrixSize; column++)
		{
			std::cout << std::setprecision(3) << matrix[row][column] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";// Todo: лишнее
}
