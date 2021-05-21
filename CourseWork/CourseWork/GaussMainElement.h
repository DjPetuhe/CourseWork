#pragma once
#include <vector>

class GaussMainElement
{
	std::vector<std::vector<double> > matrix;
	std::vector<double> freeElements;
	std::vector<int> MainRow;
	std::vector<int> MainColumn;
	void findMax(int&, int&, double&);
	bool inMainRow(int);
	bool inMainColumn(int);
	void addCoef();
	void lastMainRowAndColumn();
	std::vector<double> findResult();
public:
	GaussMainElement(std::vector<std::vector<double> >, std::vector<double>);
	std::vector<double> solve();
};

