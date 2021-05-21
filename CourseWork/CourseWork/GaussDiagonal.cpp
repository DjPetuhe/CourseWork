#include <ctime>
#include "GaussDiagonal.h"

/*----------------------
	����������� ������
  ----------------------*/

GaussDiagonal::GaussDiagonal(std::vector<std::vector<double> > mat, std::vector<double> var)
{
	matrix = mat;
	freeElements = var;
	complexity = 0;
	workTime = 0;
}

/*---------------------------------------------------------------------------------------------
	�������� �����, ���� ����'��� ����, �� ������� ������ ����'����, ���� ������� ������
  ---------------------------------------------------------------------------------------------*/

std::vector<double> GaussDiagonal::solve(std::string directory)
{
	FileWork FileText(directory);
	clock_t startTime = clock();
	double determinant = findDeterminant(matrix, complexity);
	int step = 1;
	FileText.writeNameOfMethodAndMainDeterminant("����'������ ���� ������� �����-������� (� ��������� ���������)", matrix, determinant);
	if (determinant != 0.0)
	{
		replaceColums(0,FileText, step);
		ToUpTriangle(FileText, step);
		ToDiagonal(FileText, step);
 		DiagonalToOne(FileText, step);
		FileText.writeResults(freeElements);
		clock_t endtime = clock();
		workTime = (double)(endtime - startTime) / CLOCKS_PER_SEC;
		FileText.writeStatistics(workTime, complexity);
	}
	else
	{
		//ERROR MESSAGE 
		return {};
	}
	return this->freeElements;
}

/*-------------------------------------------------------------------
	��������� �����, ���� ������� ������� �� ����������������� ����
  -------------------------------------------------------------------*/

void GaussDiagonal::ToUpTriangle(FileWork& FileText, int& step)
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
			step++;
			FileText.writeStepOfGaussDiagnonal(step, i, k, "�������� ������� �� ����������������� ����",matrix, coef);
		}
	}
}

/*-------------------------------------------------------------------------
	��������� �����, ���� ������� ��������������� ������� �� ����������
  -------------------------------------------------------------------------*/

void GaussDiagonal::ToDiagonal(FileWork& FileText, int& step)
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
			step++;
			FileText.writeStepOfGaussDiagnonal(step, i, k, "�������� ������� �� ���������� �������", matrix, coef);
		}
	}
}

/*---------------------------------------------------------------------------------------------------------
	��������� �����, ���� ������� ������ ����� ������� �� ��������� �������, �� ������ �� �� ��������
  ---------------------------------------------------------------------------------------------------------*/

void GaussDiagonal::DiagonalToOne(FileWork& FileText, int& step)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		double coef = pow(matrix[i][i], -1);
		matrix[i][i] = matrix[i][i] * coef;
		freeElements[i] = freeElements[i] * coef;
		step++;
		FileText.writeStepOfGaussDiagnonalMult(step,i,matrix,coef);
	}
}

/*------------------------------------------------------------------------------------------------------------
	��������� �����, ���� ���� ������ ���� �������, ��� �������� ��������, ���� �� ������� ������� ���
  ------------------------------------------------------------------------------------------------------------*/

bool GaussDiagonal::replaceColums(int n, FileWork& FileText, int& step)
{
	bool finished = false;
	if (n < matrix.size())
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[n][n] != 0 && !finished)
			{
				finished = replaceColums(n + 1, FileText, step);
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

/*------------------------------------------------------------------
	�������� �����, ���� ����� �������� ���� ��������� ����'����
  ------------------------------------------------------------------*/

double GaussDiagonal::getTime()
{
	return workTime;
}

/*--------------------------------------------------------------
	�������� �����, ���� ����� �������� ��������� ���������
  --------------------------------------------------------------*/

int GaussDiagonal::getComplexity()
{
	return complexity;
}
