#pragma once
#include <vector>

/*--------------------------------------------------------
	Базовий клас для всіх інших методів ровз'язання СЛАР
  --------------------------------------------------------*/

class SystemOfLinearEquations
{
protected:
	std::vector<std::vector<double> > matrix;
	std::vector<double> freeElements;
	static double findDeterminant(std::vector<std::vector<double> >);
};