#include <iostream>
#include "CStringList.h"

using namespace std;

int main()
{
    CStringList list;
    list.Append("1");
    list.Append("2");
    list.Append("3");
    list.Append("4");
    auto it = list.begin();
    while (it != list.end())
    {
        cout << *it << endl;
        it++;
    }

    CStringList list1;
    list1.Append("1");
    list1.Append("2");
    list1.Append("3");
    list1.Append("4");

    auto it1 = list1.rbegin();
    auto itEnd = list1.rend();
    while (it1 != itEnd)
    {
        cout << *it1 << endl;
        it1++;
    }
}