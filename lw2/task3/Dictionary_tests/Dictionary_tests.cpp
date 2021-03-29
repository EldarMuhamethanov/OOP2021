#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task3_1/Dictionary.h"

using namespace std;

SCENARIO("ReadDictionary of empty file gives empty dictionary")
{
	string dictionaryFileName = "empty_dictionary.txt";
	Error error;
	auto readedDictionary = ReadDictionary(dictionaryFileName, error);
	REQUIRE(readedDictionary);
	Dictionary dictionary = *readedDictionary;
	REQUIRE(dictionary.size() == 0);
}

SCENARIO("ReadDictionary of not empty file gives right dictionary")
{
	string dictionaryFileName = "not_empty_dictionary.txt";
	Error error;
	auto readedDictionary = ReadDictionary(dictionaryFileName, error);
	REQUIRE(readedDictionary);
	Dictionary dictionary = *readedDictionary;

	vector<string> greenTranslate = { "зеленый" };
	vector<string> orangeTranslate = { "оранжевый", "апельсин" };
	vector<string> theRedSquerTranslate = { "Красная площадь" };

	REQUIRE(GetTranslates(dictionary, "green") == greenTranslate);
	REQUIRE(GetTranslates(dictionary, "orange") == orangeTranslate);
	REQUIRE(GetTranslates(dictionary, "the red squer") == theRedSquerTranslate);
}

SCENARIO("AddWord to exist dictionary")
{
	Dictionary dictionary{
		{"green", {"зеленый"}},
	};
	AddWord(dictionary, "orange", "оранжевый");
	vector<string> orangeTranslate = { "оранжевый" };
	REQUIRE(GetTranslates(dictionary, "orange") == orangeTranslate);
}

SCENARIO("WriteTranslates of exist word in dictionary")
{
	Dictionary dictionary{
		{"orange", {"оранжевый", "апельсин"}},
	};
	ostringstream output("");
	WriteTranslates(output, GetTranslates(dictionary, "orange"));
	string resultString = "оранжевый, апельсин\n";
	REQUIRE(resultString == output.str());
}

SCENARIO("SaveDictionary then read it and compare with initial dictionary")
{
	Dictionary initialDictionary{
		{"orange", {"оранжевый", "апельсин"}},
		{"the red squer", {"красная площадь"}},
	};
	Error error;
	SaveDictionary("result_dictionary.txt", initialDictionary, error);
	REQUIRE(error.errorMessage == "");
	auto readedDictionary = ReadDictionary("result_dictionary.txt", error);
	Dictionary resultDictionary = *readedDictionary;
	REQUIRE(GetTranslates(resultDictionary, "orange") == GetTranslates(initialDictionary, "orange"));
	REQUIRE(GetTranslates(resultDictionary, "the red squer") == GetTranslates(initialDictionary, "the red squer"));
}


SCENARIO("HandleUnknownWord input empty string => ignore word")
{
	Dictionary dictionary;
	string testRequest = "HandleUnknownWord";
	istringstream input("");
	cin.rdbuf(input.rdbuf());
	HandleUnknownWord(dictionary, testRequest);
	REQUIRE(dictionary.size() == 0);
}

SCENARIO("HandleUnknownWord input not empty string => add new word to dictionary")
{
	Dictionary dictionary;
	string testRequest = "test word";
	istringstream input("test word translate");
	cin.rdbuf(input.rdbuf());
	vector<string> result = { "test word translate" };
	HandleUnknownWord(dictionary, testRequest);
	REQUIRE(GetTranslates(dictionary, "test word") == result);
}

SCENARIO("TranslateWord of not exist word")
{
	Dictionary dictionary{
		{"orange", {"оранжевый", "апельсин"}},
	};
	REQUIRE(!TranslateWord(dictionary, "green"));
}

