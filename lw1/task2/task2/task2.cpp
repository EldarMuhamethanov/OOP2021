#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <optional>

using namespace std;

struct Error
{
    string errorMessage;
};

struct Args
{
    int sourceNotation;
    int destinationNotation;
    string value;
};

optional<string> RadixConvert(const string& value, int sourceNotation, int destinationNotation, Error& error);
optional<long long> StringToInt(const string& str, int radix, Error& error);
int ConvertCharToInt(const char& ch);
string IntToString(long long n, int radix);
char ConvertIntToChar(long long& num);
bool IsDigits(const string& str);


optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: task2.exe <sourceNotation> <destinationNotation> <value>\n";
        return nullopt;
    }

    string initialSourceNotation = argv[1];
    string initialDestinationNotation = argv[2];
    string value = argv[3];

    int sourceNotation;
    int destinationNotation;

    if (IsDigits(initialSourceNotation) && IsDigits(initialDestinationNotation))
    {
        sourceNotation = stoi(initialSourceNotation);
        destinationNotation = stoi(initialDestinationNotation);
        if (sourceNotation < 2 || sourceNotation > 36)
        {
            cout << "Invalid source notation entered\n";
            return nullopt;
        }
        if (destinationNotation < 2 || destinationNotation > 36)
        {
            cout << "Invalid destination notation entered\n";
            return nullopt;
        }
    }
    else
    {
        cout << "Notations are set incorrectly\n";
        return nullopt;
    }

    Args args;
    args.sourceNotation = sourceNotation;
    args.destinationNotation = destinationNotation;
    args.value = value;

    return args;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    int sourceNotation = args->sourceNotation;
    int destinationNotation = args->destinationNotation;
    string value = args->value;

    Error error;

    auto result = RadixConvert(value, sourceNotation, destinationNotation, error);

    if (!result)
    {
        cout << error.errorMessage;
        return 1;
    }

    cout << *result << endl;
    return 0;
}

optional<string> RadixConvert(const string& value, int sourceNotation, int destinationNotation, Error& error)
{
    error.errorMessage = "";
    string initialValue = value;
    if (initialValue.empty())
    {
        error.errorMessage = "value is empty";
        return nullopt;
    }
    auto decimalValue = StringToInt(initialValue, sourceNotation, error);
    if (!decimalValue)
    {
        return nullopt;
    }
    string resultValue = IntToString(*decimalValue, destinationNotation);
    return resultValue;
}

string IntToString(long long n, int radix)
{
    string reverseResult;
    long long dividend = n;
    while (abs(dividend) >= radix)
    {
        long long modOfDeletion = abs(dividend) % radix;
        reverseResult += ConvertIntToChar(modOfDeletion);
        dividend = dividend / radix;
    }
    dividend = abs(dividend);
    reverseResult += ConvertIntToChar(dividend);
    reverse(reverseResult.begin(), reverseResult.end());
    return n < 0 ? '-' + reverseResult : reverseResult;
}

optional<long long> StringToInt(const string& str, int radix, Error& error)
{
    error.errorMessage = "";
    long long res = 0;
    string value = str;
    bool isNegative = false;
    if (str[0] == '-')
    {
        isNegative = true;
        value = str.substr(1);
    }
    for (int i = 0; i < value.length(); i++)
    {
        res *= radix;
        if (!((value[i] >= '0' && value[i] <= '9') || (value[i] >= 'A' && value[i] <= 'Z')))
        {
            error.errorMessage = "invalid character was found";
            return nullopt;
        }
        long long num = ConvertCharToInt(value[i]);
        if (num >= radix)
        {
            error.errorMessage = "The original value contains a character that is outside the limit of notation";
            return nullopt;
        }
        res += num;
        if (res > MAXINT)
        {
            error.errorMessage = "Overflow";
            return nullopt;
        }
    }
    return isNegative ? -res : res;
}

int ConvertCharToInt(const char& ch)
{
    if (ch <= '9' && ch >= '0')
    {
        return (int)ch - 48;
    }
    return 10 + ch - 'A';
}

char ConvertIntToChar(long long& num)
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