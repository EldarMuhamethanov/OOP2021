#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <iomanip>
#include <map>
#include <regex>

using namespace std;

struct Error
{
    string errorMessage;
};

struct Args
{
    string vocabularyFileName;
};

void VocabularyUse(string vocabularyFileName, Error& error);

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: vocabuary.exe <vocabulary file>\n";
        return nullopt;
    }
    Args args;
    args.vocabularyFileName = argv[1];
    return args;
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    Error error;

    VocabularyUse(args->vocabularyFileName, error);

    if (!error.errorMessage.empty())
    {
        cout << error.errorMessage << endl;
    }

    return 0;
}

optional<map<string, vector<string>>> ReadVocabulary(string vocabularyFileName, Error& error)
{
    error.errorMessage = "";
    ifstream vocabularyFile;
    vocabularyFile.open(vocabularyFileName);
    if (!vocabularyFile.is_open())
    {
        error.errorMessage = "Failed to open vocabulary file to read";
        return nullopt;
    }
    map<string, vector<string>> vocabulary;
    string line;
    while (getline(vocabularyFile, line))
    {
        string word;
        regex wordRegex("[\\s\\w]+");
        regex wordWithBraketRegex(R"(\[(\w|\s)+\])");
        
        smatch wordWithBraketMatch;
        regex_search(line, wordWithBraketMatch, wordWithBraketRegex);
        smatch wordMatch;
        string wordWithBraket = wordWithBraketMatch[0];
        regex_search(wordWithBraket, wordMatch, wordRegex);

        word = wordMatch[0];
        vocabulary[word] = {};

        string translates = wordWithBraketMatch.suffix();

        regex translateRegex(R"([^\s].+[^,])");
        smatch translateMatch;
        int posOfSeparator = translates.find(',');
        while (posOfSeparator != string::npos)
        {
            string translate = translates.substr(0, posOfSeparator);
            regex_search(translate, translateMatch, translateRegex);
            translate = translateMatch[0];
            vocabulary[word].push_back(translate);
            translates = translates.substr(posOfSeparator + 1);
            posOfSeparator = translates.find(',');
        }
        regex_search(translates, translateMatch, translateRegex);
        vocabulary[word].push_back(translateMatch[0]);
    }
    return vocabulary;
}

void WriteTranslates(ostream& out, vector<string> translates)
{
    string result;
    for (int i = 0; i < translates.size(); i++)
    {
        result += translates[i];
        if (i < translates.size() - 1)
        {
            result += ", ";
        }
    }
    out << result << endl;
}

void SaveVocabulary(string vocabularyFileName, map<string, vector<string>> vocabulary, Error& error)
{
    error.errorMessage = "";
    ofstream vocabularyFile;
    vocabularyFile.open(vocabularyFileName);
    if (!vocabularyFile.is_open())
    {
        error.errorMessage = "Failed to open vocabulary file to save";
    }
    for (auto& vocabularyItem : vocabulary)
    {
        vocabularyFile << "[" << vocabularyItem.first << "] ";
        vector<string> translates = vocabularyItem.second;
        WriteTranslates(vocabularyFile, translates);
    }
}

void VocabularyUse(string vocabularyFileName, Error& error)
{
    error.errorMessage = "";
    auto readedVocabulary = ReadVocabulary(vocabularyFileName, error);
    if (!readedVocabulary)
    {
        return;
    }
    map<string, vector<string>> vocabulary = *readedVocabulary;
    string userRequst;
    bool wasModified = false;
    getline(cin, userRequst);
    while (userRequst != "...")
    {
        string userRequstInLower = userRequst;
        transform(userRequstInLower.begin(), userRequstInLower.end(), userRequstInLower.begin(), tolower);
        if (vocabulary.find(userRequstInLower) != vocabulary.end())
        {
            WriteTranslates(cout, vocabulary[userRequstInLower]);
        }
        else
        {
            cout << "Unknown word \"" + userRequst + "\". Enter a translation or an empty line to refuse." << endl;
            string userAnswer;
            getline(cin, userAnswer);
            if (userAnswer.empty())
            {
                cout << "Word \"" + userRequst + "\" ignored." << endl;
            }
            else if (userAnswer != "...")
            {
                vocabulary[userRequstInLower] = { userAnswer };
                wasModified = true;
                cout << "Word \"" + userRequst + "\" saved in the dictionary as \"" + userAnswer + "\"." << endl;
            }
            else
            {
                break;
            }
        }
        getline(cin, userRequst);
    }
    if (wasModified)
    {
        cout << "Changes have been made to the dictionary. Enter Y or y to save before exiting." << endl;
        string userAnswer;
        getline(cin, userAnswer);
        if (userAnswer == "Y" || userAnswer == "y")
        {
            SaveVocabulary(vocabularyFileName, vocabulary, error);
            cout << "Changes saved. Goodbye." << endl;
        }
    }
}