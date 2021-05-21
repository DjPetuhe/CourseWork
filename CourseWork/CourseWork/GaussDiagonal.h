#pragma once
#include <vector>
#include <string>
#include "FileWork.h"
#include "SystemOfLinearEquations.h"

/*------------------------------------------------------------------------------
	�����, ���� ����'��� ���� ������� ������-������� (� ��������� ���������)
  ------------------------------------------------------------------------------*/

class GaussDiagonal: public SystemOfLinearEquations
{
private:
	void ToUpTriangle(FileWork&, int&);
	void ToDiagonal(FileWork& , int&);
	bool replaceColums(int, FileWork&, int&);
	void DiagonalToOne(FileWork&, int&);
public:
	GaussDiagonal(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve(std::string);
	double getTime();
	int getComplexity();
};

