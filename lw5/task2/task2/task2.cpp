#include <iostream>
#include "CMyString.h"

using namespace std;

int main()
{
	CMyString s("string test1");
	auto it = s.begin();

	while (it != s.end())
	{
		cout << *it << endl;
		it += 1;
	}

	//auto it1 = s.rbegin();

	//while (it1 != s.rend())
	//{
	//	cout << *it1 << endl;
	//	++it1;
	//}

	auto it3 = s.begin();

	it3 += 10;

	auto it4 = s.begin();

	it4 += 5;

	cout << it4 - it3 << endl;

	return 0;
}