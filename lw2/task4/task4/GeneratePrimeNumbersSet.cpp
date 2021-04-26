#include <set>
#include <vector>
#include "GeneratePrimeNumbersSet.h"

using namespace std;

set<int> GeneratePrimeNumbersSet(const int upperBound)
{
    vector<bool>isPrime(upperBound + 1, true);
    vector<int>primeNumbers;
    vector<int>smallestPrimeFactor(upperBound + 1);

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= upperBound; i++)
    {
        if (isPrime[i])
        {
            primeNumbers.push_back(i);
            smallestPrimeFactor[i] = i;
        }

        for (int j = 0;
            j < (int)primeNumbers.size() &&
            i * primeNumbers[j] <= upperBound && primeNumbers[j] <= smallestPrimeFactor[i];
            j++)
        {
            isPrime[i * primeNumbers[j]] = false;
            smallestPrimeFactor[i * primeNumbers[j]] = primeNumbers[j];
        }
    }
    set<int> primeSet;
    for (int number : primeNumbers)
    {
        primeSet.insert(number);
    }
    return primeSet;
}