#include <vector>
#include <math.h>
#pragma once
class Cramer
{
private:
	std::vector<std::vector<double> > matrix;
	std::vector<double> freeElements;
	std::vector<std::vector<double> > replaceColumn(int);
public:
	static double findDeterminant(std::vector<std::vector<double> >);
	Cramer(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve();
};

