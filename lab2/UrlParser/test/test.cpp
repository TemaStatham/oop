#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../UrlParser/URLWork.h"
#include "../UrlParser/URLWorkTest.h"
#include <sstream>

SCENARIO("Test URL parsing")
{
	WHEN("Test the work of the url from the task")
	{
		std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";

		Protocol protocol;
		int port = 0;
		std::string host, document;

		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTP);
		REQUIRE(port == 80);
		REQUIRE(host == "www.mysite.com");
		REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
	}

	WHEN("Test the work of the url from the task with port")
	{
		std::string url = "http://www.mysite.com:2090/docs/document1.html?page=30&lang=en#title";

		Protocol protocol;
		int port = 0;
		std::string host, document;

		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTP);
		REQUIRE(port == 2090);
		REQUIRE(host == "www.mysite.com");
		REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
	}

	WHEN("Test the work of the no valid urls ")
	{
		std::string url = "http:/www.mysite.com/docs/document1.html?page=30&lang=en#title";

		Protocol protocol;
		int port = 0;
		std::string host, document;

		REQUIRE(!ParseURL(url, protocol, port, host, document));

		url = "http:///docs/document1.html?page=30&lang=en#title";
		REQUIRE(!ParseURL(url, protocol, port, host, document));

		url = "";
		REQUIRE(!ParseURL(url, protocol, port, host, document));

		url = "://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		REQUIRE(!ParseURL(url, protocol, port, host, document));

		url = "ftp://www.mysite.com";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::FTP);
		REQUIRE(port == 21);
		REQUIRE(host == "www.mysite.com");
		REQUIRE(document == "");
	}

}

SCENARIO("Test URL work ")
{
	WHEN("Just test for 1 url")
	{
		std::stringstream in("HTTP://www.mysite.com:2090/docs/document1.html?page=30&lang=en#title");
		std::stringstream out;

		URLWork(in, out);

		std::stringstream res("HTTP://www.mysite.com:2090/docs/document1.html?page=30&lang=en#title\nHOST : www.mysite.com\nPORT : 2090\nDOC : docs/document1.html?page=30&lang=en#title\n");

		REQUIRE(out.str() == res.str());
	}

	WHEN("Test for many url")
	{
		std::stringstream in("http://www.mysite.com:2090/docs/document1.html?page=30&lang=en#title\n"
			"http://www.mysite.com/docs/document1.html?page=30&lang=en#title\n");
		std::stringstream out;

		URLWork(in, out);

		std::stringstream res("http://www.mysite.com:2090/docs/document1.html?page=30&lang=en#title"
			"\nHOST : www.mysite.com"
			"\nPORT : 2090"
			"\nDOC : docs/document1.html?page=30&lang=en#title\n"
			"http://www.mysite.com/docs/document1.html?page=30&lang=en#title\n"
			"HOST : www.mysite.com\n"
			"PORT : 80\n"
			"DOC : docs/document1.html?page=30&lang=en#title\n");

		REQUIRE(out.str() == res.str());
	}

	WHEN("Test for no valid url")
	{
		std::stringstream in("");
		std::stringstream out;

		URLWork(in, out);

		std::stringstream res("");

		REQUIRE(out.str() == res.str());

		in.str() = "www.mysite.com:2090/docs/document1.html?page=30&lang=en#title";

		REQUIRE(out.str() == res.str());

		in.str() = "http://www.mysite.com:6555555/docs/document1.html?page=30&lang=en#title";
		REQUIRE(out.str() == res.str());

		in.str() = "http://www.mysite.com:-1/docs/document1.html?page=30&lang=en#title";
		REQUIRE(out.str() == res.str());
	}
}