#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <optional>
#include <iomanip>
#include "CalculatorException.h"

enum Operand {
	Plus,
	Minus,
	Div,
	Mult,
	None,
};

struct FunctionValue
{
	std::vector<std::string> numbers;
	Operand operand;
};

typedef std::function<std::optional<double>()> FunctionCallback;

class Calculator
{
public:
	Calculator();

	void AddVar(const std::string& name, std::optional<double> value);

	void AddFunction(const std::string& name, FunctionCallback callback);

	std::optional<double> GetVarValue(const std::string& name) const;

	std::optional<double> CalculateFunction(const std::string& name) const;

	void PrintVar(std::ostream& out, const std::string& varName) const;

	void PrintFunction(std::ostream& out, const std::string& fnName) const;

	void PrintVars(std::ostream& out) const;

	void PrintFunctions(std::ostream& out) const;

private:
	std::map<std::string, std::optional<double>> m_varsMap;
	std::map<std::string, FunctionCallback> m_fnMap;

	bool CheckExistName(const std::string& name) const;
};

