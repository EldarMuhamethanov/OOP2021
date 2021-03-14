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

typedef map<string, vector<string>> Vocabulary;

struct Error
{
    string errorMessage;
};

struct Args
{
    string vocabularyFileName;
};

struct VocabularyItem
{
    string word;
    vector<string> translates;
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

optional<VocabularyItem> parseVocabularyItem(string row, Error& error)
{
    error.errorMessage = "";
    VocabularyItem item;
    regex vocabularyItemRegex(R"((\[.+\])(.+))");
    regex wordRegex(R"([^\s\[]+[A-Za-zА-Яа-я ]+[^\s\]])");
    regex translateRegex(R"([^(\s+,)][A-Za-zА-Яа-я ]+)");

    smatch vocabularyItemMatch;
    smatch wordMatch;
    smatch translateMatch;

    if (regex_search(row, vocabularyItemMatch, vocabularyItemRegex))
    {
        string wordWithBrakets = vocabularyItemMatch[1];
        if (regex_search(wordWithBrakets, wordMatch, wordRegex))
        {
            item.word = wordMatch[0];
            item.translates = {};
            string translates = vocabularyItemMatch[2];
            while (regex_search(translates, translateMatch, translateRegex))
            {
                item.translates.push_back(translateMatch[0]);
                translates = translateMatch.suffix();
            }
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

optional<Vocabulary> ReadVocabulary(string vocabularyFileName, Error& error)
{
    error.errorMessage = "";
    ifstream vocabularyFile;
    vocabularyFile.open(vocabularyFileName);
    Vocabulary vocabulary;
    if (!vocabularyFile.is_open())
    {
        return vocabulary;
    }

    string line;
    while (getline(vocabularyFile, line))
    {
        auto parsedItem = parseVocabularyItem(line, error);
        if (!parsedItem)
        {
            return nullopt;
        }
        VocabularyItem item = *parsedItem;
        vocabulary[item.word] = item.translates;
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

void SaveVocabulary(string vocabularyFileName, Vocabulary vocabulary, Error& error)
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
    Vocabulary vocabulary = *readedVocabulary;
    string userRequst;
    bool wasModified = false;
    getline(cin, userRequst);
    while (userRequst != "...")
    {
        string userRequstInLower = userRequst;
        transform(userRequstInLower.begin(), userRequstInLower.end(), userRequstInLower.begin(), tolower);
        if (userRequstInLower.empty())
        {
            getline(cin, userRequst);
            continue;
        }
        if (vocabulary.find(userRequstInLower) != vocabulary.end())
        {
            WriteTranslates(cout, vocabulary[userRequstInLower]);
        }
        else
        {
            cout << "Неизвестное слово \"" + userRequst + "\". Введите перевод или пустую строку для отказа." << endl;
            string userAnswer;
            getline(cin, userAnswer);
            if (userAnswer.empty())
            {
                cout << "Слово  \"" + userRequst + "\" проигнорировано." << endl;
            }
            else if (userAnswer != "...")
            {
                wasModified = true;
                if (vocabulary.find(userAnswer) != vocabulary.end())
                {
                    vocabulary[userAnswer].push_back(userRequst);
                    cout << "Слово \"" + userRequst + "\" добавлено в список переводов слова \"" + userAnswer + "\"." << endl;
                }
                else
                {
                    vocabulary[userRequstInLower] = { userAnswer };
                    cout << "Слово \"" + userRequst + "\" сохранено в словаре как \"" + userAnswer + "\"." << endl;
                }
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
        cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;
        string userAnswer;
        getline(cin, userAnswer);
        if (userAnswer == "Y" || userAnswer == "y")
        {
            SaveVocabulary(vocabularyFileName, vocabulary, error);
            cout << "Изменения сохранены. До свидания." << endl;
        }
    }
}