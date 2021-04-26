#include <iostream>
#include "Calculator.h"
#include "CalculatorControl.h"

using namespace std;

int main()
{
	Calculator calculator;
	CalculatorControl calculatorControl(calculator, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		calculatorControl.HandleCommand();
	}
	return 0;
}