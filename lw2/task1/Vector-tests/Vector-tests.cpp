#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task1/Vector.h"

using namespace std;

SCENARIO("ReadVector from stream gives right vector")
{
	string input = "123 524.425 98.1  9895.5";
	istringstream strm(input);
	vector<double> inputVector = ReadVector(strm);
	vector<double> resultVector = {123, 524.425, 98.1, 9895.5};
	REQUIRE(resultVector == inputVector);
}

SCENARIO("DivideByMaximum")
{
	vector<double> inputVector = { 50, 75, 100, 80 };
	vector<double> resultVector = { 1.000, 1.500, 2.000, 1.600 };
	REQUIRE(DivideByHalfMaximum(inputVector) == resultVector);
}

SCENARIO("WriteVector to output")
{
	string result = "98.100 123.000 524.425 9895.500";
	ostringstream strm("");
	vector<double> vector = { 123, 524.425, 98.1, 9895.5 };
	PrintVectorAscending(strm, vector);
	REQUIRE(strm.str() == result);
}