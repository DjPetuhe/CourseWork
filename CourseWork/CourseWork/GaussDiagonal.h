#pragma once
#include <vector>
#include "SystemOfLinearEquations.h"

class GaussDiagonal: public SystemOfLinearEquations
{
private:
	void ToUpTriangle();
	void ToDiagonal();
	bool replaceColums(int);
	void DiagonalToOne();
public:
	GaussDiagonal(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve();
};

