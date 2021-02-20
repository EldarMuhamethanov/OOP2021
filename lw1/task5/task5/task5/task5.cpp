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

using namespace std;

const int MATRIX_SIZE = 100;

typedef char Matrix[MATRIX_SIZE][MATRIX_SIZE];

struct Args
{
    string inputFileName;
    string outputFileName;
};

struct WrappedMatrix
{
    Matrix items;
};

WrappedMatrix ReadField(istream& in);
void WriteField(ostream& out, WrappedMatrix field);
void FillField(WrappedMatrix& field);
void MatchCell(WrappedMatrix& field, int row, int column);

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: fill.exe <input file> <output file>\n";
        return nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    ifstream in;
    ofstream out;
    in.open(args->inputFileName);

    if (!in.is_open())
    {
        cout << "Failed to open " << args->inputFileName << " for reading" << endl;
        return 1;
    }
    out.open(args->outputFileName);

    if (!out.is_open())
    {
        cout << "Failed to open " << args->outputFileName << " for writing" << endl;
        return 1;
    }

    WrappedMatrix field = ReadField(in);

    FillField(field);

    WriteField(out, field);

    return 0;
}

void MatchCell(WrappedMatrix& field, int row, int column)
{
    
    if (field.items[row][column] == ' ')
    {
        field.items[row][column] = '.';
        if (row < MATRIX_SIZE - 1)
        {
            MatchCell(field, row + 1, column);
        }
        if (row > 0)
        {
            MatchCell(field, row - 1, column);
        }
        if (column < MATRIX_SIZE - 1)
        {
            MatchCell(field, row, column + 1);
        }
        if (column > 0)
        {
            MatchCell(field, row, column - 1);
        }
    }
}

void FillField(WrappedMatrix& field)
{
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            if (field.items[row][column] == 'O')
            {
                MatchCell(field, row + 1, column);
                MatchCell(field, row - 1, column);
                MatchCell(field, row, column + 1);
                MatchCell(field, row, column - 1);
            }
        }
    }
}

WrappedMatrix ReadField(istream& in)
{
    string line;
    WrappedMatrix field;

    for (int lineIndex = 0; lineIndex < MATRIX_SIZE; lineIndex++)
    {
        if (getline(in, line))
        {
            for (int symbolIndex = 0; symbolIndex < MATRIX_SIZE; symbolIndex++)
            {
                field.items[lineIndex][symbolIndex] = symbolIndex < line.length()
                    ? line[symbolIndex]
                    : ' ';
            }
        }
        else
        {
            for (int symbolIndex = 0; symbolIndex < MATRIX_SIZE; symbolIndex++)
            {
                field.items[lineIndex][symbolIndex] = ' ';
            }
        }
    }
    return field;
}

void WriteField(ostream& out, WrappedMatrix field)
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            out << field.items[i][j];
        }
        out << endl;
    }
}