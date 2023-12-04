#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTMLDecode/Decode.h"
#include <sstream>

SCENARIO("Decode check")
{
	WHEN("Decode check for an empty string")
	{
		std::stringstream in("");
		std::stringstream out;
		ProcessHtmlText(in, out);
		REQUIRE(out.str().empty());
	}

	WHEN("Decode check for string with no special characters ")
	{
		std::stringstream in("Hello my name Pablo");
		std::stringstream out;
		ProcessHtmlText(in, out);
		REQUIRE(out.str() == "Hello my name Pablo\n");
	}

	WHEN("Decode check for string with special characters ")
	{
		std::stringstream in("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
		std::stringstream out;
		ProcessHtmlText(in, out);
		REQUIRE(out.str() == "Cat <says> \u0022Meow\u0022. M&M's\n");
	}

	WHEN("Decode check for text with no special characters  ")
	{
		std::stringstream in("Hello my name Sasha\n I dictor masterskaya nastroeniya");
		std::stringstream out;
		ProcessHtmlText(in, out);
		REQUIRE(out.str() == "Hello my name Sasha\n I dictor masterskaya nastroeniya\n");
	}

	WHEN("Decode check for text with special characters ")
	{
		std::stringstream in("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s\nCat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
		std::stringstream out;
		ProcessHtmlText(in, out);
		REQUIRE(out.str() == "Cat <says> \u0022Meow\u0022. M&M's\nCat <says> \u0022Meow\u0022. M&M's\n");
	}
}