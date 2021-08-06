#include <iostream>
#include "CMyArray.h"
#include <vector>

using namespace std;


void f()
{
	CMyArray<int> arr;

	arr.Append(1);
	arr.Append(2);
	arr.Append(3);
	arr.Resize(1);
	//arr[3] = 7;
	arr.Append(5);

	cout << "size: " << arr.GetSize() << endl;
	cout << "capacity: " << arr.GetCapacity() << endl;
	

	//arr.Resize(2);
	//arr.Append("10 11 12"s);

	for (size_t i = 0; i < arr.GetSize(); i++)
	{
		cout << arr[i] << endl;
	}

	arr.Clear();
	arr.Append(3);

	for (size_t i = 0; i < arr.GetSize(); i++)
	{
		cout << arr[i] << endl;
	}
	cout << "end" << endl;
}

int main()
{
	f();
	cout << "main end" << endl;
}