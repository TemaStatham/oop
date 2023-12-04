#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../CHttpUrl.h"
#include "../CUrlParsingError.h"

TEST_CASE("ConstructFromUrl")
{
	SECTION("Valid HTTP URL")
	{
		CHttpUrl url("http://example.com/index.html");
		REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetDocument() == "/index.html");
		REQUIRE(url.GetPort() == 80);
	}

	SECTION("Valid HTTPS URL")
	{
		CHttpUrl url("https://example.com/index.html");
		REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetDocument() == "/index.html");
		REQUIRE(url.GetPort() == 443);
	}

	SECTION("URL with specified port")
	{
		CHttpUrl url("https://example.com:8080/index.html");
		REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetDocument() == "/index.html");
		REQUIRE(url.GetPort() == 8080);
	}

	SECTION("Invalid URL")
	{
		REQUIRE_THROWS_AS(CHttpUrl("example.com"), CUrlParsingError);
		REQUIRE_THROWS_AS(CHttpUrl("http:/example.com/index.html"), CUrlParsingError);
		REQUIRE_THROWS_AS(CHttpUrl("http://example.com:abc/index.html"), CUrlParsingError);
		REQUIRE_THROWS_AS(CHttpUrl("http://example.com:-1/index.html"), CUrlParsingError);
		REQUIRE_THROWS_AS(CHttpUrl("http://example.com:65535/index.html"), CUrlParsingError);
	}
}

TEST_CASE("ConstructFromDomainAndDocument")
{
	SECTION("Valid HTTP URL")
	{
		CHttpUrl url1("/example.com", "/index.html", CHttpUrl::Protocol::HTTP);
		REQUIRE(url1.GetProtocol() == CHttpUrl::Protocol::HTTP);
		REQUIRE(url1.GetDomain() == "/example.com");
		REQUIRE(url1.GetDocument() == "/index.html");
		REQUIRE(url1.GetPort() == 80);
	}

	SECTION("Valid HTTPS URL")
	{
		CHttpUrl url2("/example.com", "/index.html", CHttpUrl::Protocol::HTTPS);
		REQUIRE(url2.GetProtocol() == CHttpUrl::Protocol::HTTPS);
		REQUIRE(url2.GetDomain() == "/example.com");
		REQUIRE(url2.GetDocument() == "/index.html");
		REQUIRE(url2.GetPort() == 443);
	}

	SECTION("Valid HTTP URL with port")
	{
		CHttpUrl url3("/example.com", "/index.html", CHttpUrl::Protocol::HTTP, 8080);
		REQUIRE(url3.GetProtocol() == CHttpUrl::Protocol::HTTP);
		REQUIRE(url3.GetDomain() == "/example.com");
		REQUIRE(url3.GetDocument() == "/index.html");
		REQUIRE(url3.GetPort() == 8080);
	}

	SECTION("Invalid URL with port")
	{
		// REQUIRE_THROWS_AS(CHttpUrl("/example.com", "/index.html", CHttpUrl::Protocol::HTTP, 65536), CUrlParsingError);
	}
}

TEST_CASE("GetURL")
{
	CHttpUrl url("example.com", "/index.html", CHttpUrl::Protocol::HTTPS, 8080);
	REQUIRE(url.GetURL() == "https://example.com:8080/index.html");
}

TEST_CASE("GetDomain")
{
	CHttpUrl url("/example.com", "/index.html", CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetDomain() == "/example.com");
}

TEST_CASE("GetDocument")
{
	CHttpUrl url("/example.com", "/index.html", CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetDocument() == "/index.html");
}

TEST_CASE("GetProtocol")
{
	CHttpUrl url("/example.com", "/index.html", CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
}

TEST_CASE("GetPort")
{
	CHttpUrl url("/example.com", "/index.html", CHttpUrl::Protocol::HTTP, 8080);
	REQUIRE(url.GetPort() == 8080);
}

TEST_CASE("GetProtocolAsString")
{
	REQUIRE(GetProtocolAsString(CHttpUrl::Protocol::HTTP) == "http");
	REQUIRE(GetProtocolAsString(CHttpUrl::Protocol::HTTPS) == "https");
}
