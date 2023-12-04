#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ExpandTemplate//stdafx.h"
#include "../ExpandTemplate/ExpandProcess.h"
#include "../ExpandTemplate/ParseParams.h"
#include <sstream>

SCENARIO("Test ExpandTemplate")
{
	WHEN("Just tests of task")
	{
		std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		std::map<std::string, std::string> params;
		params["Ivan Petrov"] = "%USER_NAME%";
		params["Friday"] = "{WEEK_DAY}";

		REQUIRE(ExpandTemplate(tpl, params) == "Hello, Ivan Petrov. Today is Friday.");
	}

	WHEN("Just tests of task")
	{
		std::string tpl = "-AABBCCCCCABC+";
		std::map<std::string, std::string> params;
		params["[a]"] = "A";
		params["[aa]"] = "AA";
		params["[b]"] = "B";
		params["[bb]"] = "BB";
		params["[c]"] = "C";
		params["[cc]"] = "CC";
		REQUIRE(ExpandTemplate(tpl, params) == "-[aa][bb][cc][cc][c][a][b][c]+");
	}
}

SCENARIO("Test ReplaceString ")
{
	WHEN("Test ReplaceString")
	{
		std::string subj = "hihellohihello", search = "hi", replace = "hi";
		std::vector<PositionUntouched> position;

		REQUIRE(ReplaceString(subj, search, replace, position) == "hihellohihello");

		replace = "hello";

		REQUIRE(ReplaceString(subj, search, replace, position) == "hellohellohellohello");
	}
}

SCENARIO("Check parse arguments")
{
	WHEN("Check parse arguments")
	{
		int argc = 5;

		char AA[2] = { 'A', 'A' };
		char A[1] = { 'A' };

		char bb[2] = { 'b', 'b' };
		char b[1] = { 'b' };

		char c[1] = { 'c' };

		char* argv[5] = { AA , A, bb, b, c };

		auto arg = ParseParams(argc, argv);

		REQUIRE(arg.has_value());
		REQUIRE(arg.value().params.size() == 1);

		argc = 2;
		arg = ParseParams(argc, argv);
		REQUIRE(!arg.has_value());
	}
}

SCENARIO("Test CheckValidPos")
{
	WHEN("Test CheckValidPos")
	{
		size_t pos = 20;
		std::vector<PositionUntouched> positions;

		positions.push_back({ 10,15 });

		REQUIRE(CheckValidPos(positions, pos));

		positions.push_back({ 16,21 });

		REQUIRE(CheckValidPos(positions, pos));
	}
}