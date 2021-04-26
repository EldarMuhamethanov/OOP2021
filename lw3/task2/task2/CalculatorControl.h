#pragma once
#include "Calculator.h"

class CalculatorControl
{
public:
	CalculatorControl(Calculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand() const;

private:
	bool InitVar(std::istream& args) const;
	bool SetVar(std::istream& args) const;
	bool InitFunction(std::istream& args) const;
	bool PrintIdentificator(std::istream& args) const;
	bool PrintVars(std::istream&) const;
	bool PrintFunctions(std::istream&) const;
	void ExceptionHandler(CalculatorException const& exception) const;
	void PrintValue(double value) const;
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
	
};

