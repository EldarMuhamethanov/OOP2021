#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task2/Calculator.h"

using namespace std;

SCENARIO("Test AddVar and GetVarValue function")
{
	Calculator calculator;
	WHEN("add valid var")
	{
		calculator.AddVar("a");
		REQUIRE(isnan(calculator.GetVarValue("a")));
	}
	WHEN("add invalid var")
	{
		REQUIRE_THROWS(calculator.AddVar("1abc"));
	}
	WHEN("add two var with same names")
	{
		calculator.AddVar("a");
		REQUIRE_THROWS(calculator.AddVar("a"));
	}
	WHEN("get not exist var value")
	{
		REQUIRE_THROWS(calculator.GetVarValue("a"));
	}
}

SCENARIO("test setVar function")
{
	Calculator calculator;
	WHEN("add valid var then set value")
	{
		calculator.AddVar("a");
		calculator.SetVar("a", 1.23);
		REQUIRE(calculator.GetVarValue("a") == 1.23);
	}
	WHEN("add new var with value")
	{
		calculator.SetVar("a", 1.23);
		REQUIRE(calculator.GetVarValue("a") == 1.23);
	}
	WHEN("add new var with invalid name")
	{
		REQUIRE_THROWS(calculator.SetVar("1a", 1.23));
	}
}

SCENARIO("Test AddFunction, CreateFunctionCallback and CalculateFunction function")
{
	Calculator calculator;
	

	WHEN("create valid function and calculate it")
	{
		calculator.SetVar("a", 5);
		calculator.SetVar("b", 15);
		FunctionCallback callback = calculator.CreateBinaryFunctionCallback("a", "b", Action::Plus);
		calculator.AddFunction("f", callback);
		REQUIRE(calculator.CalculateFunction("f") == 20);
	}
	WHEN("add function with exist name")
	{
		calculator.SetVar("f", 5);
		calculator.SetVar("a", 15);
		calculator.SetVar("b", 15);
		FunctionCallback callback = calculator.CreateBinaryFunctionCallback("a", "b", Action::Plus);
		REQUIRE_THROWS(calculator.AddFunction("f", callback));
	}
	WHEN("add function with exist name")
	{
		calculator.SetVar("a", 5);
		calculator.SetVar("b", 15);
		FunctionCallback callback = calculator.CreateBinaryFunctionCallback("a", "b", Action::Plus);
		REQUIRE_THROWS(calculator.AddFunction("1f", callback));
	}
	WHEN("try to calculate not exist function")
	{
		REQUIRE_THROWS(calculator.CalculateFunction("f"));
	}
	WHEN("create callback with minus")
	{
		calculator.SetVar("a", 5);
		calculator.SetVar("b", 15);
		calculator.AddFunction("f", calculator.CreateBinaryFunctionCallback("a", "b", Action::Sub));
		REQUIRE(calculator.CalculateFunction("f") == -10);
	}
	WHEN("create callback with mult")
	{
		calculator.SetVar("a", 5);
		calculator.SetVar("b", 15);
		calculator.AddFunction("f", calculator.CreateBinaryFunctionCallback("a", "b", Action::Mult));
		REQUIRE(calculator.CalculateFunction("f") == 75);
	}
	WHEN("create callback with div")
	{
		calculator.SetVar("a", 15);
		calculator.SetVar("b", 5);
		calculator.AddFunction("f", calculator.CreateBinaryFunctionCallback("a", "b", Action::Div));
		REQUIRE(calculator.CalculateFunction("f") == 3);
	}
	WHEN("create callback with one operand")
	{
		calculator.SetVar("a", 15);
		calculator.AddFunction("f", calculator.CreateUnaryFunctionCallback("a"));
		REQUIRE(calculator.CalculateFunction("f") == 15);
	}
	WHEN("create callback with one operand with value NAN")
	{
		calculator.AddVar("a");
		calculator.SetVar("b", 15);
		calculator.AddFunction("f", calculator.CreateBinaryFunctionCallback("a", "b", Action::Plus));
		REQUIRE(isnan(calculator.CalculateFunction("f")));
		calculator.SetVar("a", 5);
		REQUIRE(calculator.CalculateFunction("f") == 20);
	}
	WHEN("create callback with one operand is function and another is double value")
	{
		calculator.SetVar("a", 15);
		calculator.SetVar("b", 15);
		calculator.AddFunction("f1", calculator.CreateBinaryFunctionCallback("a", "b", Action::Plus));
		calculator.AddFunction("f2", calculator.CreateBinaryFunctionCallback("f1", "2.12", Action::Plus));
		REQUIRE(calculator.CalculateFunction("f2") == 32.12);
	}
	WHEN("create callback with incorrect operand")
	{
		REQUIRE_THROWS(calculator.CreateBinaryFunctionCallback("a", "1.1aq", Action::None));
	}
}