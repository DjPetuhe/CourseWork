#include <math.h>
#include <ctime>
#include "Cramer.h"
#include "FileWork.h"

/*----------------------
	Конструктор класса
  ----------------------*/

Cramer::Cramer(std::vector<std::vector<double> > mat, std::vector<double> var)
{
	matrix = mat;
	freeElements = var;
	complexity = 0;
	workTime = 0;
}

/*---------------------------------------------------------------------------------------------
	Публічний метод, який розв'язує СЛАР, та повертає вектор розв'язків, якщо система сумісна
  ---------------------------------------------------------------------------------------------*/

std::vector<double> Cramer::solve(std::string directory)
{
	FileWork FileText(directory);
	clock_t startTime = clock();
	std::vector<double> variables;
	std::vector<std::vector<double> > tempMatrix;
	float tempDeterminant;
	float determinant = findDeterminant(matrix, complexity);
	int step = 1;
	FileText.writeNameOfMethodAndMainDeterminant("Ровз'язання СЛАР методом Крамера", matrix, determinant);
	if (determinant != 0.0)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			tempMatrix = replaceColumn(i);
			tempDeterminant = findDeterminant(tempMatrix, complexity);
			step++;
			FileText.writeStepOfCramer(step, i, tempMatrix, tempDeterminant);
			variables.push_back(tempDeterminant / determinant);
		}
		clock_t endtime = clock();
		workTime = (double)(endtime - startTime) / CLOCKS_PER_SEC;
		FileText.writeResults(variables);
		FileText.writeStatistics(workTime, complexity);
	}
	else
	{
		//ERROR MESSAGE
		return {};
	}
	return variables;
}

/*--------------------------------------------------------------------------------------------------------------
	Приватний метод, який повертає матрицю, в якій відповідний стовпчик замінений на матрицю вільних елементів
  --------------------------------------------------------------------------------------------------------------*/

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
			complexity++;
		}
	}
	return matrWithColumn;
}

/*------------------------------------------------------------------
	Публічний метод, який вертає значення часу виконання розв'язка
  ------------------------------------------------------------------*/

double Cramer::getTime()
{
	return workTime;
}

/*--------------------------------------------------------------
	Публічний метод, який вертає значення складності алгоритма
  --------------------------------------------------------------*/

int Cramer::getComplexity()
{
	return complexity;
}