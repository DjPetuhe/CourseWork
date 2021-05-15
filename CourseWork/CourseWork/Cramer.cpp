#include "Cramer.h"
#include <iostream>
using namespace std;

vector<float> Cramer::solve()
{
	vector<float> variables;
	vector<vector<float>> tempMatrix;
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
		cout << endl <<"Error!" << endl;
	}
	return variables;
}

Cramer::Cramer(vector<vector<float>> mat, vector<float> var)
{
	matrix = mat;
	freeElements = var;
}

vector<vector<float>> Cramer::replaceColumn(int column)
{
	vector<vector<float>> matrWithColumn(matrix.size(),vector<float>(matrix.size()));
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

float Cramer::findDeterminant(vector<vector<float>> matr)
{
	float determinant = 0.0;
	vector<vector<float>> submatrix(matr.size() - 1, vector<float>(matr.size() - 1));
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