#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task1/CHttpUrl.h"
#include "../task1/CUrlParsingError.h"

using namespace std;

SCENARIO("create CHttpUrl without protocol")
{
	CHttpUrl httpUrl("domain", "document");
	REQUIRE(httpUrl.GetDomain() == "domain");
	REQUIRE(httpUrl.GetDocument() == "/document");
	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTP);
	REQUIRE(httpUrl.GetPort() == 80);
	REQUIRE(httpUrl.GetURL() == "http://domain/document");
}

SCENARIO("create CHttpUrl with protocol")
{
	CHttpUrl httpUrl("domain", "/document", Protocol::HTTPS);
	REQUIRE(httpUrl.GetDomain() == "domain");
	REQUIRE(httpUrl.GetDocument() == "/document");
	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTPS);
	REQUIRE(httpUrl.GetPort() == 443);
	REQUIRE(httpUrl.GetURL() == "https://domain/document");
}

SCENARIO("create CHttpUrl with protocol and port")
{
	CHttpUrl httpUrl("domain", "/document", Protocol::HTTPS, 12345);
	REQUIRE(httpUrl.GetDomain() == "domain");
	REQUIRE(httpUrl.GetDocument() == "/document");
	REQUIRE(httpUrl.GetProtocol() == Protocol::HTTPS);
	REQUIRE(httpUrl.GetPort() == 12345);
	REQUIRE(httpUrl.GetURL() == "https://domain:12345/document");
}

SCENARIO("create CHttpUrl with invalid domain")
{
	try
	{
		CHttpUrl httpUrl("", "/document", Protocol::HTTPS, 12345);
		REQUIRE(false);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
	}
}

SCENARIO("create CHttpUrl with invalid port")
{
	try
	{
		CHttpUrl httpUrl("domain", "/document", Protocol::HTTPS, 65535);
		REQUIRE(true);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(false);
	}
	try
	{
		CHttpUrl httpUrl("domain", "/document", Protocol::HTTPS, 1);
		REQUIRE(true);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(false);
	}
	try
	{
		CHttpUrl httpUrl("domain", "/document", Protocol::HTTPS, 0);
		REQUIRE(false);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
	}
}

SCENARIO("ParseURL valid url with protocol http gives protocol http")
{
    string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetProtocol() == Protocol::HTTP);
}

SCENARIO("ParseURL valid url with protocol http in different case gives protocol http")
{
    string url = "hTTp://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetProtocol() == Protocol::HTTP);
}

SCENARIO("ParseURL valid url with protocol https gives protocol https")
{
    string url = "https://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetProtocol() == Protocol::HTTPS);
}

SCENARIO("ParseURL valid url with protocol https in different case gives protocol https")
{
    string url = "htTPs://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetProtocol() == Protocol::HTTPS);
}

SCENARIO("ParseURL invalid url with invalid protocol 'unknown' gives false")
{
    string url = "unknown://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    try
    {
        CHttpUrl httpUrl(url);
        REQUIRE(false);
    }
    catch (const CUrlParsingError& e)
    {
        REQUIRE(e.what() == "invalid protocol"s);
    }
}

SCENARIO("ParseURL valid url with host \"www.mysite.com\" gives host \"www.mysite.com\"")
{
    string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetDomain() == "www.mysite.com");
}

SCENARIO("ParseURL invalid url empty host gives false")
{
    string url = "ftp:///docs/document1.html?page=30&lang=en#title";
    try
    {
        CHttpUrl httpUrl(url);
        REQUIRE(false);
    }
    catch (const CUrlParsingError& e)
    {
        REQUIRE(e.what() == "invalid url"s);
    }
}

SCENARIO("ParseURL with protocol http and without port gives default port for http")
{
    string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetPort() == 80);
}

SCENARIO("ParseURL with protocol https and without port gives default port for https")
{
    string url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetPort() == 443);
}

SCENARIO("ParseURL with protocol http and port 8000 gives port 8000")
{
    string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetPort() == 8000);
}

SCENARIO("ParseURL with valid port 1 gives valid URL")
{
    string url = "http://www.mysite.com:1/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetPort() == 1);
}
SCENARIO("ParseURL with valid port 65535 gives valid URL")
{
    string url = "http://www.mysite.com:65535/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetPort() == 65535);
}
SCENARIO("ParseURL with invalid port 0 gives invalid URL")
{
    string url = "http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
    try
    {
        CHttpUrl httpUrl(url);
        REQUIRE(false);
    }
    catch (const CUrlParsingError& e)
    {
        REQUIRE(e.what() == "invalid port"s);
    }
}
SCENARIO("ParseURL valid url with document gives right document")
{
    string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
}

SCENARIO("ParseURL valid url without document gives empty document")
{
    string url = "http://www.mysite.com/";
    CHttpUrl httpUrl(url);
    REQUIRE(httpUrl.GetDocument() == "/");
}

SCENARIO("Parse invalid url with invalid port with two separator \":\"")
{
    string url = "http://w:1234:9/";
    try
    {
        CHttpUrl httpUrl(url);
        REQUIRE(false);
    }
    catch (const CUrlParsingError& e)
    {
        REQUIRE(e.what() == "invalid port"s);
    }
}

SCENARIO("Parse invalid url with invalid port with character")
{
    string url = "http://w:123e/";
    try
    {
        CHttpUrl httpUrl(url);
        REQUIRE(false);
    }
    catch (const CUrlParsingError& e)
    {
        REQUIRE(e.what() == "invalid port"s);
    }
}

SCENARIO("Parse invalid url with double :: port")
{
    string url = "http://www::123/";
    try
    {
        CHttpUrl httpUrl(url);
        REQUIRE(false);
    }
    catch (const CUrlParsingError& e)
    {
        REQUIRE(e.what() == "invalid port"s);
    }
}