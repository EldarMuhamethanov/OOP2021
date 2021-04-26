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
#include <set>
#include "GeneratePrimeNumbersSet.h"

using namespace std;

struct Args 
{
    int number;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: task4.exe <number>\n";
        return nullopt;
    }
    Args args;
    args.number = stoi(argv[1]);
    return args;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    set<int> primeSet = GeneratePrimeNumbersSet(args->number);
    cout << primeSet.size() << endl;
}
