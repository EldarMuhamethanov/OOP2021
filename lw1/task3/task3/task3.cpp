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

const short MATRIX_SIZE = 3;

typedef double Matrix3x3[MATRIX_SIZE][MATRIX_SIZE];
typedef double Matrix2x2[2][2];

struct Error
{
    string errorMessage;
};

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

optional<WrappedMatrix3x3> MatrixInit(const string& inputFileName, Error& error);
void WriteMatrix(const WrappedMatrix3x3 matrix);
optional<WrappedMatrix3x3> FindInvertMatrix(const WrappedMatrix3x3 matrix, Error& error);
WrappedMatrix2x2 GetMinor(const WrappedMatrix3x3 matrix, int column, int row);
double CalculateDeterminant2x2(const WrappedMatrix2x2 matrix);
double CalculateDeterminant3x3(const WrappedMatrix3x3 matrix);
WrappedMatrix3x3 TransposeMatrix(const WrappedMatrix3x3 matrix);
WrappedMatrix3x3 GetMatrixKoef(const WrappedMatrix3x3 matrix);
WrappedMatrix3x3 MatrixDivision(const WrappedMatrix3x3 matrix, const  double number);
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
    Error error;
    auto matrix = MatrixInit(args->inputFileName, error);
    if (!matrix)
    {
        cout << error.errorMessage << endl;
        return 1;
    }

    auto invertMatrix = FindInvertMatrix(*matrix, error);
    if (!invertMatrix)
    {
        cout << error.errorMessage << endl;
        return 1;
    }

    WriteMatrix(*invertMatrix);
    return 0;
}

optional<WrappedMatrix3x3> FindInvertMatrix(const WrappedMatrix3x3 matrix, Error& error)
{
    error.errorMessage = "";
    double determinant = CalculateDeterminant3x3(matrix);

    if (determinant == 0)
    {
        error.errorMessage = "Determinant = 0 -> matrix - non degenerade";
        return nullopt;
    }

    WrappedMatrix3x3 transposedMatrix = TransposeMatrix(matrix);
    WrappedMatrix3x3 koefMatrix = GetMatrixKoef(transposedMatrix);
    WrappedMatrix3x3 invertMatrix = MatrixDivision(koefMatrix, determinant);

    return invertMatrix;
}


WrappedMatrix3x3 GetMatrixKoef(const WrappedMatrix3x3 matrix)
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

WrappedMatrix3x3 MatrixDivision(const WrappedMatrix3x3 matrix, const double divisor)
{
    WrappedMatrix3x3 resultMatrix;
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            double value = matrix.items[row][column];
            resultMatrix.items[row][column] = value / divisor;
        }
    }
    return resultMatrix;
}

WrappedMatrix3x3 TransposeMatrix(const WrappedMatrix3x3 matrix)
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

double CalculateDeterminant2x2(const WrappedMatrix2x2 matrix)
{
    return (matrix.items[0][0] * matrix.items[1][1]) - (matrix.items[0][1] * matrix.items[1][0]);
}

double CalculateDeterminant3x3(const WrappedMatrix3x3 matrix)
{
    return matrix.items[0][0] * CalculateDeterminant2x2(GetMinor(matrix, 0, 0))
        - matrix.items[0][1] * CalculateDeterminant2x2(GetMinor(matrix, 1, 0))
        + matrix.items[0][2] * CalculateDeterminant2x2(GetMinor(matrix, 2, 0));
}

WrappedMatrix2x2 GetMinor(const WrappedMatrix3x3 matrix, int column, int row)
{
    int minorRow[2];
    int minorColumn[2];

    int minorIndexRow = 0;
    int minorIndexColumn = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        if (row != i && minorIndexRow < 2)
        {
            minorRow[minorIndexRow] = i;
            minorIndexRow++;
        }
        if (column != i && minorIndexColumn < 2)
        {
            minorColumn[minorIndexColumn] = i;
            minorIndexColumn++;
        }
    }
    return {
        {
            {matrix.items[minorRow[0]][minorColumn[0]], matrix.items[minorRow[0]][minorColumn[1]]},
            {matrix.items[minorRow[1]][minorColumn[0]], matrix.items[minorRow[1]][minorColumn[1]]},
        },
    };
}

optional<WrappedMatrix3x3> MatrixInit(const string& inputFileName, Error& error)
{
    error.errorMessage = "";
    ifstream in;
    in.open(inputFileName);
    if (!in.is_open())
    {
        error.errorMessage = "Failed to open " + inputFileName + " to reading";
        return nullopt;
    }
    
    WrappedMatrix3x3 matrix;
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        string rowLine;
        if (getline(in, rowLine) && IsBlankLine(rowLine))
        {
            error.errorMessage = "Blank line or file eof find";
            return nullopt;
        }
        istringstream strm(rowLine);
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            string columnValue;
            if (strm.eof())
            {
                error.errorMessage = "Invalid count of elements";
                return nullopt;
            }
            strm >> columnValue;
            matrix.items[row][column] = stod(columnValue);
        }
    }
    return matrix;
}

void WriteMatrix(const WrappedMatrix3x3 matrix)
{
    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            cout << fixed << setprecision(3) << matrix.items[row][column];
            if (column != MATRIX_SIZE - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

bool IsSpace(char ch)
{
    return ch == ' ';
}

bool IsBlankLine(string str)
{
    return str.empty() || all_of(str.begin(), str.end(), IsSpace);
}