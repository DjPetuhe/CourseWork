#include "SystemOfLinearEquations.h"

/*-------------------------------------------------------------
	Метод, який знаходить визначник матриці, та повератє його
  -------------------------------------------------------------*/

double SystemOfLinearEquations::findDeterminant(std::vector<std::vector<double> > matr)
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
			determinant = determinant + (pow(-1, c) * matr[0][c] * findDeterminant(submatrix));
		}
	}
	return determinant;
}