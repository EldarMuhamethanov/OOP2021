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
#include <set>

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    set<int> primeSet;
    vector<bool> arr;
    arr.push_back(true);
    for (int i = 1; i <= upperBound; i++)
    {
        arr.push_back(true);
    }
    int i = 2;
    while (i * i <= upperBound)
    {
        int j = i;
        if (arr[j])
        {
            int prime = j;
            primeSet.insert(prime);
            j *= j;
            while (j <= upperBound)
            {
                arr[j] = false;
                j = j + prime;
            }
        }
        i++;
    }
    while (i <= upperBound)
    {
        if (arr[i])
        {
            primeSet.insert(i);
        }
        i++;
    }
    return primeSet;
}

int main()
{
    set<int> primeSet = GeneratePrimeNumbersSet(1000000);
    for (auto& prime: primeSet)
    {
        cout << prime << endl;
    }
    cout << "Size " << primeSet.size() << endl;
}
