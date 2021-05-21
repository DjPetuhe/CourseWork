#pragma once
#include <vector>
#include <string>
#include <fstream>

/*-----------------------------------------------
	Класс, який записує розв'язання СЛАР в файл
  -----------------------------------------------*/

class FileWork
{
	std::string directory;
	void writeMatrix(std::ofstream &FileText, std::vector<std::vector<double>> matrix);
public:
	FileWork(std::string);
	void writeNameOfMethodAndMainDeterminant(std::string, std::vector<std::vector<double> >, double);
	void writeStepOfGaussMainElementFind(int, std::string, std::vector<std::vector<double> >, int, int, double);
	void writeStepOfGaussMainElementMultiplication(int, int, std::vector<std::vector<double> >, double);
	void writeStepOfGaussMainElement(int, int , int);
	void writeStepOfGaussDiagnonal(int, int, int, std::string, std::vector<std::vector<double> >, double);
	void writeStepOfGaussDiagnonalMult(int step, int i, std::vector<std::vector<double> > matrix, double coef);
	void writeStepOfGaussDiagnonalReplace(int step, int i, int k, std::vector<std::vector<double> >);
	void writeStepOfCramer(int, int, std::vector<std::vector<double> >, double);
	void writeResults(std::vector<double>);
	void writeStatistics(double time, int complexity);
};

