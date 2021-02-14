#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>


using namespace std;

const short MATRIX_SIZE = 3;

typedef double Matrix3x3[MATRIX_SIZE][MATRIX_SIZE];
typedef double Matrix2x2[2][2];

struct Args
{
    string inputFileName;
};

struct WrappedMatrix3x3
{
    Matrix3x3 items;
};

struct WrappedMatrix2x2
{
    Matrix2x2 items;
};

WrappedMatrix3x3 MatrixInit(ifstream& in, bool& error);
void WriteMatrix(WrappedMatrix3x3 matrix);
string Readline(ifstream& in);
WrappedMatrix3x3 FindInvertMatrix(WrappedMatrix3x3 matrix, bool& error);
WrappedMatrix2x2 GetMinor(WrappedMatrix3x3 matrix, int column, int row);
double CalculateDeterminant2x2(WrappedMatrix2x2 matrix);
double CalculateDeterminant3x3(WrappedMatrix3x3 matrix);
WrappedMatrix3x3 TransposeMatrix(WrappedMatrix3x3 matrix);
WrappedMatrix3x3 GetMatrixKoef(WrappedMatrix3x3 matrix);
WrappedMatrix3x3 MatrixDivision(WrappedMatrix3x3 matrix, double number);
bool IsDigits(const string& str);
bool IsBlankLine(string str);


optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: task3.exe <matrix file1>\n";
        return nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    return args;
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);

    auto args = ParseArgs(argc, argv);

    ifstream in;

    if (!args)
    {
        return 1;
    }
    in.open(args->inputFileName);
    if (!in.is_open())
    {
        cout << "Failed to open " << args->inputFileName << " to reading" << endl;
        return 1;
    }

    bool error = false;
    WrappedMatrix3x3 matrix = MatrixInit(in, error);
    if (error)
    {
        cout << "Failed to read initial matrix" << endl;
        return 1;
    }

    WrappedMatrix3x3 invertMatrix = FindInvertMatrix(matrix, error);
    if (error)
    {
        cout << "non-degenerate matrix" << endl;
        return 1;
    }

    WriteMatrix(invertMatrix);
    return 0;
}

WrappedMatrix3x3 FindInvertMatrix(WrappedMatrix3x3 matrix, bool& error)
{
    double determinant = CalculateDeterminant3x3(matrix);

    if (determinant == 0)
    {
        error = true;
        return {};
    }

    WrappedMatrix3x3 transposedMatrix = TransposeMatrix(matrix);
    WrappedMatrix3x3 koefMatrix = GetMatrixKoef(transposedMatrix);
    WrappedMatrix3x3 invertMatrix = MatrixDivision(koefMatrix, determinant);

    return invertMatrix;
}


WrappedMatrix3x3 GetMatrixKoef(WrappedMatrix3x3 matrix)
{
    WrappedMatrix3x3 koefMatrix;
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            koefMatrix.items[row][column] = CalculateDeterminant2x2(GetMinor(matrix, column, row));
            if ((row + column) % 2 != 0)
            {
                koefMatrix.items[row][column] *= -1;
            }
        }
    }
    return koefMatrix;
}

WrappedMatrix3x3 MatrixDivision(WrappedMatrix3x3 matrix, double number)
{
    WrappedMatrix3x3 resultMatrix;
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            double value = matrix.items[row][column];
            resultMatrix.items[row][column] = round(value / number * 1000) / 1000;
        }
    }
    return resultMatrix;
}

WrappedMatrix3x3 TransposeMatrix(WrappedMatrix3x3 matrix)
{
    WrappedMatrix3x3 transposedMatrix;
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            transposedMatrix.items[row][column] = matrix.items[column][row];
        }
    }
    return transposedMatrix;
}

double CalculateDeterminant2x2(WrappedMatrix2x2 matrix)
{
    return (matrix.items[0][0] * matrix.items[1][1]) - (matrix.items[0][1] * matrix.items[1][0]);
}

double CalculateDeterminant3x3(WrappedMatrix3x3 matrix)
{
    return matrix.items[0][0] * CalculateDeterminant2x2(GetMinor(matrix, 0, 0))
        - matrix.items[0][1] * CalculateDeterminant2x2(GetMinor(matrix, 1, 0))
        + matrix.items[0][2] * CalculateDeterminant2x2(GetMinor(matrix, 2, 0));
}

WrappedMatrix2x2 GetMinor(WrappedMatrix3x3 matrix, int column, int row)
{
    vector<int> minorRow;
    vector<int> minorColumn;

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        if (row != i)
        {
            minorRow.push_back(i);
        }
        if (column != i)
        {
            minorColumn.push_back(i);
        }
    }
    return {
        {
        {matrix.items[minorRow[0]][minorColumn[0]], matrix.items[minorRow[0]][minorColumn[1]]},
        {matrix.items[minorRow[1]][minorColumn[0]], matrix.items[minorRow[1]][minorColumn[1]]},
        },
    };
}

WrappedMatrix3x3 MatrixInit(ifstream& in, bool& error)
{
    WrappedMatrix3x3 defaultMatrix;
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        if (in.eof())
        {
            error = true;
            return {};
        }
        string rowLine = Readline(in);
        if (IsBlankLine(rowLine))
        {
            error = true;
            return {};
        }
        istringstream strm(rowLine);
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            string numberString;
            if (strm.eof())
            {
                error = true;
                return {};
            }
            strm >> numberString;
            double number;
            if (!IsDigits(numberString))
            {
                error = true;
                return {};
            }
            number = stod(numberString);
            defaultMatrix.items[row][column] = number;
        }
    }
    return defaultMatrix;
}

void WriteMatrix(WrappedMatrix3x3 matrix)
{
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            if (column != MATRIX_SIZE - 1)
            {
                printf("%4.3f ", matrix.items[row][column]);
            }
            else
            {
                printf("%4.3f", matrix.items[row][column]);
            }
        }
        cout << endl;
    }
}

string Readline(ifstream& in)
{
    string str;
    getline(in, str);
    return str;
}

bool IsDigits(const string& str)
{
    if (str[0] == '-')
    {
        string value = str.substr(1);
        return all_of(value.begin(), value.end(), ::isdigit);
    }
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

bool IsSpace(char ch)
{
    return ch == ' ';
}

bool IsBlankLine(string str)
{
    return str.empty() || all_of(str.begin(), str.end(), IsSpace);
}