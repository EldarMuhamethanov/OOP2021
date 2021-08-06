#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task2/CStringList.h"

using namespace std;

string GetStringListValues(CStringList& list)
{
	string res;
	auto it = list.begin();

	while (it != list.end())
	{
		res += *it + " ";
		++it;
	}
	return res;
}


SCENARIO("Test base methods")
{
	CStringList list;

	WHEN("Test append Function")
	{
		list.Append("1");
		REQUIRE(list.GetSize() == 1);
		REQUIRE(list.GetBackElement() == "1");
		WHEN("Test append when list have any elements")
		{
			list.Append("2");
			REQUIRE(list.GetSize() == 2);
		}
	}
	WHEN("Test unshift function")
	{
		list.PushFront("1");
		REQUIRE(list.GetSize() == 1);
		REQUIRE(list.GetBackElement() == "1");
		WHEN("Test append when list have any elements")
		{
			list.PushFront("1");
			REQUIRE(list.GetSize() == 2);
		}
	}
	WHEN("Test Insert and Delete and Clear function")
	{
		list.Append("1");
		list.Append("2");
		list.Append("3");
		list.Append("4");
		REQUIRE(list.GetSize() == 4);
		REQUIRE(list.GetBackElement() == "4");

		auto insertIt = list.begin();
		insertIt++;
		insertIt++;
		
		list.Insert(insertIt, "5");
		REQUIRE(list.GetSize() == 5);
		REQUIRE(GetStringListValues(list) == "1 2 5 3 4 ");
		
		auto deleteIt = list.begin();
		++deleteIt;
		++deleteIt;
		++deleteIt;

		list.Delete(deleteIt);
		REQUIRE(list.GetSize() == 4);
		REQUIRE(GetStringListValues(list) == "1 2 5 4 ");

		list.Clear();
		REQUIRE(list.GetSize() == 0);
	}
	WHEN("Test Insert and Delete and Clear function")
	{
		list.Append("1");
		list.Append("2");
		list.Append("3");
		list.Append("4");
		REQUIRE(list.GetSize() == 4);
		REQUIRE(list.GetBackElement() == "4");

		auto insertIt = list.rbegin();
		++insertIt;
		++insertIt;

		list.Insert(insertIt, "5");
		REQUIRE(list.GetSize() == 5);
		REQUIRE(GetStringListValues(list) == "1 2 5 3 4 ");

		auto deleteIt = list.rbegin();
		++deleteIt;
		++deleteIt;
		++deleteIt;

		list.Delete(deleteIt);
		REQUIRE(list.GetSize() == 4);
		REQUIRE(GetStringListValues(list) == "1 2 3 4 ");

		list.Clear();
		REQUIRE(list.GetSize() == 0);
	}
}

SCENARIO("test iterators")
{
	CStringList list;
	list.Append("1");
	list.Append("2");
	list.Append("3");
	list.Append("4");

	WHEN("Test reverse iterators")
	{
		auto it = list.rbegin();
		auto itEnd = list.rend();
		string res;
		while (it != list.rend())
		{
			res += *it + ' ';
			++it;
		}
		REQUIRE(res == "4 3 2 1 ");
	}
}

SCENARIO("test constructor of move")
{
	CStringList list;
	list.Append("1");
	list.Append("2");
	list.Append("3");
	list.Append("4");

	CStringList list1;
	list1 = move(list);

	REQUIRE(list.GetSize() == 0);
	REQUIRE(list1.GetSize() == 4);
	REQUIRE(list1.GetBackElement() == "4");
}

SCENARIO("test constructor of copy")
{
	CStringList list;
	list.Append("1");
	list.Append("2");
	list.Append("3");
	list.Append("4");

	CStringList list1;
	list1 = list;

	REQUIRE(list.GetSize() == 4);
	REQUIRE(list.GetBackElement() == "4");

	REQUIRE(list1.GetSize() == 4);
	REQUIRE(list1.GetBackElement() == "4");
}