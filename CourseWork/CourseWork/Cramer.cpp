#include "Cramer.h"
#include <iostream>

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

double Cramer::findDeterminant(std::vector<std::vector<double> > matr)
{
	float determinant = 0.0;
	std::vector<std::vector<double> > submatrix(matr.size() - 1, std::vector<double>(matr.size() - 1));
	if (matr.size() == 1)
	{
		return matr[0][0];
	}
	else if (matr.size() == 2)
	{
		return ((matr[0][0] * matr[1][1]) - (matr[0][1] * matr[1][0]));
	}
	else
	{
		for (int c = 0; c < matr.size(); c++)
		{
			int subi = 0;
			for (int i = 1; i < matr.size(); i++)
			{
				int subj = 0;
				for (int j = 0; j < matr.size(); j++)
				{
					if (j == c)
					{
						continue;
					}
					submatrix[subi][subj] = matr[i][j];
					subj++;
				}
				subi++;
			}
			determinant = determinant + (pow(-1, c ) * matr[0][c] * findDeterminant(submatrix));
		}
	}
	return determinant;
}