#include <math.h>
#include <ctime>
#include "Cramer.h"
#include "FileWork.h"

/*----------------------
	����������� ������
  ----------------------*/

Cramer::Cramer(std::vector<std::vector<double> > mat, std::vector<double> var)
{
	matrix = mat;
	freeElements = var;
	complexity = 0;
	workTime = 0;
}

/*---------------------------------------------------------------------------------------------
	�������� �����, ���� ����'��� ����, �� ������� ������ ����'����, ���� ������� ������
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
	FileText.writeNameOfMethodAndMainDeterminant("����'������ ���� ������� �������", matrix, determinant);
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
	��������� �����, ���� ������� �������, � ��� ��������� �������� �������� �� ������� ������ ��������
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
	�������� �����, ���� ����� �������� ���� ��������� ����'����
  ------------------------------------------------------------------*/

double Cramer::getTime()
{
	return workTime;
}

/*--------------------------------------------------------------
	�������� �����, ���� ����� �������� ��������� ���������
  --------------------------------------------------------------*/

int Cramer::getComplexity()
{
	return complexity;
}