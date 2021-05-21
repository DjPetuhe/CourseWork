#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "Cramer.h"
#include "GaussDiagonal.h"
#include "GaussMainElement.h"
using namespace std;

template <typename T>
void input(string str, T* a)
{
    cout << str;
    cin >> *a;
}

void graph_inicial(vector<vector<double> >&);
void random_inicial(vector<vector<double> >&);
void manual_inicial(vector<vector<double> >&);
void graph_out(vector<vector<double> >&);

int main()
{
    srand(time(NULL));
    vector<vector<double> > matrix(6, vector<double>(6));
    vector<double> var(6);
    vector<double> solved(6);
    for (int i = 0; i < 6; i++)
    {
        var[i] = rand() % 9 + 1;
    }
    graph_inicial(matrix);
    vector<vector<double> > matrix2 = matrix;
    vector<vector<double> > matrix3 = matrix;
    vector<double> var2 = var;
    vector<double> var3 = var;
    vector<double> solved2(6);
    vector<double> solved3(6);
    Cramer system(matrix, var);
    GaussDiagonal system2(matrix2,var2);
    GaussMainElement system3(matrix3, var3);
    solved = system.solve();
    solved2 = system2.solve();
    solved3 = system3.solve();
    cout << endl << "CRAMAR: " << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << endl << "var " << i << " " << var[i];
    }
    for (int i = 0; i < solved.size(); i++)
    {
        cout << endl << "Amswer " << i << " "<< round(solved[i] * 100000)/100000.0;
    }
    cout << endl << "GaussDiag: " << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << endl << "var2 " << i << " " << var2[i];
    }
    for (int i = 0; i < solved2.size(); i++)
    {
        cout << endl << "Amswer2 " << i << " " << round(solved2[i] * 100000) / 100000.0;
    }
    cout << endl << "GaussMain: " << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << endl << "var3 " << i << " " << var3[i];
    }
    for (int i = 0; i < solved3.size(); i++)
    {
        cout << endl << "Amswer3 " << i << " " << round(solved3[i] * 100000) / 100000.0;
    }
}

void graph_inicial(vector<vector<double> > &graph)
{
    bool random;
    input("Do you want your graph to be randomly generated?\n(1 - yes, 0 - no): ", &random);
    if (random)
    {
        random_inicial(graph);
    }
    else
    {
        manual_inicial(graph);
    }
    cout << "Current graph: " << endl;
    graph_out(graph);
}

/*Ініціалізація графа випадковим чином.*/

void random_inicial(vector<vector<double> > &graph)
{
    for (int i = 0; i < 6; i++) //Генерування іншої частини графу.
    {
        for (int j = 0; j < 6; j++)
        {
            graph[i][j] = rand() % 9 + 1;
        }
    }
}

/*Генерування графу власноруч.*/

void manual_inicial(vector<vector<double> > &graph)
{
    for (int i = 0; i < 6; i++) //Для кожної вершини вказуємо зв'язки.
    {
        cout << "Enter vertices that have a common edge with " << i + 1 << " vertex:" << endl;
        for (int j = 0; j < graph.size(); j++)
        {
            cout << j + 1 << ": ";
            int vertice;
            cin >> vertice;
            graph[i][j] = vertice;
        }
    }
}

/*Функція, яка виводить матрицю суміжності графа.*/

void graph_out(vector<vector<double> > &graph)
{
    cout << "    ";
    for (int i = 0; i < graph.size(); i++)
    {
        cout << setw(3) << i + 1;
    }
    cout << endl
        << "    ";
    for (int i = 0; i < graph.size(); i++)
    {
        cout << "---";
    }
    cout << endl;
    for (int i = 0; i < graph.size(); i++)
    {
        cout << setw(2) << i + 1 << " |";
        for (int j = 0; j < graph.size(); j++)
        {
            cout << setw(3) << graph[i][j];
        }
        cout << endl;
    }
}
