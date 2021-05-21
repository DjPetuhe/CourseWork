#include "GaussDiagonal.h"
#include "Cramer.h"

GaussDiagonal::GaussDiagonal(std::vector<std::vector<double> > mat, std::vector<double> var)
{
	matrix = mat;
	freeElements = var;
}

std::vector<double> GaussDiagonal::solve()
{
	double determinant = Cramer::findDeterminant(matrix);
	if (determinant != 0.0)
	{
		replaceColums(0);
		ToUpTriangle();
		ToDiagonal();
 		DiagonalToOne();
	}
	else
	{
		//ERROR MESSAGE 
		return {};
	}
	return this->freeElements;
}


void GaussDiagonal::ToUpTriangle()
{
	for (int k = 0; k < matrix.size() - 1; k++)
	{
		for (int i = k+1; i < matrix.size(); i++)
		{
			double coef = matrix[i][k] / matrix[k][k];
			for (int j = k; j < matrix.size(); j++)
			{
				matrix[i][j] = matrix[i][j] - matrix[k][j] * coef;
			}
			freeElements[i] = freeElements[i] - freeElements[k] * coef;
		}
	}
}

void GaussDiagonal::ToDiagonal()
{
	for (int k = matrix.size() - 1; k >= 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			double coef = matrix[i][k] / matrix[k][k];
			for (int j = k; j >= 0; j--)
			{
				matrix[i][j] = matrix[i][j] - matrix[k][j]* coef;
			}
			freeElements[i] = freeElements[i] - freeElements[k] * coef;
		}
	}
}

void GaussDiagonal::DiagonalToOne()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		double coef = pow(matrix[i][i], -1);
		matrix[i][i] = matrix[i][i] * coef;
		freeElements[i] = freeElements[i] * coef;
	}
}

bool GaussDiagonal::replaceColums(int n)
{
	bool finished = false;
	if (n < matrix.size())
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[n][n] != 0 && !finished)
			{
				finished = replaceColums(n + 1);
			}
			else if (!finished)
			{
				for (int j = 0; j < matrix.size(); j++)
				{
					double temp = matrix[n][j];
					matrix[n][j] = matrix[i][j];
					matrix[i][j] = temp;
				}
				double temp = freeElements[n];
				freeElements[n] = freeElements[i];
				freeElements[i] = temp;
			}
			else if (finished)
			{
				return true;
			}
		}
	}
	else
	{
		return true;
	}
}