#include "GaussDiagonal.h"

/*----------------------
	Конструктор класса
  ----------------------*/

GaussDiagonal::GaussDiagonal(std::vector<std::vector<double> > mat, std::vector<double> var)
{
	matrix = mat;
	freeElements = var;
}

/*---------------------------------------------------------------------------------------------
	Публічний метод, який розв'язує СЛАР, та повертає вектор розв'язків, якщо система сумісна
  ---------------------------------------------------------------------------------------------*/

std::vector<double> GaussDiagonal::solve()
{
	double determinant = findDeterminant(matrix);
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

/*-------------------------------------------------------------------
	Приватний метод, який зводить матрицю до верхньотрикутного виду
  -------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------
	Приватний метод, який зводить верхньотрикутну матрицю до діагональної
  -------------------------------------------------------------------------*/

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

/*---------------------------------------------------------------------------------------------------------
	Приватний метод, який домножає кожний рядок матриці на відповідний множник, що звести ії до одиничної
  ---------------------------------------------------------------------------------------------------------*/

void GaussDiagonal::DiagonalToOne()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		double coef = pow(matrix[i][i], -1);
		matrix[i][i] = matrix[i][i] * coef;
		freeElements[i] = freeElements[i] * coef;
	}
}

/*------------------------------------------------------------------------------------------------------------
	Приватний метод, який міняє місцями ряди матриці, щоб уникнути ситуацій, коли на головній діагоналі нулі
  ------------------------------------------------------------------------------------------------------------*/

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