#include <iostream>
#include <limits>
#include <optional>
#include <string>

const int numberOfParams = 4, maxNumberSystem = 36, minNumberSystem = 2;

struct MainArguments
{
	MainArguments()
		: destinationNotation(0)
		, sourceNotation(0){};

	MainArguments(int _destinationNotation, int _sourceNotation, std::string _value)
		: destinationNotation(_destinationNotation)
		, sourceNotation(_sourceNotation)
		, value(_value){};

	int destinationNotation;
	int sourceNotation;
	std::string value;
};
//TODO: ИЗБАВСЯОТ ВАС ЕРОР
void CheckInputNumberSystem(const int& numberSystem, bool& wasError)
{
	if (numberSystem < minNumberSystem || numberSystem > maxNumberSystem)
	{
		wasError = true;
	}
}

char DigitToSymbol(const int& number, bool& wasError, const int& radix)
{
	const char out[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	if (number > radix || number < 0)
	{
		wasError = true;
		return '0';
	}

	return out[number];
}

int SymbolToDigit(const char& symbol)
{
	if (symbol >= '0' && symbol <= '9')
	{
		return symbol - '0';
	}

	if (symbol >= 'A' && symbol <= 'Z')
	{
		return symbol - '0' - 7;
	}

	return INT_MIN;
}

void CheckСontentOfCorrectNumbers(const char& ch, const int& radix, bool& wasError)
{
	if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z'))
	{
		const char out[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

		for (int i = 0; i < maxNumberSystem; i++)
		{
			if (ch == out[i] && i > radix)
			{
				std::cout << ch << " didn`t correct\n";
				wasError = true;
				return;
			}
		}

		return;
	}
	wasError = true;
}

unsigned long long StringToInt(const std::string& str, const int& radix, bool& wasError)
{
	unsigned long long result = 0;
	int number = 0;

	for (size_t i = 0, n = str.length() - 1; i < str.length() && n >= 0; n--, i++)
	{
		number = SymbolToDigit(str[i]);
		//todo: переделать проверку оверфлойу
		if (result + (static_cast<unsigned long long>(pow(radix, n))) * number >= ULLONG_MAX)
		{
			std::cout << "Overflow " << result << "\n";
			wasError = true;
		}

		result += (static_cast<unsigned long long>(pow(radix, n))) * number;
		//todo: удалить
		CheckСontentOfCorrectNumbers(str[i], radix, wasError);

		if (wasError)
		{
			return 0;
		}
	}

	return result;
}

std::string IntToString(const unsigned long long& n, const int& radix, bool& wasError)
{
	unsigned long long copyValue = n;
	int remainder = 0;
	std::string result;

	while (copyValue)
	{
		remainder = copyValue % radix;
		result += DigitToSymbol(remainder, wasError, radix);
		copyValue = copyValue / radix;
	}

	std::reverse(result.begin(), result.end());

	return result;
}
//TODO: избавиться от вас еррор
std::optional<MainArguments> InitMainArguments(int& argc, char* argv[], bool& wasError)
{
	if (argc != numberOfParams)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: task2.exe <source notation> <destination notation> <value>\n";
		wasError = true;
		return std::nullopt;
	}
	//TODO: ДОБАВИТЬ ПРОВЕРКУ НА НЕ ЧИСЛО И  ТЕСТЫ
	MainArguments arguments(std::stoi(argv[2]), std::stoi(argv[1]), argv[3]);

	CheckInputNumberSystem(arguments.sourceNotation, wasError);
	CheckInputNumberSystem(arguments.destinationNotation, wasError);

	if (wasError)
	{
		std::cout << "Error, program works only for number systems from 2 to 36\n";
		return std::nullopt;
	}

	return arguments;
}

int main(int argc, char* argv[])
{
	bool wasError = false;

	auto arguments = InitMainArguments(argc, argv, wasError);

	if (wasError)
	{
		return 0;
	}

	if (arguments->value.front() == '-')
	{
		arguments->value.erase(arguments->value.begin());
		std::cout << '-';
	}

	if (arguments->value == "0")
	{
		std::cout << "0\n";
		return 0;
	}
	//todo: переименовать в корект название переменной
	unsigned long long numberToDeci = StringToInt(arguments->value, arguments->sourceNotation, wasError);

	if (wasError)
	{
		std::cout << "Error failed to convert string to number\n";
		return 0;
	}
	//todo: переименовать в резалт 
	//todo: с мионусом поработать
	std::string numberFromDeci = IntToString(numberToDeci, arguments->destinationNotation, wasError);

	if (wasError)
	{
		std::cout << "Error failed to convert number to string\n";
		return 0;
	}

	std::cout << numberFromDeci << "\n";

	return 0;
}
