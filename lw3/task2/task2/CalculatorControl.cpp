#include <sstream>
#include "CalculatorControl.h"
#include <regex>

using namespace std;
using namespace std::placeholders;


CalculatorControl::CalculatorControl(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "var", bind(&CalculatorControl::InitVar, this, _1) },
		  { "let", bind(&CalculatorControl::SetVar, this, _1) },
		  { "fn", bind(&CalculatorControl::InitFunction, this, _1) },
		  { "print", bind(&CalculatorControl::PrintIdentificator, this, _1) },
		  { "printvars", bind(&CalculatorControl::PrintVars, this, _1) },
		  { "printfns", bind(&CalculatorControl::PrintFunctions, this, _1) },
		})
{
}

bool CalculatorControl::HandleCommand() const
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	m_output << "Неизвестная команда" << endl;
	return false;
}

bool CalculatorControl::InitVar(istream& args) const
{
	string value;
	args >> value;

	regex expressionRegex(R"(^\w+$)");
	smatch expressionMatch;
	if (regex_search(value, expressionMatch, expressionRegex))
	{
		try {
			m_calculator.AddVar(expressionMatch[0]);
			return true;
		}
		catch (CalculatorException const& exception) {
			ExceptionHandler(exception);
			return false;
		}
	}
	m_output << "Неверный формат входной строки" << endl;
	return false;
}

bool CalculatorControl::SetVar(istream& args) const
{
	string expression;
	args >> expression;
	regex expressionRegex(R"(^(\w+)(\s*=\s*)([\w\.]+)$)");
	smatch expressionMatch;
	if (regex_search(expression, expressionMatch, expressionRegex))
	{
		string varName = expressionMatch[1];
		try {
			double varValue = m_calculator.GetExpressionValue(expressionMatch[3]);
			m_calculator.SetVar(varName, varValue);
			return true;
		}
		catch (CalculatorException const& exception) {
			ExceptionHandler(exception);
			return false;
		}
	}
	m_output << "Неверный формат входной строки" << endl;
	return false;
}

bool CalculatorControl::InitFunction(istream& args) const
{
	string expression;
	args >> expression;
	regex functionExpressionRegex(R"(^(\w+)(\s*=\s*)(\w+)([\/\+\-\*])?([\w\.]+)?$)");
	smatch functionExpressionMatch;
	
	static const map<string, Action> strToSignMap{
		{"/", Action::Div},
		{"+", Action::Plus},
		{"-", Action::Sub},
		{"*", Action::Mult},
	};

	if (regex_search(expression, functionExpressionMatch, functionExpressionRegex))
	{
		string functionName = functionExpressionMatch[1];
		string operand1 = functionExpressionMatch[3];
		string operand2;
		Action sign = Action::None;
		if (functionExpressionMatch[4].matched && functionExpressionMatch[5].matched)
		{
			sign = strToSignMap.at(functionExpressionMatch[4]);
			operand2 = functionExpressionMatch[5];
			try {
				FunctionCallback callback = m_calculator.CreateBinaryFunctionCallback(operand1, operand2, sign);
				m_calculator.AddFunction(functionName, callback);
				return true;
			}
			catch (CalculatorException const& exception) {
				ExceptionHandler(exception);
				return false;
			}
		}
		try {
			FunctionCallback callback = m_calculator.CreateUnaryFunctionCallback(operand1);
			m_calculator.AddFunction(functionName, callback);
			return true;
		}
		catch (CalculatorException const& exception) {
			ExceptionHandler(exception);
			return false;
		}		
	}
	m_output << "Неверный формат введенной строки" << endl;
	return false;
}


bool CalculatorControl::PrintIdentificator(istream& args) const
{
	string id;
	args >> id;
	try {
		PrintValue(m_calculator.GetVarValue(id));
		m_output << endl;
		return true;
	}
	catch (CalculatorException const&) {
		try {
			PrintValue(m_calculator.CalculateFunction(id));
			m_output << endl;
			return true;
		}
		catch (CalculatorException const&) {
			m_output << "Ошибка: Идентификатора с именеи \"" + id + "\" не существует" << endl;
			return false;
		}
	}	
}

bool CalculatorControl::PrintVars(istream&) const
{
	map<string, double> varsMap = m_calculator.GetVarsMap();
	for (auto& var : varsMap)
	{
		string varName = var.first;
		m_output << varName << ":";
		PrintValue(varsMap.at(varName));
		m_output << endl;
	}
	return true;
}

bool CalculatorControl::PrintFunctions(istream&) const
{
	map<string, FunctionCallback> fnMap = m_calculator.GetFunctionsMap();
	for (auto& fn : fnMap)
	{
		string fnName = fn.first;
		m_output << fnName << ":";
		PrintValue(fnMap.at(fnName)());
		m_output << endl;
	}
	return true;
}

void CalculatorControl::PrintValue(double value) const
{
	if (isnan(value))
		m_output << "nan";
	else
		m_output << fixed << setprecision(2) << value;
}

void CalculatorControl::ExceptionHandler(CalculatorException const& exception) const {
	m_output << "Ошибка: " << exception.GetMessage() << endl;
}