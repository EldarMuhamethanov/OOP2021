#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../lw5/CRational.h"

using namespace std;

SCENARIO("Tests constructor")
{
	WHEN("Use constructor without params")
	{
		CRational rational;
		REQUIRE(rational.GetNumerator() == 0);
		REQUIRE(rational.GetDenominator() == 1);
	}
	WHEN("Use constructor with one param")
	{
		CRational rational(5);
		REQUIRE(rational.GetNumerator() == 5);
		REQUIRE(rational.GetDenominator() == 1);
	}
	WHEN("Use constructor with two params")
	{
		CRational rational(5, 3);
		REQUIRE(rational.GetNumerator() == 5);
		REQUIRE(rational.GetDenominator() == 3);
	}
	WHEN("Use constructor with two params and denominator is negative")
	{
		CRational rational(5, -3);
		REQUIRE(rational.GetNumerator() == -5);
		REQUIRE(rational.GetDenominator() == 3);
	}
	WHEN("Use constructor with two params and both params is negative")
	{
		CRational rational(-5, -3);
		REQUIRE(rational.GetNumerator() == 5);
		REQUIRE(rational.GetDenominator() == 3);
	}
	WHEN("12")
	{
		try
		{
			CRational rational(-5, 0);
			assert(false);
		}
		catch (const invalid_argument&)
		{
		}
	}
}

SCENARIO("Test operators")
{
	WHEN("Operator unary +")
	{
		CRational rational(-2, 3);
		CRational res = +rational;
		REQUIRE(res.GetNumerator() == -2);
		REQUIRE(res.GetDenominator() == 3);
	}
	WHEN("Operator unary -")
	{
		CRational rational(2, 3);
		CRational res = -rational;
		REQUIRE(res.GetNumerator() == -2);
		REQUIRE(res.GetDenominator() == 3);
	}
	WHEN("Operator unary - in denominator")
	{
		CRational rational(2, -3);
		CRational res = -rational;
		REQUIRE(res.GetNumerator() == 2);
		REQUIRE(res.GetDenominator() == 3);
	}

	WHEN("Operator += Rational")
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		r1 += r2;
		REQUIRE(r1.GetNumerator() == 2);
		REQUIRE(r1.GetDenominator() == 3);
	}
	WHEN("Operator += int")
	{
		CRational r1(1, 2);
		r1 += 1;
		REQUIRE(r1.GetNumerator() == 3);
		REQUIRE(r1.GetDenominator() == 2);
	}

	WHEN("Operator -= Rational")
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		r1 -= r2;
		REQUIRE(r1.GetNumerator() == 1);
		REQUIRE(r1.GetDenominator() == 3);
	}
	WHEN("Operator -= int")
	{
		CRational r1(1, 2);
		r1 -= 1;
		REQUIRE(r1.GetNumerator() == -1);
		REQUIRE(r1.GetDenominator() == 2);
	}

	WHEN("Operator +(rational and rational)")
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		CRational res = r1 + r2;
		REQUIRE(res.GetNumerator() == 2);
		REQUIRE(res.GetDenominator() == 3);
	}
	WHEN("Operator +(rational and int)")
	{
		CRational r1(1, 2);
		CRational res = r1 + 1;
		REQUIRE(res.GetNumerator() == 3);
		REQUIRE(res.GetDenominator() == 2);
	}
	WHEN("Operator +(rational and rational)")
	{
		CRational r2(1, 2);
		CRational res = 1 + r2;
		REQUIRE(res.GetNumerator() == 3);
		REQUIRE(res.GetDenominator() == 2);
	}

	WHEN("Operator -(rational and rational)")
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		CRational res = r1 - r2;
		REQUIRE(res.GetNumerator() == 1);
		REQUIRE(res.GetDenominator() == 3);
	}
	WHEN("Operator -(rational and int)")
	{
		CRational r1(1, 2);
		CRational res = r1 - 1;
		REQUIRE(res.GetNumerator() == -1);
		REQUIRE(res.GetDenominator() == 2);
	}
	WHEN("Operator -(rational and rational)")
	{
		CRational r2(1, 2);
		CRational res = 1 - r2;
		REQUIRE(res.GetNumerator() == 1);
		REQUIRE(res.GetDenominator() == 2);
	}

	WHEN("Operator *= Rational")
	{
		CRational r1(1, 2);
		CRational r2(2, 3);
		r1 *= r2;
		REQUIRE(r1.GetNumerator() == 1);
		REQUIRE(r1.GetDenominator() == 3);
	}
	WHEN("Operator *= int")
	{
		CRational r1(1, 2);
		r1 *= 3;
		REQUIRE(r1.GetNumerator() == 3);
		REQUIRE(r1.GetDenominator() == 2);
	}

	WHEN("Operator /= Rational")
	{
		CRational r1(1, 2);
		CRational r2(2, 3);
		r1 /= r2;
		REQUIRE(r1.GetNumerator() == 3);
		REQUIRE(r1.GetDenominator() == 4);
	}
	WHEN("Operator /= Rational 2")
	{
		CRational r1(3, 4);
		CRational r2(3, 8);
		r1 /= r2;
		REQUIRE(r1.GetNumerator() == 2);
		REQUIRE(r1.GetDenominator() == 1);
	}
	WHEN("Operator /= int")
	{
		CRational r1(1, 2);
		r1 /= 3;
		REQUIRE(r1.GetNumerator() == 1);
		REQUIRE(r1.GetDenominator() == 6);
	}


	WHEN("Operator *(rational and rational)")
	{
		CRational r1(1, 2);
		CRational r2(2, 3);
		CRational res = r1 * r2;
		REQUIRE(res.GetNumerator() == 1);
		REQUIRE(res.GetDenominator() == 3);
	}
	WHEN("Operator *(rational and int)")
	{
		CRational r1(1, 2);
		CRational res = r1 * (-3);
		REQUIRE(res.GetNumerator() == -3);
		REQUIRE(res.GetDenominator() == 2);
	}
	WHEN("Operator *(rational and rational)")
	{
		CRational r2(2, 3);
		CRational res = 7 * r2;
		REQUIRE(res.GetNumerator() == 14);
		REQUIRE(res.GetDenominator() == 3);
	}


	WHEN("Operator /(rational and rational)")
	{
		CRational r1(1, 2);
		CRational r2(2, 3);
		CRational res = r1 / r2;
		REQUIRE(res.GetNumerator() == 3);
		REQUIRE(res.GetDenominator() == 4);
	}
	WHEN("Operator /(rational and int)")
	{
		CRational r1(1, 2);
		CRational res = r1 / 5;
		REQUIRE(res.GetNumerator() == 1);
		REQUIRE(res.GetDenominator() == 10);
	}
	WHEN("Operator /(rational and rational)")
	{
		CRational r2(2, 3);
		CRational res = 7 / r2;
		REQUIRE(res.GetNumerator() == 21);
		REQUIRE(res.GetDenominator() == 2);
	}

	WHEN("Operator == and !=")
	{
		CRational r1(1, 2);
		CRational r2(1, 2);
		REQUIRE(r1 == r2);

		CRational r3(1, 2);
		CRational r4(1, 3);
		REQUIRE(r3 != r4);

		CRational r5(1, 2);
		REQUIRE(r5 != 2);
	}

	WHEN("Opeartors <, <=, >, >=")
	{
		CRational r1(1, 2);
		CRational r2(1, 3);
		REQUIRE(r1 > r2);

		CRational r3(1, 2);
		CRational r4(1, 3);
		REQUIRE(!(r3 <= r4));

		CRational r5(1, 2);
		REQUIRE(r5 < 7);

		CRational r6(7, 2);
		bool b = 3 < r6;
		REQUIRE(3 < r6);
	}


	WHEN("Operators << #1")
	{
		CRational r1(-7, 15);
		ostringstream strm("");
		strm << r1;
		REQUIRE(strm.str() == "-7/15");
	}
	WHEN("Operators << #2")
	{
		CRational r1(7, 1);
		ostringstream strm("");
		strm << r1;
		REQUIRE(strm.str() == "7");
	}

	WHEN("Operator >> #1")
	{
		CRational r1;
		istringstream strm("7/15");
		strm >> r1;
		REQUIRE(r1.GetNumerator() == 7);
		REQUIRE(r1.GetDenominator() == 15);
	}
	WHEN("Operator >> #2")
	{
		CRational r1;
		istringstream strm("7");
		strm >> r1;
		REQUIRE(r1.GetNumerator() == 7);
		REQUIRE(r1.GetDenominator() == 1);
	}
}

SCENARIO("Test ToCompoundFraction")
{
	CRational initialRational(5, 2);
	pair<int, CRational> res = initialRational.ToCompoundFraction();
	REQUIRE(res.first == 2);
	REQUIRE(res.second.GetNumerator() == 1);
	REQUIRE(res.second.GetDenominator() == 2);
}

SCENARIO("Test some operations")
{
	CRational r1(1, 6);
	CRational r2(5, 21);
	CRational r3(15, 9);
	CRational r4(1, 4);
	CRational r5(9, 13);
	CRational res = r1 + r2 - r3 * r4 / r5;
	REQUIRE(res.GetNumerator() == -149);
	REQUIRE(res.GetDenominator() == 756);
}

SCENARIO("ToDouble test")
{
	CRational r(3, 2);
	double res = r.ToDouble();
	REQUIRE(res == 1.5);
}