#include <iostream>
#include "Calculator.h"
#include <regex>

using namespace std;

Calculator::Calculator()
{
}

void Calculator::AddVar(const string& name)
{
	if (CheckExistName(name))
		throw CalculatorException("Переменная или функция с именем \"" + name + "\" уже существует");
	if (!CheckValidName(name))
		throw CalculatorException("Невалидное название переменной");
	m_varsMap[name] = NAN;
}

void Calculator::SetVar(const string& name, double value)
{
	if (!CheckValidName(name))
		throw CalculatorException("Невалидное название переменной");
	m_varsMap[name] = value;
}

FunctionCallback Calculator::CreateBinaryFunctionCallback(const string& operand1, const string& operand2, Action sign) const
{
	if (!(CheckValidName(operand1) && CheckExistName(operand1)) && !CheckIsDoubleValue(operand1))
		throw CalculatorException("Операнд \"" + operand1 + "\" некорректный");
	if (!(CheckValidName(operand2) && CheckExistName(operand2)) && !CheckIsDoubleValue(operand2))
		throw CalculatorException("Операнд \"" + operand2 + "\" некорректный");

	FunctionCallback callback = [this, operand1, operand2, sign]() -> double {
		double value1;
		double value2;
		try {
			value1 = GetExpressionValue(operand1);
			value2 = GetExpressionValue(operand2);
		}
		catch (const CalculatorException& exception)
		{
			throw exception;
		}
		if (!isnan(value1) && !isnan(value2))
		{
			switch (sign)
			{
				case Action::Plus:
					return value1 + value2;
				case Action::Sub:
					return value1 - value2;
				case Action::Div:
					return value1 / value2;
				case Action::Mult:
					return value1 * value2;
				default:
					return NAN;
			}
		}
		return NAN;
	};
	return callback;
}

FunctionCallback Calculator::CreateUnaryFunctionCallback(const string& operand) const
{
	if (!(CheckValidName(operand) && CheckExistName(operand)) && !CheckIsDoubleValue(operand))
		throw CalculatorException("Операнд \"" + operand + "\" некорректный");
	FunctionCallback callback = [this, operand]() -> double {
		try {
			return GetExpressionValue(operand);
		}
		catch (const CalculatorException& exception)
		{
			throw exception;
		}
	};
	return callback;
}

void Calculator::AddFunction(const string& name, FunctionCallback callback)
{
	if (CheckExistName(name))
		throw CalculatorException("Переменная или функция с именем \"" + name + "\" уже существует");
	if (!CheckValidName(name))
		throw CalculatorException("Невалидное название функции");
	m_fnMap[name] = callback;
}

double Calculator::GetVarValue(const string& name) const
{
	if (!CheckExistVarName(name))
		throw CalculatorException("Переменная с именем \"" + name + "\" не существует");
	return m_varsMap.at(name);
}

double Calculator::CalculateFunction(const string& name) const
{
	if (!CheckExistFunctionName(name))
		throw CalculatorException("Функция с именем \"" + name + "\" не существует");

	try {
		double result = GetFuntionValue(name);
		m_calculatedFnMap.clear();
		return result;
	}
	catch (CalculatorException const& exception) {
		throw exception;
	}
}

double Calculator::GetFuntionValue(const string& name) const
{
	double value;
	if (m_calculatedFnMap.find(name) != m_calculatedFnMap.end())
	{
		value = m_calculatedFnMap.at(name);
	}
	else
	{
		FunctionCallback callback = m_fnMap.at(name);
		try {
			value = callback();
		}
		catch (CalculatorException const& exception) {
			throw exception;
		}
		m_calculatedFnMap[name] = value;
	}
	return value;
}

map<string, FunctionCallback> Calculator::GetFunctionsMap() const
{
	return m_fnMap;
}

map<string, double> Calculator::GetVarsMap() const
{
	return m_varsMap;
}

bool Calculator::CheckExistName(const string& name) const
{
	return CheckExistVarName(name) || CheckExistFunctionName(name);
}

bool Calculator::CheckExistVarName(const string& name) const
{
	return (m_varsMap.find(name) != m_varsMap.end());
}

bool Calculator::CheckExistFunctionName(const string& name) const
{
	return (m_fnMap.find(name) != m_fnMap.end());
}

bool Calculator::CheckValidName(const string& name) const
{
	regex validNameRegex(R"(^[A-z_]\w*)");
	return regex_match(name, validNameRegex);
}

bool Calculator::CheckIsDoubleValue(const string& expression) const
{
	regex doubleValueRegex(R"(^\d+\.?\d*?$)");
	return regex_match(expression, doubleValueRegex);
}

double Calculator::GetExpressionValue(const string& expression) const
{
	if (CheckValidName(expression))
	{
		if (CheckExistVarName(expression))
			return GetVarValue(expression);
		else if (CheckExistFunctionName(expression))
			return GetFuntionValue(expression);
	}
	if (CheckIsDoubleValue(expression))
	{
		return stod(expression);
	}
	throw CalculatorException("Неверное задано значение выражения \"" + expression + "\"");
}