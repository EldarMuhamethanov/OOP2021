#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task2/CMyString.h"

using namespace std;

SCENARIO("Constructors tests")
{
	WHEN("test constructor default")
	{
		CMyString myString;
		REQUIRE(myString.GetLength() == 0);
		REQUIRE(strcmp(myString.GetStringData(), "") == 0);
	}
	WHEN("test constructor with char*")
	{
		const char* initStr = "test";
		CMyString myString(initStr);
		REQUIRE(myString.GetLength() == 4);
		REQUIRE(strcmp(myString.GetStringData(), "test") == 0);
	}
	WHEN("test constructor with char* and length")
	{
		const char* initStr = "test";
		CMyString myString(initStr, 5);
		REQUIRE(myString.GetLength() == 5);
		REQUIRE(strcmp(myString.GetStringData(), "test") == 0);
	}
	WHEN("test constructor with string")
	{
		string s = "test";
		CMyString myString(s);
		REQUIRE(myString.GetLength() == 4);
		REQUIRE(strcmp(myString.GetStringData(), "test") == 0);
	}
	WHEN("test constructor of copy")
	{
		const char* ch = "other";
		CMyString myString("current");
		myString = ch;
		REQUIRE(myString.GetLength() == 5);
		REQUIRE(strcmp(myString.GetStringData(), "other") == 0);
		REQUIRE(strlen(ch) == 5);
		REQUIRE(strcmp(ch, "other") == 0);
	}
	WHEN("test constructor of moving")
	{
		CMyString ch("other");
		CMyString myString("current");
		myString = move(ch);
		REQUIRE(myString.GetLength() == 5);
		REQUIRE(strcmp(myString.GetStringData(), "other") == 0);
		REQUIRE(ch.GetLength() == 0);
		REQUIRE(strcmp(ch.GetStringData(), "") == 0);
	}
}

SCENARIO("Test substring")
{
	WHEN("With param length")
	{
		CMyString s("string test");
		CMyString s2 = s.SubString(7, 2);
		REQUIRE(s2.GetLength() == 2);
		REQUIRE(strcmp(s2.GetStringData(), "te") == 0);
	}
	WHEN("Without param length")
	{
		CMyString s("string test");
		CMyString s2 = s.SubString(7);
		REQUIRE(s2.GetLength() == 4);
		REQUIRE(strcmp(s2.GetStringData(), "test") == 0);
	}
}

SCENARIO("Test clear string")
{
	CMyString s("string test");
	s.Clear();
	REQUIRE(s.GetLength() == 0);
	REQUIRE(strcmp(s.GetStringData(), "") == 0);
}

SCENARIO("Test [] operator")
{
	WHEN("const []")
	{
		CMyString s("string test");
		REQUIRE(s[1] == 't');
	}
	WHEN("change char by index")
	{
		CMyString s("string test");
		s[1] = 'l';
		REQUIRE(s[1] == 'l');
	}
}

SCENARIO("Test += operator")
{
	CMyString s1("string ");
	CMyString s2("test");
	s1 += s2;
	REQUIRE(s1.GetLength() == 11);
	REQUIRE(strcmp(s1.GetStringData(), "string test") == 0);
}

SCENARIO("Test + operator")
{
	WHEN("CMyString + CMyString")
	{
		CMyString s1("string ");
		CMyString s2("test");
		CMyString s3 = s1 + s2;
		REQUIRE(s3.GetLength() == 11);
		REQUIRE(strcmp(s3.GetStringData(), "string test") == 0);
	}
	WHEN("CMyString + std::string")
	{
		CMyString s1("string ");
		CMyString s3 = s1 + "test"s;
		REQUIRE(s3.GetLength() == 11);
		REQUIRE(strcmp(s3.GetStringData(), "string test") == 0);
	}
	WHEN("CMyString + char*")
	{
		CMyString s1("string ");
		CMyString s3 = s1 + "test";
		REQUIRE(s3.GetLength() == 11);
		REQUIRE(strcmp(s3.GetStringData(), "string test") == 0);
	}
	WHEN("CMyString + char")
	{
		CMyString s1("string ");
		CMyString s3 = s1 + 't';
		REQUIRE(s3.GetLength() == 11);
		REQUIRE(strcmp(s3.GetStringData(), "string t") == 0);
	}
}

SCENARIO("Test operator == and !=")
{
	CMyString s1("aaa");
	CMyString s2("aaa");
	REQUIRE(s1 == s2);

	CMyString s3("aaa");
	CMyString s4("aa");
	REQUIRE(s3 != s4);
}

SCENARIO("Test operator <, >, <=, >=")
{
	CMyString s1("aa");
	CMyString s2("aaa");
	REQUIRE(s1 < s2);

	CMyString s3("ab");
	CMyString s4("aaa");
	REQUIRE(s3 > s4);

	CMyString s5("aaa");
	CMyString s6("aaa");
	REQUIRE(s5 <= s6);

	CMyString s7("aaa");
	CMyString s8("aaa");
	REQUIRE(s7 >= s8);
}

SCENARIO("Test <<, >>")
{
	WHEN("test << operator")
	{
		CMyString s("string test");
		ostringstream strm("");
		strm << s;
		REQUIRE(strm.str() == "string test");
	}
	WHEN("test >> operator")
	{
		istringstream strm("string test\noperator");
		CMyString s1;
		CMyString s2;
		strm >> s1 >> s2;
		REQUIRE(strcmp(s1.GetStringData(), "string") == 0);
		REQUIRE(strcmp(s2.GetStringData(), "test") == 0);
	}
}