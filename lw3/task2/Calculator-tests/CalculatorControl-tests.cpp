#include "../../../Catch2/catch.hpp"
#include "../task2/CalculatorControl.h"
#include <sstream>

using namespace std;

SCENARIO("test init var")
{
	Calculator calculator;

	WHEN("init var a and check value")
	{
		istringstream in("var a");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(calculatorControl.HandleCommand());
		REQUIRE(isnan(calculator.GetVarValue("a")));
	}
	WHEN("init exist var")
	{
		istringstream in("var a");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		calculator.AddVar("a");
		REQUIRE(!calculatorControl.HandleCommand());
		REQUIRE(out.str() == "Ошибка: Переменная или функция с именем \"a\" уже существует\n");
	}
	WHEN("input is not correct")
	{
		istringstream in("var a=12");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(!calculatorControl.HandleCommand());
		REQUIRE(out.str() == "Неверный формат входной строки\n");
	}
}

SCENARIO("test set var")
{
	Calculator calculator;
	WHEN("init var with value")
	{
		istringstream in("let a=10");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(calculatorControl.HandleCommand());
		REQUIRE(calculator.GetVarValue("a") == 10);
	}
	WHEN("init var with incorrect input")
	{
		istringstream in("let a");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(!calculatorControl.HandleCommand());
		REQUIRE(out.str() == "Неверный формат входной строки\n");
	}
	WHEN("init var with incorrect var name")
	{
		istringstream in("let 1a=12");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(!calculatorControl.HandleCommand());
		REQUIRE(out.str() == "Ошибка: Невалидное название переменной\n");
	}
}

SCENARIO("test init function")
{
	Calculator calculator;
	WHEN("init function with two operands")
	{
		istringstream in("fn f=2+2");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(calculatorControl.HandleCommand());
		REQUIRE(calculator.CalculateFunction("f") == 4);
	}
	WHEN("init function with one operand")
	{
		istringstream in("fn f=2");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(calculatorControl.HandleCommand());
		REQUIRE(calculator.CalculateFunction("f") == 2);
	}
	WHEN("init function with existed name")
	{
		calculator.AddVar("f");
		istringstream in("fn f=2");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(!calculatorControl.HandleCommand());
		REQUIRE(out.str() == "Ошибка: Переменная или функция с именем \"f\" уже существует\n");
	}
	WHEN("init function with incorrect input")
	{
		istringstream in("fn f");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(!calculatorControl.HandleCommand());
		REQUIRE(out.str() == "Неверный формат введенной строки\n");
	}
}

SCENARIO("test PrintIdentificator")
{
	Calculator calculator;
	WHEN("print var id")
	{
		calculator.SetVar("a", 5);
		istringstream in("print a");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(calculatorControl.HandleCommand());
		REQUIRE(out.str() == "5.00\n");
	}
	WHEN("print function id")
	{
		calculator.AddFunction("f", []() -> double {
			return 1.00;
		});
		istringstream in("print f");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(calculatorControl.HandleCommand());
		REQUIRE(out.str() == "1.00\n");
	}
	WHEN("Print unknown id")
	{
		istringstream in("print f");
		ostringstream out("");
		CalculatorControl calculatorControl(calculator, in, out);
		REQUIRE(!calculatorControl.HandleCommand());
		REQUIRE(out.str() == "Ошибка: Идентификатора с именеи \"f\" не существует\n");
	}
}

SCENARIO("test print vars")
{
	Calculator calculator;
	calculator.AddFunction("f1", []() -> double {
		return 1.00;
	});
	calculator.AddFunction("f2", []() -> double {
		return 2.00;
	});
	calculator.AddFunction("f3", []() -> double {
		return 3.00;
	});
	istringstream in("printfns");
	ostringstream out("");
	CalculatorControl calculatorControl(calculator, in, out);
	REQUIRE(calculatorControl.HandleCommand());
	REQUIRE(out.str() == "f1:1.00\nf2:2.00\nf3:3.00\n");
}

SCENARIO("test print functions")
{
	Calculator calculator;
	calculator.SetVar("a", 1);
	calculator.SetVar("b", 2);
	calculator.SetVar("c", 3);
	istringstream in("printvars");
	ostringstream out("");
	CalculatorControl calculatorControl(calculator, in, out);
	REQUIRE(calculatorControl.HandleCommand());
	REQUIRE(out.str() == "a:1.00\nb:2.00\nc:3.00\n");
}

SCENARIO("test unknown command")
{
	Calculator calculator;
	istringstream in("unknown");
	ostringstream out("");
	CalculatorControl calculatorControl(calculator, in, out);
	REQUIRE(!calculatorControl.HandleCommand());
	REQUIRE(out.str() == "Неизвестная команда\n");
}