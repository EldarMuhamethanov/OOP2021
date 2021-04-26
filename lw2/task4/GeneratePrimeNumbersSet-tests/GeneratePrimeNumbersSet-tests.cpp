#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task4/GeneratePrimeNumbersSet.h"

SCENARIO("GeneratePrimeNumbersSet with upperBound 12")
{
	std::set<int> primeSet = GeneratePrimeNumbersSet(12);
	REQUIRE(primeSet.find(3) != primeSet.end());
	REQUIRE(primeSet.find(7) != primeSet.end());
	REQUIRE(primeSet.find(11) != primeSet.end());
	REQUIRE(primeSet.size() == 5);
}

SCENARIO("GeneratePrimeNumbersSet with upperBound 10000")
{
	REQUIRE(GeneratePrimeNumbersSet(10000).size() == 1229);
}

SCENARIO("GeneratePrimeNumbersSet with upperBound 100000000")
{
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}
