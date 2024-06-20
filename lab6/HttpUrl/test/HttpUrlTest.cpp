#include "catch2/catch_test_macros.hpp"
#include "HttpUrl.h"
#include "UrlParsingError.h"

TEST_CASE("HttpUrl constructor with full URL")
{
	SECTION("Valid HTTP URL")
	{
		HttpUrl url("http://example.com/index.html");
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetDocument() == "/index.html");
		REQUIRE(url.GetPort() == 80);
	}

	SECTION("Valid HTTPS URL with non-standard port")
	{
		HttpUrl url("https://example.com:8080/docs");
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetDocument() == "/docs");
		REQUIRE(url.GetPort() == 8080);
	}

	SECTION("Invalid URL without protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("example.com/index.html"), UrlParsingError);
	}

	SECTION("Invalid URL with unsupported protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("ftp://example.com/index.html"), UrlParsingError);
	}
}

TEST_CASE("HttpUrl constructor with domain, document, and protocol")
{
	SECTION("Valid HTTP URL")
	{
		HttpUrl url("example.com", "index.html", Protocol::HTTP);
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetDocument() == "/index.html");
		REQUIRE(url.GetPort() == 80);
	}

	SECTION("Document without leading slash")
	{
		HttpUrl url("example.com", "docs", Protocol::HTTPS);
		REQUIRE(url.GetDocument() == "/docs");
	}
}

TEST_CASE("HttpUrl constructor with domain, document, protocol, and port")
{
	SECTION("Valid URL with non-standard port")
	{
		HttpUrl url("example.com", "/docs", Protocol::HTTP, 8080);
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetDocument() == "/docs");
		REQUIRE(url.GetPort() == 8080);
	}

	SECTION("Invalid port")
	{
		REQUIRE_THROWS_AS(HttpUrl("example.com", "/docs", Protocol::HTTPS, 0), std::invalid_argument);
	}
}

TEST_CASE("HttpUrl methods")
{
	HttpUrl url("https://example.com:8080/docs");

	SECTION("GetURL")
	{
		REQUIRE(url.GetURL() == "https://example.com:8080/docs");
	}

	SECTION("GetDomain")
	{
		REQUIRE(url.GetDomain() == "example.com");
	}

	SECTION("GetDocument")
	{
		REQUIRE(url.GetDocument() == "/docs");
	}

	SECTION("GetProtocol")
	{
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
	}

	SECTION("GetPort")
	{
		REQUIRE(url.GetPort() == 8080);
	}
}