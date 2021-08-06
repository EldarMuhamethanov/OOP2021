#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task22/CMyArray.h"

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
	if (arr.GetSize() > 0)
		res.pop_back();
	return res;
}


SCENARIO("tests constructors")
{
	WHEN("empty constructor")
	{
		CMyArray<int> arr;
		REQUIRE(arr.GetSize() == 0);
	}
}

SCENARIO("test constructors of copy/move")
{
	CMyArray<int> arr;
	arr.Append(1);
	arr.Append(2);
	CMyArray<int> copiedArr = arr;
	REQUIRE(arr.GetSize() == 2);
	REQUIRE(PrintArray(arr) == "1 2");
	REQUIRE(copiedArr.GetSize() == 2);
	REQUIRE(PrintArray(copiedArr) == "1 2");

	CMyArray<int> movedArr = move(arr);
	REQUIRE(movedArr.GetSize() == 2);
	REQUIRE(PrintArray(movedArr) == "1 2");
	REQUIRE(arr.GetSize() == 0);
	REQUIRE(PrintArray(arr) == "");
}

SCENARIO("test array operations")
{
	CMyArray<string> arr;

	REQUIRE(arr.GetSize() == 0);
	REQUIRE(PrintArray(arr) == "");

	arr.Append("6");
	REQUIRE(arr.GetSize() == 1);
	REQUIRE(PrintArray(arr) == "6");

	arr[0] = "7";
	REQUIRE(arr.GetSize() == 1);
	REQUIRE(PrintArray(arr) == "7");

	arr.Resize(4);
	arr[3] = "8";
	REQUIRE(arr.GetSize() == 4);
	REQUIRE(PrintArray(arr) == "7   8");

	WHEN("catch exception out of range")
	{
		REQUIRE_THROWS(arr[4]);
	}

	arr.Clear();
	REQUIRE(arr.GetSize() == 0);
	REQUIRE(PrintArray(arr) == "");
}

SCENARIO("iterators test")
{
	CMyArray<int> arr;

	arr.Append(1);
	arr.Append(2);

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