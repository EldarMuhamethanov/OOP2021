#pragma once
#include <string>
#include <vector>
#include <optional>
#include <map>

using namespace std;

typedef map<string, vector<string>> Dictionary;

struct Error
{
    string errorMessage;
};

struct DictionaryItem
{
    string word;
    vector<string> translates;
};

optional<Dictionary> ReadDictionary(string const& dictionaryFileName, Error& error);
void WriteTranslates(ostream& out, vector<string> const& translates);
void SaveDictionary(string const& dictionaryFileName, Dictionary const& dictionary, Error& error);
void AddWord(Dictionary& dictionary, string const& word, string const& translate);
vector<string> GetTranslates(Dictionary const& dictionary, string const& word);
bool TranslateWord(Dictionary const& dictionary, string const& word);
void DictionaryUse(string const& dictionaryFileName, Error& error);
void HandleUnknownWord(Dictionary& dictionary, string const& userRequst);
