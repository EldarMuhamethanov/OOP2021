#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <optional>

using namespace std;

struct Args
{
    string sourceNotation;
    string destinationNotation;
    string value;
};

string RadixConvert(string value, int sourceNotation, int destinationNotation, bool& wasError);
long long StringToInt(const string& str, int radix, bool& wasError);
int ConvertCharToInt(char ch);
string IntToString(long long n, int radix, bool& wasError);
char ConvertIntToChar(long long num);
bool IsDigits(const string& str);
bool CheckValidNumber(const string& value, int radix);


optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: task2.exe <sourceNotation> <destinationNotation> <value>\n";
        return nullopt;
    }
    Args args;
    args.sourceNotation = argv[1];
    args.destinationNotation = argv[2];
    args.value = argv[3];
    return args;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    string sourceNotation = args->sourceNotation;
    string destinationNotation = args->destinationNotation;
    string value = args->value;

    int sourceNotationInt;
    int destinationNotationInt;

    if (IsDigits(sourceNotation) && IsDigits(destinationNotation))
    {
        sourceNotationInt = stoi(sourceNotation);
        destinationNotationInt = stoi(destinationNotation);
        if (sourceNotationInt < 2 || sourceNotationInt > 36)
        {
            cout << "Invalid source notation entered\n";
            return 1;
        }
        if (destinationNotationInt < 2 || destinationNotationInt > 36)
        {
            cout << "Invalid destination notation entered\n";
            return 1;
        }
    }
    else
    {
        cout << "Notations are set incorrectly\n";
        return 1;
    }

    bool error = false;

    string result = RadixConvert(value, sourceNotationInt, destinationNotationInt, error);

    if (error)
    {
        cout << "Failed to convert value\n";
        return 1;
    }

    cout << result << endl;
    return 0;
}

string RadixConvert(string value, int sourceNotation, int destinationNotation, bool& wasError)
{
    string initialValue = value;
    bool isNegative = false;
    if (value[0] == '-')
    {
        isNegative = true;
        initialValue = value.substr(1);
    }
    long long decimalValue = StringToInt(move(initialValue), sourceNotation, wasError);
    if (wasError)
    {
        cout << "Failed to convert Value to decimal notation";
        return "";
    }
    string resultValue = IntToString(decimalValue, destinationNotation, wasError);
    if (wasError)
    {
        cout << "Failed to convert Value to destination notation";
        return "";
    }
    return isNegative ? '-' + resultValue : resultValue;
}

string IntToString(long long n, int radix, bool& wasError)
{
    string reverseResult;
    long long dividend = n;
    while (dividend >= radix)
    {
        long long modOfDeletion = dividend % radix;
        reverseResult += ConvertIntToChar(modOfDeletion);
        dividend = dividend / radix;
    }
    reverseResult += ConvertIntToChar(dividend);
    reverse(reverseResult.begin(), reverseResult.end());
    return reverseResult;
}

long long StringToInt(const string& str, int radix, bool& wasError)
{
    int valueLength = str.length();
    long long res = 0;
    for (int i = 0; i < valueLength; i++)
    {
        if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z')))
        {
            wasError = true;
            return 0;
        }
        long num = ConvertCharToInt(str[i]);
        if (num >= radix)
        {
            wasError = true;
            return 0;
        }
        int power = valueLength - (i + 1);
        res += num * pow(radix, power);
    }
    return res;
}

int ConvertCharToInt(char ch)
{
    if (ch <= '9' && ch >= '0')
    {
        return (int)ch - 48;
    }
    return 10 + ch - 'A';
}

char ConvertIntToChar(long long num)
{
    if (num <= 9)
    {
        return (num + '0');
    }
    return 'A' + (num - 10);
}

bool IsDigits(const string& str)
{
    if (str[0] == '-')
    {
        string value = str.substr(1);
        return all_of(value.begin(), value.end(), ::isdigit);
    }
    return all_of(str.begin(), str.end(), ::isdigit);
}