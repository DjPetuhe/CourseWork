#pragma once
#include <vector>

class SystemOfLinearEquations
{
protected:
	std::vector<std::vector<double> > matrix;
	std::vector<double> freeElements;
	static double findDeterminant(std::vector<std::vector<double> >);
};