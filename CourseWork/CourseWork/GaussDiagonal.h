#pragma once
#include <vector>
#include "SystemOfLinearEquations.h"

/*------------------------------------------------------------------------------
	Класс, який розв'язує СЛАР методом Гаусса-Жордана (з одиничною діагоналлю)
  ------------------------------------------------------------------------------*/

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

