#include <iostream>
#include "BodiesContainer.h"

using namespace std;

int main()
{
	BodiesContainer bodiesContainer(cin, cout);
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		bodiesContainer.HandleCommand();
	}
	return 0;
}
