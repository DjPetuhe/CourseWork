#pragma once
#include <vector>
#include "SystemOfLinearEquations.h"

/*----------------------------------------------
	Класс, який розв'язує СЛАР методом крамера
  ----------------------------------------------*/

class Cramer : public SystemOfLinearEquations
{
private:
	std::vector<std::vector<double> > replaceColumn(int);
public:
	Cramer(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve();
};

