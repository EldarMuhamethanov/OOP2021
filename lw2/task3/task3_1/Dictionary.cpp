#include <iostream>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include "Dictionary.h"


const string EXIT_COMMAND = "...";

void WriteMessage(string msg)
{
    cout << msg << endl;
}

string TrimString(const string& str)
{
    regex trimRegex(R"(^(\s*)(.+?)(\s*)$)");
    smatch match;
    regex_search(str, match, trimRegex);
    return match[2];
}

vector<string> SplitString(const string& str, const string& separator)
{
    vector<string> resultVector;
    int currPosition = 0;
    int posOfSearched = str.find(separator);
    while (posOfSearched != string::npos)
    {
        string substr = str.substr(currPosition, posOfSearched - currPosition);
        resultVector.push_back(TrimString(substr));
        currPosition = posOfSearched + separator.length();
        posOfSearched = str.find(separator, currPosition);
    }
    resultVector.push_back(TrimString(str.substr(currPosition, str.length() - currPosition)));
    return resultVector;
}

optional<DictionaryItem> ParseDictionaryItem(const string& row, Error& error)
{
    error.errorMessage = "";
    DictionaryItem item;
    regex dictionaryItemRegex(R"((\[.+\])(.*))");
    smatch dictionaryItemMatch;

    if (regex_search(row, dictionaryItemMatch, dictionaryItemRegex))
    {
        string wordWithBrakets = dictionaryItemMatch[1];
        regex wordRegex(R"([A-Za-zА-Яа-я ]+)");
        smatch wordMatch;
        if (regex_search(wordWithBrakets, wordMatch, wordRegex))
        {
            item.word = TrimString(wordMatch[0]);
            item.translates = SplitString(dictionaryItemMatch[2], ",");
        }
        else
        {
            error.errorMessage = "Неверный формат заданной строки";
            return nullopt;
        }
    }
    else
    {
        error.errorMessage = "Неверный формат заданной строки";
        return nullopt;
    }

    return item;
}

optional<Dictionary> ReadDictionary(string const& dictionaryFileName, Error& error)
{
    error.errorMessage = "";
    ifstream dictionaryFile;
    dictionaryFile.open(dictionaryFileName);
    Dictionary dictionary;
    if (!dictionaryFile.is_open())
    {
        return dictionary;
    }

    string line;
    while (getline(dictionaryFile, line))
    {
        auto parsedItem = ParseDictionaryItem(line, error);
        if (!parsedItem)
        {
            return nullopt;
        }
        DictionaryItem item = *parsedItem;
        dictionary[item.word] = item.translates;
    }
    return dictionary;
}

void WriteTranslates(ostream& out, vector<string> const& translates)
{
    string result;
    for (unsigned int i = 0; i < translates.size(); i++)
    {
        result += translates[i];
        if (i < translates.size() - 1)
        {
            result += ", ";
        }
    }
    out << result << endl;
}

void SaveDictionary(string const& dictionaryFileName, Dictionary const& dictionary, Error& error)
{
    error.errorMessage = "";
    ofstream dictionaryFile;
    dictionaryFile.open(dictionaryFileName);
    if (!dictionaryFile.is_open())
    {
        error.errorMessage = "Failed to open dictionary file to save";
        return;
    }
    for (auto& dictionaryItem : dictionary)
    {
        dictionaryFile << "[" << dictionaryItem.first << "] ";
        vector<string> translates = dictionaryItem.second;
        WriteTranslates(dictionaryFile, translates);
    }
}

void AddWord(Dictionary& dictionary, string const& word, string const& translate)
{
    dictionary[word] = { translate };
}

vector<string> GetTranslates(Dictionary const& dictionary, string const& word)
{
    return dictionary.at(word);
}

bool TranslateWord(Dictionary const& dictionary, string const& word)
{
    if (dictionary.find(word) != dictionary.end())
    {
        WriteTranslates(cout, GetTranslates(dictionary, word));
        return true;
    }
    return false;
}

void HandleUnknownWord(Dictionary& dictionary, string const& userRequst)
{
    WriteMessage("Неизвестное слово \"" + userRequst + "\". Введите перевод или пустую строку для отказа.");
    string userAnswer;
    getline(cin, userAnswer);
    if (userAnswer.empty())
    {
        WriteMessage("Слово  \"" + userRequst + "\" проигнорировано.");
        return;
    }
    AddWord(dictionary, userRequst, userAnswer);
    WriteMessage("Слово \"" + userRequst + "\" сохранено в словаре как \"" + userAnswer + "\".");
    return;
}

void HandleRequest(Dictionary& dictionary, const string& userRequst)
{
    string userRequstInLower = userRequst;
    transform(userRequstInLower.begin(), userRequstInLower.end(), userRequstInLower.begin(), tolower);
    if (userRequstInLower.empty())
    {
        return;
    }
    if (!TranslateWord(dictionary, userRequstInLower))
    {
        HandleUnknownWord(dictionary, userRequst);
    }
}

void ExitDictionary(const Dictionary& dictionary, const string& dictionaryFileName, bool wasModified, Error& error)
{
    if (wasModified)
    {
        WriteMessage("В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.");
        string userAnswer;
        getline(cin, userAnswer);
        if (userAnswer == "Y" || userAnswer == "y")
        {
            SaveDictionary(dictionaryFileName, dictionary, error);
            if (!error.errorMessage.empty())
            {
                return;
            }
            WriteMessage("Изменения сохранены. До свидания.");
        }
    }
}

void DictionaryUse(const string& dictionaryFileName, Error& error)
{
    error.errorMessage = "";
    auto readedDictionary = ReadDictionary(dictionaryFileName, error);
    if (!readedDictionary)
    {
        return;
    }
    // readedDictionary исправить
    Dictionary dictionary = *readedDictionary;
    int startDictionarySize = dictionary.size();
    string userRequst;
    while (true)
    {
        getline(cin, userRequst);
        if (userRequst == EXIT_COMMAND)
        {
            break;
        }
        HandleRequest(dictionary, userRequst);
    }
    bool wasModified = dictionary.size() != startDictionarySize;
    ExitDictionary(dictionary, dictionaryFileName, wasModified, error);
}