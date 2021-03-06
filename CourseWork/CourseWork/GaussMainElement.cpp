#include <math.h>
#include <ctime>
#include "GaussMainElement.h"

/*----------------------
	??????????? ?????? 
  ----------------------*/

GaussMainElement::GaussMainElement(std::vector<std::vector<double>> mat, std::vector<double> free)
{
	matrix = mat;
	freeElements = free;
	complexity = 0;
	workTime = 0;
}

/*---------------------------------------------------------------------------------------------
	????????? ?????, ???? ????'???? ????, ?? ???????? ?????? ????'?????, ???? ??????? ???????
  ---------------------------------------------------------------------------------------------*/

std::vector<double> GaussMainElement::solve(std::string directory)
{
	FileWork FileText(directory);
	clock_t startTime = clock();
	double determinant = findDeterminant(matrix, complexity);
	FileText.writeNameOfMethodAndMainDeterminant("????'?????? ???? ??????? ????? ? ??????? ????????? ???????? ? ???????", matrix, determinant);
	int step = 1;
	if (determinant != 0)
	{
		for (int i = 0; i < matrix.size() - 1; i++)
		{
			int i_max, j_max;
			double max = INT_MIN;
			findMax(i_max, j_max, max);
			step++;
			FileText.writeStepOfGaussMainElementFind(step, "??????????? ??????????? ?? ??????? ???????? ????? ?????????? ?????? ?? ????????", matrix, i_max, j_max, max);
			MainRow.push_back(i_max);
			MainColumn.push_back(j_max);
			addCoef(FileText, step);
		}
		lastMainRowAndColumn(FileText, step);
		std::vector<double> results = findResult();
		clock_t endtime = clock();
		workTime = (double)(endtime - startTime) / CLOCKS_PER_SEC;
		FileText.writeResults(results);
		FileText.writeStatistics(workTime, complexity);
		return results;
	}
	else
	{
		//Error Message
		return {};
	}
}

/*--------------------------------------------------------------------------------------------------
	????????? ?????, ???? ????????? ?????????? ??????? ????? ?????????? ?????? ?? ???????? ???????
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
	????????? ?????, ???? ???????? ??????????, ???? ????? ????? ? ????????, ? ????????, ???? ??
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
	????????? ?????, ???? ???????? ??????????, ???? ????? ???????? ? ????????, ? ????????, ???? ??
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
	????????? ?????, ???? ??? ??????? ??????????? ????? ??????? ???????? ???????, 
	?? ????? ?? ????? ??????????? ?? ??? ??????? ???????? ?????.
  ---------------------------------------------------------------------------------*/

void GaussMainElement::addCoef(FileWork &FileText, int &step)
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
			step++;
			FileText.writeStepOfGaussMainElementMultiplication(step,i,matrix, coef);
		}
	}
}
/*-------------------------------------------------------------------------------------------------------
	????????? ?????, ???? ????? ?? ???????? ?????? ?? ???????? ???????? ???????? ?? ????? ? ??????? 1?1
  -------------------------------------------------------------------------------------------------------*/

void GaussMainElement::lastMainRowAndColumn(FileWork &FileText, int &step)
{
	int i_last, j_last;
	for (int i = 0; i < matrix.size(); i++)
	{
		if (!inMainRow(i))
		{
			MainRow.push_back(i);
			i_last = i;
		}
		if (!inMainColumn(i))
		{
			MainColumn.push_back(i);
			j_last = i;
		}
	}
	step++;
	FileText.writeStepOfGaussMainElement(step, i_last, j_last);
}

/*----------------------------------------------------------------------------------------------------------------
	????????? ?????, ????????? ?? ???????? ?????? ????'?????, ??? ????????? ??????? ????????? ?? ????? ?????????
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
			complexity++;
		}
		results[MainColumn[i]] = (freeElements[MainRow[i]] - S) / matrix[MainRow[i]][MainColumn[i]];
	}
	return results;
}

/*------------------------------------------------------------------
	????????? ?????, ???? ?????? ???????? ???? ????????? ????'????
  ------------------------------------------------------------------*/

double GaussMainElement::getTime()
{
	return workTime;
}

/*--------------------------------------------------------------
	????????? ?????, ???? ?????? ???????? ?????????? ?????????
  --------------------------------------------------------------*/

int GaussMainElement::getComplexity()
{
	return complexity;
}