#pragma once
#include <vector>
#include "SystemOfLinearEquations.h"

class Cramer : public SystemOfLinearEquations
{
private:
	std::vector<std::vector<double> > replaceColumn(int);
public:
	Cramer(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve();
};

