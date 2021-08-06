#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task21/CMyArray.h"

using namespace std;

template <typename T>
string PrintArray(CMyArray<T> arr)
{
	ostringstream strm("");

	auto it = arr.begin();
	while (it != arr.end())
	{
		strm << *it << " ";
		++it;
	}
	string res = strm.str();
	if (arr.GetLength() > 0)
		res.pop_back();
	return res;
}


SCENARIO("tests constructors")
{
	WHEN("empty constructor")
	{
		CMyArray<int> arr;
		REQUIRE(arr.GetLength() == 0);
	}
	WHEN("constructor with length")
	{
		CMyArray<int> arr(10);
		REQUIRE(arr.GetLength() == 10);
	}
	WHEN("constructor with length and value")
	{
		CMyArray<int> arr(10, 5);
		REQUIRE(arr.GetLength() == 10);
		REQUIRE(PrintArray(arr) == "5 5 5 5 5 5 5 5 5 5");
	}
}

SCENARIO("test constructors of copy/move")
{
	CMyArray<int> arr(2, 5);

	CMyArray<int> copiedArr = arr;
	REQUIRE(arr.GetLength() == 2);
	REQUIRE(PrintArray(arr) == "5 5");
	REQUIRE(copiedArr.GetLength() == 2);
	REQUIRE(PrintArray(copiedArr) == "5 5");

	CMyArray<int> movedArr = move(arr);
	REQUIRE(movedArr.GetLength() == 2);
	REQUIRE(PrintArray(movedArr) == "5 5");
	REQUIRE(arr.GetLength() == 0);
	REQUIRE(PrintArray(arr) == "");
}

SCENARIO("test array operations")
{
	CMyArray<string> arr(2, "5");

	REQUIRE(arr.GetLength() == 2);
	REQUIRE(PrintArray(arr) == "5 5");

	arr.Push("6");
	REQUIRE(arr.GetLength() == 3);
	REQUIRE(PrintArray(arr) == "5 5 6");

	arr[2] = "7";
	REQUIRE(arr.GetLength() == 3);
	REQUIRE(PrintArray(arr) == "5 5 7");

	arr.Resize(4);
	arr[3] = "8";
	REQUIRE(arr.GetLength() == 4);
	REQUIRE(PrintArray(arr) == "5 5 7 8");

	WHEN("catch exception out of range")
	{
		REQUIRE_THROWS(arr[4]);
	}

	arr.Clear();
	REQUIRE(arr.GetLength() == 0);
	REQUIRE(PrintArray(arr) == "");
}

SCENARIO("iterators test")
{
	CMyArray<int> arr;

	arr.Push(1);
	arr.Push(2);

	WHEN("test Iterator")
	{
		auto it = arr.begin();
		string res;
		while (it != arr.end())
		{
			res += to_string(*it) + " ";
			++it;
		}
		REQUIRE(res == "1 2 ");

		auto revIt = arr.end();
		string revRes;
		while (revIt != arr.begin())
		{
			--revIt;
			revRes += to_string(*revIt) + " ";
		}
		REQUIRE(revRes == "2 1 ");
	}
	WHEN("test reverse Iterator")
	{
		auto it = arr.rbegin();
		string res;
		while (it != arr.rend())
		{
			res += to_string(*it) + " ";
			++it;
		}
		REQUIRE(res == "2 1 ");
	}
}