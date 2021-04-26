#pragma once

std::vector<double> ReadVector(std::istream& in);
std::vector<double> DivideByHalfMaximum(std::vector<double> const& numbers);
void PrintVectorAscending(std::ostream& out, std::vector<double>& vector);