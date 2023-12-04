#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <stack>
#include <string>

const int NUMBER_OF_PARAMS = 3;
const int MAX_REC_SIZE = 2500;
const int FIELD_SIZE = 100;
const int minFieldSize = 0;

using Field = std::array<std::array<char, FIELD_SIZE>, FIELD_SIZE>;

const char SPACE = ' ';
const char BORDER = '#';
const char CENTER = 'O';
const char DRAW = '-';

struct MainArguments
{
	std::string inputFile;
	std::string outputFile;
};

std::optional<MainArguments> ParseMainArguments(int& argc, char* argv[]);

bool Fill(const std::optional<MainArguments>& args);

int main(int argc, char* argv[])
{
	const auto args = ParseMainArguments(argc, argv);

	if (!args.has_value())
	{
		return 1;
	}

	if (!Fill(args))
	{
		return 1;
	}

	return 0;
}

bool IsOpenFiles(std::ifstream& in, std::ofstream& out)
{
	if (!in.is_open())
	{
		std::cout << "Error didnt open\n";
		return 1;
	}

	if (!out.is_open())
	{
		std::cout << "Error didnt open\n";
		return false;
	}

	return true;
}

std::optional<MainArguments> ParseMainArguments(int& argc, char* argv[])
{
	if (argc != NUMBER_OF_PARAMS)
	{
		std::cout << "Invalid argument count\n"
				  << "fill.exe <input file> <output file>\n";
		return std::nullopt;
	}

	MainArguments arguments({ argv[1], argv[2] });
	return arguments;
}

void ReadToStrokeEnd(std::istream& input)
{
	char ch;
	while (input.get(ch))
	{
		if (ch == '\n')
		{
			return;
		}
	}
}

Field ReadField(std::istream& input)
{
	Field field;

	std::fill(&field[0][0], &field[FIELD_SIZE - 1][FIELD_SIZE - 1], SPACE);

	char ch = ' ';

	for (size_t row = 0; row < FIELD_SIZE; row++)
	{
		for (size_t column = 0; column < FIELD_SIZE; column++)
		{
			if (input.eof())
			{
				return field;
			}
			// ïîèñêàòü â  ñòä àëüòåðíàòèâó äëÿ \í
			input.get(ch);

			if (ch == '\n')
			{
				break;
			}

			if (ch == CENTER || ch == BORDER)
			{
				field[row][column] = ch;
			}

			if (column == FIELD_SIZE - 1)
			{
				ReadToStrokeEnd(input);
			}
		}
	}

	return field;
}

void PrintField(Field& field, std::ofstream& outputFile)
{
	for (size_t row = 0; row < FIELD_SIZE; row++)
	{
		for (size_t column = 0; column < FIELD_SIZE; column++)
		{
			outputFile << field[row][column];
		}
		outputFile << '\n';
	}
}

struct Point
{
	// unsign int
	size_t x;
	size_t y;
};

void FillCell(Field& field, size_t row, size_t column, std::stack<Point>& stack, int countRec)
{
	if (column > FIELD_SIZE - 1 || column < minFieldSize
		|| row > FIELD_SIZE - 1 || row < minFieldSize)
	{
		return;
	}

	if (field[row][column] != SPACE)
	{
		return;
	}

	if (countRec == MAX_REC_SIZE)
	{
		Point p{ row, column };
		stack.push(p);
		return;
	}

	field[row][column] = DRAW;
	countRec++;

	FillCell(field, row + 1, column, stack, countRec);
	FillCell(field, row - 1, column, stack, countRec);
	FillCell(field, row, column + 1, stack, countRec);
	FillCell(field, row, column - 1, stack, countRec);

	while (!stack.empty() && countRec == 1)
	{
		FillCell(field, stack.top().x, stack.top().y, stack, countRec);
		stack.pop();
	}
}

void FillField(Field& field)
{
	for (size_t row = 0; row < FIELD_SIZE; row++)
	{
		for (size_t column = 0; column < FIELD_SIZE; column++)
		{
			if (field[row][column] != CENTER)
			{
				continue;
			}

			std::stack<Point> stack;
			int countReñ = 0;
			field[row][column] = SPACE;
			FillCell(field, row, column, stack, countReñ);
			field[row][column] = CENTER;
		}
	}
}
// peredat imena failov
bool Fill(const std::optional<MainArguments>& args)
{
	std::ifstream inputFile(args->inputFile);
	std::ofstream outputFile(args->outputFile);

	if (!inputFile.is_open())
	{
		std::cout << "Error didnt open" << std::endl;
		return false;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Error didnt open" << std::endl;
		return false;
	}

	Field field = ReadField(inputFile);

	FillField(field);
	PrintField(field, outputFile);

	inputFile.close();
	outputFile.close();

	return true;
}