#include <iostream>
#include "Dictionary.h"

using namespace std;

struct Args
{
    string dictionaryFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: vocabuary.exe <dictionary file>\n";
        return nullopt;
    }
    Args args;
    args.dictionaryFileName = argv[1];
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

    DictionaryUse(args->dictionaryFileName, error);

    if (!error.errorMessage.empty())
    {
        cout << error.errorMessage << endl;
    }

    return 0;
}
