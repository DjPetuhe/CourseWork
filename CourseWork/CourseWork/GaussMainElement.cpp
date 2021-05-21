#include "GaussMainElement.h"
#include <math.h>

/*----------------------
	Конструктор класса 
  ----------------------*/

GaussMainElement::GaussMainElement(std::vector<std::vector<double>> mat, std::vector<double> free)
{
	matrix = mat;
	freeElements = free;
}

/*---------------------------------------------------------------------------------------------
	Публічний метод, який розв'язує СЛАР, та повертає вектор розв'язків, якщо система сумісна
  ---------------------------------------------------------------------------------------------*/

std::vector<double> GaussMainElement::solve()
{
	double determinant = findDeterminant(matrix);
	if (determinant != 0)
	{
		for (int i = 0; i < matrix.size() - 1; i++)
		{
			int i_max, j_max;
			double max = INT_MIN;
			findMax(i_max, j_max, max);
			MainRow.push_back(i_max);
			MainColumn.push_back(j_max);
			addCoef();
		}
		lastMainRowAndColumn();
		return findResult();
	}
	else
	{
		//Error Message
		return {};
	}
}

/*--------------------------------------------------------------------------------------------------
	Приватний метод, який знаходить найбільший елемент серед неголовних рядків та стовпців матриці
  --------------------------------------------------------------------------------------------------*/

void GaussMainElement::findMax(int &i_max, int &j_max, double &max)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (abs(matrix[i][j]) > max && (!inMainRow(i)) && (!inMainColumn(j)))
			{
				i_max = i;
				j_max = j;
				max = matrix[i][j];
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------------
	Приватний метод, який повертає істинність, якщо даний рядок є головним, і хибність, якщо ні
  -----------------------------------------------------------------------------------------------*/

bool GaussMainElement::inMainRow(int index)
{
	for (int i = 0; i < MainRow.size(); i++)
	{
		if (MainRow[i] == index)
		{
			return true;
		}
	}
	return false;
}

/*--------------------------------------------------------------------------------------------------
	Приватний метод, який повертає істинність, якщо даний стовпець є головним, і хибність, якщо ні
  --------------------------------------------------------------------------------------------------*/

bool GaussMainElement::inMainColumn(int index)
{
	bool in = false;
	for (int i = 0; i < MainColumn.size(); i++)
	{
		if (MainColumn[i] == index)
		{
			return true;
		}
	}
	return false;
}

/*---------------------------------------------------------------------------------
	Приватний метод, який для кожного неголовного рядка матриці обчислює множник, 
	та додає до нього домноженний на цей множник головний рядок.
  ---------------------------------------------------------------------------------*/

void GaussMainElement::addCoef()
{
	double coef;
	for (int i = 0; i < matrix.size(); i++)
	{
		if (!inMainRow(i))
		{
			coef = -matrix[i][MainColumn.back()]/(double)matrix[MainRow.back()][MainColumn.back()];
			for (int j = 0; j < matrix.size(); j++)
			{
				if (!inMainColumn(j))
				{
					matrix[i][j] = matrix[i][j] + matrix[MainRow.back()][j] * coef;
				}
			}
			freeElements[i] = freeElements[i] + freeElements[MainRow.back()] * coef;
		}
	}
}
/*-------------------------------------------------------------------------------------------------------
	Приватний метод, який додає до головних рядків та стовбців останній стовпець та рядок в матрциі 1х1
  -------------------------------------------------------------------------------------------------------*/

void GaussMainElement::lastMainRowAndColumn()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		if (!inMainRow(i))
		{
			MainRow.push_back(i);
		}
		if (!inMainColumn(i))
		{
			MainColumn.push_back(i);
		}
	}
}

/*----------------------------------------------------------------------------------------------------------------
	Приватний метод, знаходить та повертає вектор розв'язків, які знаходить завдяки знайденим до цього значенням
  ----------------------------------------------------------------------------------------------------------------*/

std::vector<double> GaussMainElement::findResult()
{
	std::vector<double> results(matrix.size());
	results[MainColumn.back()] = freeElements[MainRow.back()] / (double)matrix[MainRow.back()][MainColumn.back()];
	for (int i = MainRow.size() - 2; i >= 0; i--)
	{
		double S = 0;
		for (int j = i + 1; j < MainRow.size(); j++)
		{
			S += matrix[MainRow[i]][MainColumn[j]] * results[MainColumn[j]];
		}
		results[MainColumn[i]] = (freeElements[MainRow[i]] - S) / matrix[MainRow[i]][MainColumn[i]];
	}
	return results;
}