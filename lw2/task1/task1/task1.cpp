#include <iostream>
#include <vector>
#include "Vector.h"

using namespace std;

int main()
{
    vector<double> numbers = ReadVector(cin);
    vector<double> resultNumbers = DivideByHalfMaximum(numbers);
    PrintVectorAscending(cout, resultNumbers);
}
