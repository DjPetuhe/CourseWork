#include "GaussDiagonal.h"
#include "Cramer.h"
#include <iostream> //!!!!!
using namespace std;

GaussDiagonal::GaussDiagonal(vector<vector<double> > mat, vector<double> var)
{
	matrix = mat;
	freeElements = var;
}

vector<double> GaussDiagonal::solve()
{
	double determinant = Cramer::findDeterminant(matrix);
	if (determinant != 0.0)
	{
		//replaceColums();
		ToUpTriangle();
		ToDiagonal();
		DiagonalToOne();
	}
	else
	{
		cout << "Error!";
		freeElements.clear();
	}
	return this->freeElements;
}


void GaussDiagonal::ToUpTriangle()
{
	for (int k = 0; k < matrix.size() - 1; k++)
	{
		for (int i = k+1; i < matrix.size(); i++)
		{
			double coef = matrix[k][k] / matrix[i][k];
			for (int j = k; j < matrix.size(); j++)
			{
				matrix[i][j] = matrix[k][j] - matrix[i][j] * coef;
			}
			freeElements[i] = freeElements[k] - freeElements[i] * coef;
		}
	}
}

void GaussDiagonal::DiagonalToOne()
{
	for (int k = matrix.size() - 1; k > 0; k--)
	{
		for (int i = k - 1; i > 0; i--)
		{
			double coef = matrix[k][k] / matrix[i][k];
			for (int j = k; j > 0; j--)
			{
				matrix[i][j] = matrix[k][j] - matrix[i][j] * coef;
			}
			freeElements[i] = freeElements[k] - freeElements[i] * coef;
		}
	}
}

void GaussDiagonal::ToDiagonal()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		double coef = pow(matrix[i][i], -1);
		matrix[i][i] = matrix[i][i] * coef;
		freeElements[i] = freeElements[i] * coef;
	}
}

void GaussDiagonal::replaceColums()
{

}