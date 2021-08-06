#include <iostream>
#include "CMyArray.h"
#include <vector>

using namespace std;

int main()
{
    CMyArray<double> arr(2);
    
    arr[0] = 2.1;
    arr[1] = 3.4;

    arr.Push(4.5);

    arr.Resize(5);

    arr[3] = 5.6;
    arr[4] = 6.7;

    arr.Push(7.8);

    auto it = arr.begin();

    while (it != arr.end())
    {
        cout << *it << endl;
        it += 2;
    }
}
