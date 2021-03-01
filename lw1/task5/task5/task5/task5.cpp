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
#include <stack>

using namespace std;

const int MATRIX_SIZE = 100;

typedef char Matrix[MATRIX_SIZE][MATRIX_SIZE];

struct Args
{
    string inputFileName;
    string outputFileName;
};

struct WrappedField
{
    Matrix items;
};

struct CellCoordinate
{
    int x;
    int y;
};

struct Error
{
    string errorMessage;
};

optional<WrappedField> ReadField(const string& inputFileName, Error& error);
void WriteField(const string& outputFileName, const WrappedField& field, Error& error);
void FillField(WrappedField& field);
void AddToStackNeighborCells(const WrappedField& field, stack<CellCoordinate>& stack, int row, int column);
void FillCell(WrappedField& field, stack<CellCoordinate>& stack, int row, int column);

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

    Error error;

    auto field = ReadField(args->inputFileName, error);

    if (!field && !error.errorMessage.empty())
    {
        cout << error.errorMessage << endl;
        return 1;
    }

    FillField(*field);

    WriteField(args->outputFileName, *field, error);

    if (!error.errorMessage.empty())
    {
        cout << error.errorMessage << endl;
        return 1;
    }

    return 0;
}

void FillCell(WrappedField& field, stack<CellCoordinate>& stack, int row, int column)
{
    while (!stack.empty())
    {
        CellCoordinate cell = stack.top();
        stack.pop();
        field.items[cell.y][cell.x] = '.';
        AddToStackNeighborCells(field, stack, cell.y, cell.x);
    }
}

void AddToStackNeighborCells(const WrappedField& field, stack<CellCoordinate>& stack, int row, int column)
{
    CellCoordinate cell;
    if (row < MATRIX_SIZE - 1 && field.items[row + 1][column] == ' ')
    {
        cell.x = column;
        cell.y = row + 1;
        stack.push(cell);
    }
    if (row > 0 && field.items[row - 1][column] == ' ')
    {
        cell.x = column;
        cell.y = row - 1;
        stack.push(cell);
    }
    if (column < MATRIX_SIZE - 1 && field.items[row][column + 1] == ' ')
    {
        cell.x = column + 1;
        cell.y = row;
        stack.push(cell);
    }
    if (column > 0 && field.items[row][column - 1] == ' ')
    {
        cell.x = column - 1;
        cell.y = row;
        stack.push(cell);
    }
}

void FillField(WrappedField& field)
{
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            if (field.items[row][column] == 'O')
            {
                stack<CellCoordinate> stack;
                AddToStackNeighborCells(field, stack, row, column);
                FillCell(field, stack, row, column);
            }
        }
    }
}

optional<WrappedField> ReadField(const string& inputFileName, Error& error)
{
    ifstream in;
    in.open(inputFileName);
    error.errorMessage = "";
    if (!in.is_open())
    {
        error.errorMessage = "Failed to open " + inputFileName + " for reading";
        return nullopt;
    }
    string line;
    WrappedField field;

    for (int lineIndex = 0; lineIndex < MATRIX_SIZE; lineIndex++)
    {
        if (getline(in, line))
        {
            for (int symbolIndex = 0; symbolIndex < MATRIX_SIZE; symbolIndex++)
            {
                field.items[lineIndex][symbolIndex] = symbolIndex < (int)line.length()
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

void WriteField(const string& outputFileName, const WrappedField& field, Error& error)
{
    ofstream out;
    out.open(outputFileName);
    error.errorMessage = "";
    if (!out.is_open())
    {
        cout << "Failed to open " << outputFileName << " for writing" << endl;
        return;
    }

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            out << field.items[i][j];
        }
        out << endl;
    }
}