#pragma once
#include <vector>
#include <string>
#include "FileWork.h"
#include "SystemOfLinearEquations.h"

/*------------------------------------------------------------------------------------
	Класс, який розв'язує СЛАР методом Гаусса з вибором головного елемента в матриці
  ------------------------------------------------------------------------------------*/

class GaussMainElement: public SystemOfLinearEquations
{
	std::vector<int> MainRow;
	std::vector<int> MainColumn;
	void findMax(int&, int&, double&);
	bool inMainRow(int);
	bool inMainColumn(int);
	void addCoef(FileWork &, int &);
	void lastMainRowAndColumn(FileWork &, int&);
	std::vector<double> findResult();
public:
	GaussMainElement(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve(std::string);
	double getTime();
	int getComplexity();
};

