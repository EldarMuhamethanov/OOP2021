#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task2/HtmlDecode.h"

using namespace std;


SCENARIO("HtmlDecode string without html gives the same string")
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