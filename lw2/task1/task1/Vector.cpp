#include <algorithm>
#include <istream>
#include <istream>
#include <vector>
#include <string>
#include <regex>
#include <iomanip>

using namespace std;

vector<double> ReadVector(istream& in)
{
    string line;
    getline(in, line);

    vector<double> numbersVector;
    regex numberRegex(R"([0-9]+[.,]?[0-9]*)");
    auto numbers_begin = sregex_iterator(line.begin(), line.end(), numberRegex);
    auto numbers_end = sregex_iterator();

    for (sregex_iterator i = numbers_begin; i != numbers_end; ++i) {
        smatch match = *i;
        double number = stod(match.str());
        numbersVector.push_back(number);
    }
    return numbersVector;
}

vector<double> DivideByHalfMaximum(vector<double> const& numbers)
{
    double maxElement = *max_element(numbers.begin(), numbers.end());
    vector<double> resultNumbers = numbers;
    transform(resultNumbers.begin(), resultNumbers.end(), resultNumbers.begin(), 
        [maxElement](double num) -> double {
            return (num / (maxElement / 2));
        });
    return resultNumbers;
}

void PrintVectorAscending(ostream& out, vector<double>& vector)
{
    sort(vector.begin(), vector.end());
    for (unsigned int i = 0; i < vector.size(); i++)
    {
        out << fixed << setprecision(3) << vector[i];
        if (i != vector.size() - 1)
        {
            out << " ";
        }
    }
}