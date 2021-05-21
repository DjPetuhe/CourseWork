#include <fstream>
#include <math.h>
#include <iomanip>
#include "FileWork.h"

/*----------------------
	����������� ������
  ----------------------*/

FileWork::FileWork(std::string dir)
{
	directory = dir;
}

/*--------------------------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ����� ������ �� ��������� ������� �������.
  --------------------------------------------------------------------------------------*/

void FileWork::writeNameOfMethodAndMainDeterminant(std::string str, std::vector<std::vector<double>> matrix, double determinant)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{	
		FileText << "\n*************************************************************************************************************\n";
		FileText << str << '\n';
		FileText << "���� �1\n ����������� ���������� �������, �� ��������, �� � �� ������� �������.\n";
		writeMatrix(FileText, matrix);
		FileText << "\n��������� ���� ������� = " << determinant << '\n';
		if (determinant)
		{
			FileText << "��������� ���� ������� �� ������� ���� => ������� ������.\n";
		}
		else
		{
			FileText << "��������� ���� ������� ������� ���� => ������� �� ������.\n";
			FileText << "*************************************************************************************************************\n";
		}
	}
	FileText.close();
}

/*----------------------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ���� ����������� ��������� �������� ��� 
	����'����� ������� ������ � ������� ��������� �������� � �������
  ----------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussMainElementFind(int step, std::string str, std::vector<std::vector<double> > matrix, int i_max, int j_max, double max)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n���� �" << step << '\n' << str << '\n';
		writeMatrix(FileText, matrix);
		FileText << "\n��������� �� ������� ������� ����� ���������� ����� �� ��������: A[" << i_max + 1 << "][" << j_max + 1 << "] = " << max << '\n';
	}
	FileText.close();
}

/*-----------------------------------------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ���� � ����������� ���������� ����� �� �������� ������� ��
	��������� ���������� ��� ����'����� ������� ������ � ������� ��������� �������� � �������
  -----------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussMainElementMultiplication(int step, int i, std::vector<std::vector<double> > matrix, double coef)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n���� �" << step << "\n����������� �������� ��� ����� �� ��������� �� ����� ��������� ����� ������������ �� ��� �������\n";
		FileText << "������� ��� " << i + 1 << "-�� �����: " << coef << '\n';
		FileText << "������� ���� ��������� �����������:\n";
		writeMatrix(FileText,matrix);
		FileText << '\n';
	}
	FileText.close();
}

void FileWork::writeStepOfGaussMainElement(int step, int i, int j)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n���� �" << step << "\nԳ������� ����. ����� ���������� � ��� ���������� ���� "<< i+1 << " ����� �� "<< j+1 << " ��������.\n";
		FileText << "������� �� �� �������� ����� �� ���������. ��������� ���������� ������� �� ���������� ������� ����� ������� ����������.\n";
		FileText << "��� �����, �ᒺ����� � �������, ��������� � ����������, ���� ������� � ������� , �� ������ �����. � ��������� ��������\n";
		FileText << "������� �� ��������� ���, ����� ��������� ������.\n";
	}
	FileText.close();
}

/*---------------------------------------------------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ����� ����'������ ���� ������� �����-������� (� ��������� ���������) 
  ---------------------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussDiagnonal(int step, int i, int k, std::string str, std::vector<std::vector<double> > matrix, double coef)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n���� �" << step << "\n" << str;
		FileText << "\n³� ������� �������� " << i + 1 << "-�� ����� ������� ��������� ������� " << k + 1 << "-�� ������ ������������ �� ����������.";
		FileText << "\n���������� �������� = " << coef << '\n';
		FileText << "������� ���� ��������:\n";
		writeMatrix(FileText, matrix);
	}
	FileText.close();
}

/*---------------------------------------------------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ����� ����'������ ���� ������� �����-������� (� ��������� ���������)
  ---------------------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussDiagnonalMult(int step, int i, std::vector<std::vector<double> > matrix, double coef)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n���� �" << step << "\n" << "������������ � �������� �������";
		FileText << "\n������� �������" << i + 1 << "-�� ����� �� ����� ����������, ��� ������ ���� �� 1.";
		FileText << "\n���������� �������� = " << coef << '\n';
		FileText << "������� ���� ��������:\n";
		writeMatrix(FileText, matrix);
	}
	FileText.close();
}

/*----------------------------------------------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ����� ������������ �����, � �������, ���� �� �������� ���������
	���������� ������ �������� ��� ����'���� ���� ������� �����-������� (� ��������� ���������)
  ----------------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussDiagnonalReplace(int step, int i, int k, std::vector<std::vector<double>>matrix)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n���� �" << step << "\n��� �������� ������� ����� �������� ������� �� ������� ������� ����������� ����� �����.\n";
		FileText << "������� ������� " << i + 1 << " �� " << k + 1 << "�����.\n";
		FileText << "������� ���� ������������:\n";
		writeMatrix(FileText, matrix);
	}
	FileText.close();
}

/*--------------------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ����� ����'������ ���� ������� �������
  --------------------------------------------------------------------------------*/

void FileWork::writeStepOfCramer(int step, int i, std::vector<std::vector<double>> matrix, double det)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n���� �" << step << "\n��������� ��������� �������, � ���� ������� ��������\n";
		FileText << "�� ������� " << i + 1 << " �������� ���������� ������� ���������� � �������� �������:\n";
		writeMatrix(FileText, matrix);
		FileText << "\n��������� ���� ���������: " << det << '\n';
		FileText << "ĳ���� ��� ��������� �� ��������� � �������� ��������� �����\n";
	}
	FileText.close();
}

/*---------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ���������� ����'������ ���� 
  ---------------------------------------------------------------------*/

void FileWork::writeResults(std::vector<double> results)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n����������:\n";
		for (int i = 0; i < results.size(); i++)
		{
			FileText << 'X' << i + 1 << " = " << round(results[i] * 100000) / 100000.0 << '\n';
		}
	}
	FileText.close();
}

/*-----------------------------------------------------------------------
	�������� �����, ���� ���� ���������� ���������� ������ ����'������
  -----------------------------------------------------------------------*/

void FileWork::writeStatistics(double workTime, int complexity)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n----------------------------";
		FileText << "\n���������� ������ ���������:\n";
		FileText << "��������� ���������: " << complexity << " ��������.\n";
		FileText << "��� ���������: " << workTime << " ������.\n";
		FileText << "*************************************************************************************************************\n";
	}
	FileText.close();
}

/*--------------------------------------------------------
	��������� �����, ���� ���� ���������� ������� � ����
  --------------------------------------------------------*/

void FileWork::writeMatrix(std::ofstream &FileText, std::vector<std::vector<double> > matrix)
{
	FileText << '\n' << "----";
	for (int i = 0; i < matrix.size(); i++)
	{
		FileText << "----------";
	}
	FileText << "\n   |";
	for (int i = 0; i < matrix.size(); i++)
	{
		FileText << std::setw(10) << i + 1;
	}
	FileText << '\n' << "----";
	for (int i = 0; i < matrix.size(); i++)
	{
		FileText << "----------";
	}
	FileText << '\n';
	for (int i = 0; i < matrix.size(); i++)
	{
		FileText << std::setw(2) << i + 1 << " |";
		for (int j = 0; j < matrix.size(); j++)
		{
			FileText << std::setw(10) << round(matrix[i][j] * 100000) / 100000.0;
		}
		FileText << '\n';
	}
	FileText << "----";
	for (int i = 0; i < matrix.size(); i++)
	{
		FileText << "----------";
	}
	FileText << '\n';
}