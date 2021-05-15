#include <vector>
#include <math.h>
#pragma once
class Cramer
{
private:
	std::vector<std::vector<float>> matrix;
	std::vector<float> freeElements;
public:
	Cramer(std::vector<std::vector<float>>, std::vector<float>);
	std::vector<float> solve();
	std::vector<std::vector<float>> replaceColumn(int);
	static float findDeterminant(std::vector<std::vector<float>>);
};

