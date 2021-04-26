#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "Car.h"
#include "RemoteCarControl.h"


using namespace std;


int main()
{
	Car car;
	RemoteCarControl remoteControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		remoteControl.HandleCommand();
	}
	return 0;
}