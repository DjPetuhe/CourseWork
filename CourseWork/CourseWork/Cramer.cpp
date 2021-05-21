#include "Cramer.h"
#include <math.h>

std::vector<double> Cramer::solve()
{
	std::vector<double> variables;
	std::vector<std::vector<double> > tempMatrix;
	float tempDeterminant;
	float determinant = findDeterminant(matrix);
	if (determinant != 0.0)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			tempMatrix = replaceColumn(i);
			tempDeterminant = findDeterminant(tempMatrix);
			variables.push_back(tempDeterminant / determinant);
		}
	}
	else
	{
		//ERROR MESSAGE
		return {};
	}
	return variables;
}

Cramer::Cramer(std::vector<std::vector<double> > mat, std::vector<double> var)
{
	matrix = mat;
	freeElements = var;
}

std::vector<std::vector<double> > Cramer::replaceColumn(int column)
{
	std::vector<std::vector<double> > matrWithColumn(matrix.size(), std::vector<double>(matrix.size()));
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (j == column)
			{
				matrWithColumn[i][j] = freeElements[i];
			}
			else
			{
				matrWithColumn[i][j] = matrix[i][j];
			}
		}
	}
	return matrWithColumn;
}