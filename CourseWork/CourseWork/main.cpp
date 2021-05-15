#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "Cramer.h"
using namespace std;

template <typename T>
void input(string str, T* a)
{
    cout << str;
    cin >> *a;
}

void graph_inicial(vector<vector<float>>&);
void random_inicial(vector<vector<float>>&);
void manual_inicial(vector<vector<float>>&);
void graph_out(vector<vector<float>>&);

int main()
{
    srand(time(NULL));
    vector<vector<float>> matrix(5, vector<float>(5));
    vector<float> var(5);
    vector<float> solved(5);
    for (int i = 0; i < 5; i++)
    {
        var[i] = rand() % 9 + 1;
    }
    graph_inicial(matrix);
    Cramer system(matrix, var);
    solved = system.solve();
    for (int i = 0; i < 5; i++)
    {
        cout << endl << "var " << i << " " << var[i];
    }
    for (int i = 0; i < 5; i++)
    {
        cout << endl << "Amswer " << i << " "<< solved[i];
    }
}

void graph_inicial(vector<vector<float>> &graph)
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

void random_inicial(vector<vector<float>> &graph)
{
    for (int i = 0; i < 5; i++) //Генерування іншої частини графу.
    {
        for (int j = 0; j < 5; j++)
        {
            graph[i][j] = rand() % 9 + 1;
        }
    }
}

/*Генерування графу власноруч.*/

void manual_inicial(vector<vector<float>> &graph)
{
    for (int i = 0; i < 5; i++) //Для кожної вершини вказуємо зв'язки.
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

void graph_out(vector<vector<float>> &graph)
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
