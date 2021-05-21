#include <fstream>
#include <math.h>
#include <iomanip>
#include "FileWork.h"

/*----------------------
	Конструктор класса
  ----------------------*/

FileWork::FileWork(std::string dir)
{
	directory = dir;
}

/*--------------------------------------------------------------------------------------
	Публічний метод, який буде записувати назву метода та визначник головної матриці.
  --------------------------------------------------------------------------------------*/

void FileWork::writeNameOfMethodAndMainDeterminant(std::string str, std::vector<std::vector<double>> matrix, double determinant)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{	
		FileText << "\n*************************************************************************************************************\n";
		FileText << str << '\n';
		FileText << "Крок №1\n знаходження визначника матриці, та перевірка, чи є ця система сумісною.\n";
		writeMatrix(FileText, matrix);
		FileText << "\nВизначник цієї матриці = " << determinant << '\n';
		if (determinant)
		{
			FileText << "Визначник цієї матриці не дорівнює нулю => система сумісна.\n";
		}
		else
		{
			FileText << "Визначник цієї матриці дорівнює нулю => система не сумісна.\n";
			FileText << "*************************************************************************************************************\n";
		}
	}
	FileText.close();
}

/*----------------------------------------------------------------------------------
	Публічний метод, який буде записувати крок знаходження головного елемента при 
	розв'язанні методом Гаусса з вибором головного елемента в матриці
  ----------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussMainElementFind(int step, std::string str, std::vector<std::vector<double> > matrix, int i_max, int j_max, double max)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\nКрок №" << step << '\n' << str << '\n';
		writeMatrix(FileText, matrix);
		FileText << "\nНайбільший за модулем елемент серед неголовних рядків та стовпців: A[" << i_max + 1 << "][" << j_max + 1 << "] = " << max << '\n';
	}
	FileText.close();
}

/*-----------------------------------------------------------------------------------------------------
	Публічний метод, який буде записувати крок з домноженням неголовних рядків та сповпців матриці на
	відповідний коефіціент при розв'язанні методом Гаусса з вибором головного елемента в матриці
  -----------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussMainElementMultiplication(int step, int i, std::vector<std::vector<double> > matrix, double coef)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\nКрок №" << step << "\nЗнаходження множника для рядка та додавання до нього головного рядка помноженного на цей множник\n";
		FileText << "Множник для " << i + 1 << "-го рядка: " << coef << '\n';
		FileText << "Матриця після відповідних перетворень:\n";
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
		FileText << "\nКрок №" << step << "\nФінальний крок. Серед неголовних в нас залишилися лише "<< i+1 << " рядок та "<< j+1 << " стовпчик.\n";
		FileText << "Додаэмо їх до головних рядків та стовпчиків. Процедуру приведення матриці до трикутного вигляду можно вважати завершеною.\n";
		FileText << "Для цього, об’єднуємо в систему, починаючи з останнього, який входить в матрицю , всі головні рядки. В результаті отримуємо\n";
		FileText << "систему за допомогою якої, легко знаходимо невідомі.\n";
	}
	FileText.close();
}

/*---------------------------------------------------------------------------------------------------------------
	Публічний метод, який буде записувати кроки розв'язання СЛАР методом Гауса-Жордана (з одиничною діагоналлю) 
  ---------------------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussDiagnonal(int step, int i, int k, std::string str, std::vector<std::vector<double> > matrix, double coef)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\nКрок №" << step << "\n" << str;
		FileText << "\nВід кожного елемента " << i + 1 << "-го рядка віднімаємо відповідний елемент " << k + 1 << "-го ряждка домноженного на коефіцієнт.";
		FileText << "\nКоефіцієнт множення = " << coef << '\n';
		FileText << "Матриця після множення:\n";
		writeMatrix(FileText, matrix);
	}
	FileText.close();
}

/*---------------------------------------------------------------------------------------------------------------
	Публічний метод, який буде записувати кроки розв'язання СЛАР методом Гауса-Жордана (з одиничною діагоналлю)
  ---------------------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussDiagnonalMult(int step, int i, std::vector<std::vector<double> > matrix, double coef)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\nКрок №" << step << "\n" << "Перетворення в одиничну матрицю";
		FileText << "\nМножимо елемент" << i + 1 << "-го рядка на такий коефіцієнт, щоб звести його до 1.";
		FileText << "\nКоефіцієнт множення = " << coef << '\n';
		FileText << "Матриця після множення:\n";
		writeMatrix(FileText, matrix);
	}
	FileText.close();
}

/*----------------------------------------------------------------------------------------------------------
	Публічний метод, який буде записувати кроки перестановки рядків, у випадку, якщо на головних елементах
	виявляться нульові значення при розв'язку СЛАР методом Гауса-Жордана (з одиничною діагоналлю)
  ----------------------------------------------------------------------------------------------------------*/

void FileWork::writeStepOfGaussDiagnonalReplace(int step, int i, int k, std::vector<std::vector<double>>matrix)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\nКрок №" << step << "\nЩоб уникнути помилку через нульовий елемент на головної діагоналі переставимо рядки міцями.\n";
		FileText << "Змінюємо місціями " << i + 1 << " та " << k + 1 << "рядки.\n";
		FileText << "Матриця після перестановок:\n";
		writeMatrix(FileText, matrix);
	}
	FileText.close();
}

/*--------------------------------------------------------------------------------
	Публічний метод, який буде записувати кроки розв'язання СЛАР методом Крамера
  --------------------------------------------------------------------------------*/

void FileWork::writeStepOfCramer(int step, int i, std::vector<std::vector<double>> matrix, double det)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\nКрок №" << step << "\nЗнаходимо визначник матриці, в який замінили стовпець\n";
		FileText << "Ми замінили " << i + 1 << " стовбець відповідними вільними елементами і отримали матрицю:\n";
		writeMatrix(FileText, matrix);
		FileText << "\nЗнаходимо його визначник: " << det << '\n';
		FileText << "Ділимо цей визначник на загальний и отримуємо відповідний корінь\n";
	}
	FileText.close();
}

/*---------------------------------------------------------------------
	Публічний метод, який буде записувати результати розв'язання СЛАР 
  ---------------------------------------------------------------------*/

void FileWork::writeResults(std::vector<double> results)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\nРезультати:\n";
		for (int i = 0; i < results.size(); i++)
		{
			FileText << 'X' << i + 1 << " = " << round(results[i] * 100000) / 100000.0 << '\n';
		}
	}
	FileText.close();
}

/*-----------------------------------------------------------------------
	Публічний метод, який буде записувати статистику метода розв'язання
  -----------------------------------------------------------------------*/

void FileWork::writeStatistics(double workTime, int complexity)
{
	std::ofstream FileText(directory, std::ios_base::app);
	if (FileText.is_open())
	{
		FileText << "\n----------------------------";
		FileText << "\nСтатистика роботи алгоритма:\n";
		FileText << "Складність алгоритма: " << complexity << " ітерацій.\n";
		FileText << "Час виконання: " << workTime << " секунд.\n";
		FileText << "*************************************************************************************************************\n";
	}
	FileText.close();
}

/*--------------------------------------------------------
	Приватний метод, який буде записувати матрицю в файл
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