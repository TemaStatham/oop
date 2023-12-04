#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
// в разных строках
constexpr int MIN_KEY_VALUE = 0;
constexpr int MAX_KEY_VALUE = 255;
constexpr int BYTE = 8;

// size t использовать uint8_t
const std::array<uint8_t, BYTE> MASK = { 2, 3, 4, 6, 7, 0, 1, 5 };
// cryptarg = operation
enum class Operations
{
	// заглваынми
	CRYPT,
	DECRYPT,
};

struct MainArguments
{
	std::string inputFile;
	std::string outputFile;
	unsigned char key;
	Operations arg;
};

std::optional<MainArguments> ParseMainArguments(int& argc, char* argv[]);
void Encrypt(std::istream& input, std::ostream& output, char key);
void Decrypt(std::istream& input, std::ostream& output, char key);

int main(int argc, char* argv[])
{
	auto arguments = ParseMainArguments(argc, argv);

	if (!arguments.has_value())
	{
		return 1;
	}
	// создание файлов в другой функции вызов трансформ ток
	std::ifstream inputFile(arguments->inputFile, std::ios::binary); // как открыть бинарно

	std::ofstream outputFile(arguments->outputFile, std::ios::binary);

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		std::cout << "Error " << arguments->inputFile << " or "
				  << arguments->outputFile << " didnt open\n";
		return 1;
	}

	if (arguments->arg == Operations::CRYPT)
	{
		Encrypt(inputFile, outputFile, arguments->key);
	}

	if (arguments->arg == Operations::DECRYPT)
	{
		Decrypt(inputFile, outputFile, arguments->key);
	}

	inputFile.close();
	outputFile.close();

	return 0;
}

bool IsNumeric(const std::string& str)
{
	auto it = str.begin();
	while (it != str.end())
	{
		if (!std::isdigit(*it))
		{
			return false;
		}
		it++;
	}
	return true;
}
// main delrete
std::optional<MainArguments> ParseMainArguments(int& argc, char* argv[])
{
	using namespace std::literals;

	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "crypt.exe crypt <input file> <output file> <key>\n"
				  << "or\n"
				  << "crypt.exe decrypt <input file> <output file> <key>\n";
		return std::nullopt;
	}

	if (!IsNumeric(argv[4]))
	{
		std::cout << "Error key has not digit\n";
		return std::nullopt;
	}
	// try catch stoi
	int keyInt = std::stoi(argv[4]);

	if (keyInt < MIN_KEY_VALUE || keyInt > MAX_KEY_VALUE)
	{
		std::cout << "Error the key value is not in the range from 0 to 255\n";
		return std::nullopt;
	}
	// dyblirovanie
	if (std::string(argv[1]) == "crypt")
	{
		MainArguments arguments(argv[2], argv[3], static_cast<unsigned char>(keyInt), CryptArg::crypt);
		return arguments;
	}

	if (std::string(argv[1]) == "decrypt"s)
	{
		MainArguments arguments(argv[2], argv[3], static_cast<unsigned char>(keyInt), CryptArg::decrypt);
		return arguments;
	}

	return std::nullopt;
}

// подумать над вынесением алгоритма шифрации в общую функцию
char EncryptByte(char byte, char key)
{
	byte ^= key;

	char result = 0;
	for (size_t sourcePos = 0; sourcePos < BYTE; ++sourcePos)
	{
		result |= (char)((byte >> sourcePos) & 1) << MASK[sourcePos];
	}

	return result;
}

char DecryptByte(char byte, char key)
{
	char result = 0;
	for (size_t sourcePos = 0; sourcePos < BYTE; ++sourcePos)
	{
		result |= (char)((byte >> MASK[sourcePos]) & 1) << sourcePos;
	}

	result ^= key;

	return result;
}
// transform lambda function peredat v arg
void Encrypt(std::istream& input, std::ostream& output, char key)
{
	char byte;
	while (input.read(&byte, sizeof(byte)))
	{
		char encryptedByte = EncryptByte(byte, key);
		output.write(&encryptedByte, sizeof(byte));
	}
}

void Decrypt(std::istream& input, std::ostream& output, char key)
{
	char byte;
	while (input.read(&byte, sizeof(byte)))
	{
		char decryptedByte = DecryptByte(byte, key);
		output.write(&decryptedByte, sizeof(byte));
	}
}