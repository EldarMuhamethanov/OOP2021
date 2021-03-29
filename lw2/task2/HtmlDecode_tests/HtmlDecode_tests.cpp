#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task2/HtmlDecode.h"

using namespace std;

SCENARIO("HtmlDecode empty string gives empty string too")
{
	string str;
	REQUIRE(HtmlDecode(str).empty());
}

SCENARIO("HtmlDecode string without html gives the same string")
{
	string str = "Cat says Meow.";
	REQUIRE(HtmlDecode(str) == "Cat says Meow.");
}

SCENARIO("HtmlDecode string with html gives decoded string without html")
{
	string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	REQUIRE(HtmlDecode(str) == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("HtmlDecode string with html and unlnown html symbol gives decoded string without html, but with unknown html symbol")
{
	string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s&excl;";
	REQUIRE(HtmlDecode(str) == "Cat <says> \"Meow\". M&M's&excl;");
}

SCENARIO("HtmlDecode string with incorrect html gives the same string")
{
	string str = "&tuoq;";
	REQUIRE(HtmlDecode(str) == "&tuoq;");
}