/*/
Header de la clase "MyGraph"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 05/11/2020
Fecha de modificacion: 09/11/2020
/*/

#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class MyGraph
{
    private:
        vector<vector<int> > matriz;
        void DFS(int v, vector<bool>& status);

    public:
        MyGraph(vector<vector<int> >& matriz);
        void loadGraph(vector<vector<int> >& matriz);
        void DFS();
        void BFS();
};

#endif
