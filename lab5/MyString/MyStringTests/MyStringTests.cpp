#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../../MyString/MyString/CMyString.h"

TEST_CASE("Test initialization string")
{
	SECTION("Test default constructor string")
	{
		CMyString const s;

		REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
		REQUIRE(s.GetLength() == 0);
	}

	SECTION("Test constructor that initializes a string with string data")
	{
		SECTION("nullptr test")
		{
			CMyString const s(nullptr);

			REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
			REQUIRE(s.GetLength() == 0);
		}

		SECTION("char * test")
		{
			auto const cString = "artem";
			CMyString const s(cString);

			REQUIRE(std::strcmp(s.GetStringData(), cString) == 0);
			REQUIRE(s.GetLength() == std::strlen(cString));
		}
	}

	SECTION("Test constructors")
	{
		SECTION("char * test")
		{
			auto const cString = "artem";
			size_t const length = 5;
			CMyString const s(cString, length);

			REQUIRE(std::strcmp(s.GetStringData(), "artem") == 0);
			REQUIRE(s.GetLength() == length);
		}

		SECTION("nullptr test")
		{
			CMyString const s(nullptr, 42);

			REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
			REQUIRE(s.GetLength() == 0);
		}

		SECTION("null characters")
		{
			auto const cString = "Hello\0, wonderful\0 World!";
			size_t const length = 25;
			CMyString const s(cString, length);

			REQUIRE(std::memcmp(s.GetStringData(), cString, length) == 0);
			REQUIRE(s.GetLength() == length);
		}
	}

	SECTION("Test constructor std::string")
	{
		size_t const length = 25;
		std::string const stlString("Hello\0, wonderful\0 World!", length);
		CMyString const s(stlString);

		REQUIRE(std::memcmp(s.GetStringData(), stlString.c_str(), length) == 0);
		REQUIRE(s.GetLength() == length);
	}
}

TEST_CASE("Test other constructors")
{
	SECTION("test copy constructor")
	{
		CMyString s = "artem\0 copy\n!";
		CMyString const copy(s);

		REQUIRE(std::strcmp(s.GetStringData(), copy.GetStringData()) == 0);
		REQUIRE(s.GetLength() == copy.GetLength());
	}

	SECTION("test move constructor")
	{
		char const* initialString = "artem moved";
		size_t const initialLength = std::strlen(initialString);
		CMyString s = initialString;
		CMyString const moved(std::move(s));

		REQUIRE(std::strcmp(initialString, moved.GetStringData()) == 0);
		REQUIRE(initialLength == moved.GetLength());
	}
}

TEST_CASE("Test GetSubstring")
{
	CMyString s = "Hello, wonderful World!";

	SECTION("test whith length")
	{
		size_t const start = 0;
		size_t const length = 5;

		auto const subString = s.SubString(start, length);

		REQUIRE(std::strcmp(subString.GetStringData(), "Hello") == 0);
	}

	SECTION("test whithout not length")
	{
		size_t const start = 7;

		auto const subString = s.SubString(start);

		REQUIRE(std::strcmp(subString.GetStringData(), "wonderful World!") == 0);
	}

	SECTION("test whis length > str.length()")
	{
		size_t const start = 7;
		size_t const length = 420;

		auto const subString = s.SubString(start, length);

		REQUIRE(std::strcmp(subString.GetStringData(), "wonderful World!") == 0);
	}

	SECTION("test null characters")
	{
		CMyString sNulls = "Hello\0, wonderful\0 NULL!";
		size_t const start = 0;
		size_t const length = 8;

		auto const subString = sNulls.SubString(start, length);

		REQUIRE(std::strcmp(subString.GetStringData(), "Hello\0, ") == 0);
	}

	SECTION("test with start > s.length()")
	{
		size_t const start = 420;

		REQUIRE_THROWS_AS(s.SubString(start), std::out_of_range);
	}
}

TEST_CASE("Test Clear")
{
	CMyString s = "Hello, wonderful World!";
	s.Clear();

	REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
	REQUIRE(s.GetLength() == 0);

	s += "artem";
	REQUIRE(s.GetLength() == 5);
}

TEST_CASE("Test operators")
{
	SECTION("test operator ==")
	{
		REQUIRE(CMyString("Hello, World!") == CMyString("Hello, World!"));
		REQUIRE_FALSE(CMyString("Hello, World!") == CMyString("Goodbye, World!"));
	}

	SECTION("test operator !=")
	{
		REQUIRE_FALSE(CMyString("Hello, World!") != CMyString("Hello, World!"));
		REQUIRE(CMyString("Hello, World!") != CMyString("Goodbye, World!"));
	}

	SECTION("test operator <")
	{
		REQUIRE(CMyString("1") < CMyString("2"));
		REQUIRE_FALSE(CMyString("2") < CMyString("1"));
		REQUIRE_FALSE(CMyString("dsa") < CMyString("asd"));
	}

	SECTION("test operator >")
	{
		REQUIRE(CMyString("2") > CMyString("1"));
		REQUIRE_FALSE(CMyString("1") > CMyString("2"));
		REQUIRE_FALSE(CMyString("asd") > CMyString("dsa"));
	}

	SECTION("test operator <=")
	{
		REQUIRE(CMyString("1") <= CMyString("1"));
		REQUIRE_FALSE(CMyString("1230") <= CMyString("123"));
		REQUIRE(CMyString("asd") <= CMyString("asd"));
		REQUIRE(CMyString("a") <= CMyString("asd"));
	}

	SECTION("test operator >=")
	{
		REQUIRE(CMyString("2") >= CMyString("1"));
		REQUIRE_FALSE(CMyString("artem") >= CMyString("artyr"));
		REQUIRE(CMyString("123") >= CMyString("123"));
	}

	SECTION("test operator = copy")
	{
		CMyString s = "artem ivanov";
		CMyString copy;
		copy = s;

		REQUIRE(std::strcmp(s.GetStringData(), copy.GetStringData()) == 0);
	}

	SECTION("test operator = move")
	{
		char const* initialString = "artem ivanov";
		CMyString s = initialString;
		CMyString moved;
		moved = std::move(s);

		REQUIRE(std::strcmp(moved.GetStringData(), initialString) == 0);
		REQUIRE(s.GetStringData() == nullptr);
		REQUIRE(s.GetLength() == 0);
	}

	SECTION("test operator s = s")
	{
		char const* initialString = "artem ivanov";
		CMyString s = initialString;
		size_t const initialLength = s.GetLength();

		s = s;
		REQUIRE(std::strcmp(s.GetStringData(), initialString) == 0);
		REQUIRE(s.GetLength() == initialLength);

		s = std::move(s);
		REQUIRE(std::strcmp(s.GetStringData(), initialString) == 0);
		REQUIRE(s.GetLength() == initialLength);
	}

	SECTION("test operator [] modify")
	{
		CMyString s = "artem ivanov";
		s[0] = 'A';

		REQUIRE(std::strcmp(s.GetStringData(), "Artem ivanov") == 0);
	}

	SECTION("test operator [] read")
	{
		CMyString const s = "artem ivanov";

		REQUIRE(s[5] == ' ');
	}

	SECTION("test operator []")
	{
		CMyString s = "artem hello";
		CMyString const sConst = "artem hello";

		REQUIRE_THROWS_AS(s[420] = 'W', std::out_of_range);
		REQUIRE_THROWS_AS(sConst[420], std::out_of_range);
	}

	SECTION("test operator +=")
	{
		CMyString const s1("artem\0, ", 8);
		CMyString const s2("ivanov\0\n!", 7);
		auto const result = s1 + s2;

		REQUIRE(std::memcmp(result.GetStringData(), "artem\0, ivanov\0\n!", 15) == 0);
	}

	SECTION("test operator >>")
	{
		std::stringstream input;

		std::string const originalString("artem\0 \n ivanov!", 15);
		input.str(originalString);
		CMyString s;
		input >> s;

		REQUIRE(std::memcmp(s.GetStringData(), originalString.c_str(), 7) == 0);
	}

	SECTION("test operator <<")
	{
		std::stringstream output;

		char const* originalString = "aaaaa\0  aaa\0a!";
		size_t const length = 15;
		CMyString const s(originalString, length);
		output << s;

		REQUIRE(std::memcmp(output.str().c_str(), originalString, length) == 0);
	}
}
