#include <iostream>
#include "Calculator.h"

using namespace std;

void Calculator::AddVar(const string& name, optional<double> value)
{
	if (Calculator::CheckExistName(name))
	{
		throw CalculatorException("Переменная или функция с таким именем уже существует");
	}
	m_varsMap[name] = value;
}

void Calculator::AddFunction(const string& name, FunctionCallback callback)
{
	if (Calculator::CheckExistName(name))
	{
		throw CalculatorException("Переменная или функция с таким именем уже существует");
	}
	m_fnMap[name] = callback;
}

optional<double> Calculator::GetVarValue(const string& name) const
{
	if (!Calculator::CheckExistName(name))
	{
		throw CalculatorException("Переменная с таким именем не существует");
	}
	return m_varsMap.at(name);
}

optional<double> Calculator::CalculateFunction(const string& name) const
{
	if (!Calculator::CheckExistName(name))
	{
		throw CalculatorException("Функция с таким именем не существует");
	}
	function<optional<double>()> callback = m_fnMap.at(name);
	optional<double> result = callback();
	return result;
}

void Calculator::PrintFunction(ostream& out, const string& fnName) const
{
	auto result = CalculateFunction(fnName);
	string resultString = result ? to_string(*result) : "nan";
	out << fixed << setprecision(2) << fnName << ":" << resultString << endl;
}

void Calculator::PrintVar(ostream& out, const string& varName) const
{
	auto value = GetVarValue(varName);
	string valueString = value	? to_string(*value)	: "nan" ;
	out << fixed << setprecision(2) << varName << ":" << valueString << endl;
}

void Calculator::PrintFunctions(ostream& out) const
{
	for (auto& fn : m_fnMap)
	{
		string fnName = fn.first;
		auto result = CalculateFunction(fnName);
		string resultString = result ? to_string(*result) : "nan";
		out << fixed << setprecision(2) << fnName << ":" << resultString << endl;
	}
}

void Calculator::PrintVars(ostream& out) const
{
	for (auto& var : m_varsMap)
	{
		string varName = var.first;
		auto value = GetVarValue(varName);
		string valueString = value ? to_string(*value) : "nan";
		out << fixed << setprecision(2) << varName << ":" << valueString << endl;
	}
}

bool Calculator::CheckExistName(string const& name) const
{
	if (m_fnMap.find(name) != m_fnMap.end() || m_varsMap.find(name) != m_varsMap.end())
	{
		return true;
	}
}