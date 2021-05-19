#pragma once
#include <vector>

class GaussDiagonal
{
private:
	std::vector<std::vector<double> > matrix;
	std::vector<double> freeElements;
	void ToUpTriangle();
	void ToDiagonal();
	void replaceColums();
	void DiagonalToOne();
public:
	GaussDiagonal(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve();
};

