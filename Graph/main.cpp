/*/
Act 4.1

Representacion de un grafo en una matriz de adyacencia y
sus recorridos por profundidad y anchura.

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 05/11/2020
Fecha de modificacion: 09/11/2020
/*/

#include <iostream>
#include "MyGraph.h"
using namespace std;

int main()
{
    // Caso 1
    vector<vector<int> > m{
        {0,1,1,1,1,0,0,0,0},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
        };
    MyGraph g(m);
    g.DFS();
    g.BFS();
    cout << endl;

    // Caso 2
    m = {
        {0,1,1,1,1},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        };
    g.loadGraph(m);
    g.DFS();
    g.BFS();
    cout << endl;

    // Caso 3
    m = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 0},
        {0, 1, 0, 0}
        };
    g.loadGraph(m);
    g.DFS();
    g.BFS();

    return 0;
}
