#include "CMyString.h"

int main()
{
	CMyString str{ "a" };
	std::cout << str << "  - ";
	str = "asd";
	std::cout << str << "  - ";
	std::cin >> str;
	std::cout << str << "  - ";
	CMyString a = "das7";
	str = a + " asdasd";
	std::cout << str << "  - ";
	CMyString b = "9088989";
	str = str;
	std::cout << str << "  - ";
	str += "asd";
	std::cout << str << "  - ";
	std::string st = "		asd";
	str += st;
	std::cout << str << "  - ";
	std::cout << str[2] << std::endl;
	str[2] = '1';
	std::cout << str[2] << std::endl;
	CMyString my(nullptr);
	my.Clear();
}
