/*
Actividad Integradora 2: Alta demanda para los Proveedores de Servicios de Internet (ISP)
Autor: Samuel Alejandro Díaz del Guante Ochoa (A01637592)
Ultima actualizacion: 09/12/2021

Parte 1: Minimum spanning tree
    Para este problema se utilizo el "Algoritmo de Prim" que consiste en generar un arbol
    (un grafo completamente conectado sin ciclos) a partir de un grafo con la suma menor de sus
    arcos. Este algoritmo empieza en un nodo arbitrario generando un arbol y conectando nuevos
    nodos para crecer el arbol siempre escogiendo el arco vecino menos costoso.

Parte 2: Traveling salesman problem
    Para este problema se utilizo el algoritmo "Repetitve Nearest Neighbor" para encontrar el camino
    mas corto visitando todos los nodos una sola vez, sin repetir el mismo arco y siempre terminando
    el viaje en el nodo inicial. Este algoritmo emplea el algoritmo "Nearest Neighbor" en donde
    se elige un nodo inicial y se continua por el vertice vecino con arco menos costoso. Lo que hace
    RNN es ejecutar este procedimiento con todos los vertices como nodo inicial para determinar cual
    de todos genera el camino mas corto con las caracteristicas especificadas.

Parte 3: Flujo maximo
    Para este problema se utilizo el una variante del algoritmo de "Ford-Fulkerson" conocido como 
    "Edmonds-Karp" para calcular el flujo maximo en un grafo de un nodo fuente hasta un nodo terminal.
    Ambas implementaciones manejan conceptos similares como un grafo residual para el calculo del
    flujo maximo sin embargo "Edmonds-Karp" hace una busqueda en anchura (BFS) para recorrer el grafo
    por todas sus configuraciones con una complejidad computacional menor a la solucion tradicional de
    "Ford-Fulkerson".

Parte 4: Consultas de un punto en el diagrama de voronoi
    Para este problema se utilizaron metodos y estructuras encontradas en la geometria computacional 
    en este caso la principal siendo el "diagrama de voronoi". El diagrama de voronoi se genera en base 
    a una serie de puntos en el plano para generar geometrias denominadas "caras". El area de estas caras 
    contienen los puntos mas cercanos a los puntos con los que se genero el diagrama de voronoi. Este tipo 
    de implementacion es muy complejo por lo que se empleo la libreria de CGAL con la que se puede generar
    el diagrama de voronoi y hacer consultas de punto para determinar la central mas cercana a la nueva
    contratacion.

Entrada:
Parte 1: Un numero entero N que representa el número de colonias en la ciudad
Parte 2: Matriz cuadrada de N x N que representa el grafo con las distancias en kilómetros entre las colonias de la ciudad
Parte 3: Matriz cuadrada de N x N que representa las capacidades máximas de flujo de datos entre colonia i y colonia j
Parte 4: Lista de N pares ordenados de la forma (A,B) que representan la ubicación en un plano coordenado de las centrales

Salida:
Parte 1: Forma de cablear las colonias con fibra (lista de arcos de la forma (A,B))
Parte 2: Ruta a seguir por el personal que reparte correspondencia, considerando inicio y fin en al misma colonia.
Parte 3: Valor de flujo máximo de información del nodo inicial al nodo final
Parte 4: Lista de polígonos (cada elemento es una lista de puntos de la forma (x,y))
*/

// Standard includes
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <cassert>
// CGAL includes
// includes for defining the Voronoi diagram adaptor
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
// typedefs for defining the adaptor
typedef CGAL::Exact_predicates_inexact_constructions_kernel                  K;
typedef CGAL::Delaunay_triangulation_2<K>                                    DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT>                 AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT, AT, AP>                                    VD;
// typedef for the result type of the point location
typedef AT::Site_2                    Site_2;
typedef AT::Point_2                   Point_2;
typedef VD::Locate_result             Locate_result;
typedef VD::Vertex_handle             Vertex_handle;
typedef VD::Face_handle               Face_handle;
typedef VD::Halfedge_handle           Halfedge_handle;
typedef VD::Ccb_halfedge_circulator   Ccb_halfedge_circulator;

using namespace std;

/*
Function: Pass input from the file to a 2D array
Input: Size of the matrix (int), reference to a 2D array (vector<vector<int>>), text to parse (vector<string>)
Output: None
Time complexity: O(n^2)
*/
void createMatrix(int n, vector<vector<int>>& m, vector<string>& text)
{
    for (int i = 0; i < n; i++) {
        vector<int> v;
        for (int j = 0; j < n; j++) {
            v.push_back(stoi(text[0]));
            text.erase(text.begin());
        }
        m.push_back(v);
    }
}

/*
Function: Pass input from the file to a matrix that represents coordinates in a 2D plane
Input: Array of 2D coordinates (vector<vector<int>>), text to parse (vector<string>)
Output: None
Time complexity: O(n^2)
*/
void createCoor(vector<vector<int>>& coor, vector<string>& text)
{
    for (string pair : text) {
        int index = 0;
        string a, b;
        for (char c : pair) {
            if (c != '(' && c != ')') {
                if (c == ',') {
                    index++;
                    continue;
                }
                if (!index) {
                    a += c;
                }
                else {
                    b += c;
                }
            }
        }
        vector<int> tmp = {stoi(a), stoi(b)};
        coor.push_back(tmp);
    }
}

/*
Function: Process characters from text file into data structures
Input: Name of the file (string), number of neighborhoods (int), two 2D arrays (vector<vector<int>>)
Output: None
Time complexity: O(n^2)
*/
void processFile(string fileName, int& n, vector<vector<int>>& m1, vector<vector<int>>& m2, vector<vector<int>>& coor)
{
    fstream file(fileName);
    string line;
    vector<string> text;

    // Store values from text file in a list
    while (file >> line) {
        text.push_back(line);
    }
    
    // Assign N value
    n = stoi(text[0]);
    text.erase(text.begin());
    // Assign m1 values
    createMatrix(n, m1, text);
    // Assign m2 values
    createMatrix(n, m2, text);
    // Assign coor values
    createCoor(coor, text);
}

/*
Aux struct to store edge information for prim's algorithm
from: The vertex from which the edge is originated
to: The destination vertex
cost: The weight/cost of the edge
*/
struct primEdge
{
    int from;
    int to;
    int cost;

    // Struct constructor
    primEdge(int from, int to, int cost)
    {
        this->from = from;
        this->to = to;
        this->cost = cost;
    }
};

/*
Function: Aux function from mergeSort to sort the items in an array in ascending order of cost
Input: Array of edges (deque<primEdge>), array indexes (int)
Output: None
Time complexity: O(n)
*/
void merge(deque<primEdge>& originalArray, int first, int last, int middle) {
    int tmpArraySize = last - first + 1;
    deque<primEdge> tmpArray(tmpArraySize, primEdge(0, 0, 0));
    int firstIndex = first;
    int secondIndex = middle + 1;

    for (int i = 0; i < tmpArraySize; i++) {
        if (firstIndex <= middle && secondIndex <= last) {
            if (originalArray[firstIndex].cost < originalArray[secondIndex].cost) {
                tmpArray[i] = originalArray[firstIndex++];
            }
            else {
                tmpArray[i] = originalArray[secondIndex++];
            }
        }
        else if (firstIndex <= middle) {
            tmpArray[i] = originalArray[firstIndex++];
        }
        else if (secondIndex <= last) {
            tmpArray[i] = originalArray[secondIndex++];
        }
    }

    for (int i = 0; i < tmpArraySize; i++) {
        originalArray[first + i] = tmpArray[i];
    }

}

/*
Function: Recursive main function to perform a merge sort
Input: Array of edges (deque<primEdge>), array indexes (int)
Output: None
Time complexity: O(nlogn)
*/
void mergeSort(deque<primEdge>& originalArray, int first, int last) {
    if (first < last) {
        int middle = (last + first) / 2;
        // First half
        mergeSort(originalArray, first, middle);
        // Second half
        mergeSort(originalArray, middle + 1, last);
        // Merge
        merge(originalArray, first, last, middle);
    }
}

/*
Function: Aux function of prim's algorithm, it keeps the the priority queue updated and in ascending order
Input: Index from which the edge starts (int), priority queue that stores all unprocessed vertices (deque<primEdge>),
       array that keeps track of visited vertices (vector<bool>), adjacency matrix (vector<vector<int>>)
Output: None
Time complexity: O(n)
*/
void addEdges(int nodeIndex, deque<primEdge>& q, vector<bool> visited, vector<vector<int>> m)
{
    for (int i = 0; i < m.size(); i++) {
        // Add edges to the queue as longs as they are not visited and there is a edge between vertices
        if (!visited[i] && m[nodeIndex][i]) {
            q.push_back(primEdge(nodeIndex, i, m[nodeIndex][i]));
        }
    }
    // Sort array to accomodate new edges
    mergeSort(q, 0, q.size() - 1);
}

/*
Function: Print the edges in a (A,B) format
Input: Edges to form minimum spanning tree
Output: None
Time complexity: O(n)
*/
void printPrim(vector<primEdge> mst)
{
    for (int i = 0; i < mst.size(); i++) {
        cout << "(" << (char)('A' + mst[i].from) << "," << (char)('A' + mst[i].to) << ")" << endl;
    }
}

/*
Function: Implementation of Prim's Algorithm to find the minimum spanning tree from a connected graph
Input: Size of the matrix (int), adjacency matrix (vector<vector<int>>)
Output: None
Time complexity: O(V^2)
*/
void primAlgorithm(int n, vector<vector<int>> m)
{
    // Array of visited vertices
    vector<bool> visited(n, 0);
    // Array that stores the path of edges for the minumum spanning tree
    vector<primEdge> mst;
    // Priority to check edges and grow the size of the tree
    deque<primEdge> q;

    // In this instance the algorithm will always start from vertex 0
    visited[0] = 1;
    addEdges(0, q, visited, m);

    // Check all edges once to find the best mst
    while (!q.empty()) {
        primEdge node = q.front();
        q.pop_front();
        int nodeIndex = node.to;
        // Ignore edges that have a vertex that is already visited
        if (visited[nodeIndex]) {
            continue;
        }
        // Add edge to the list, mark it as visited and visit all the edges from a source vertex
        mst.push_back(node);
        visited[nodeIndex] = 1;
        addEdges(nodeIndex, q, visited, m);
    }

    // Print the edges in a (A,B) format
    printPrim(mst);

}

/*
Aux struct for repetitive nearest neighbor algorithm
path: Stores the order in which the each neighborhood needs to be visited
pathLen: Total cost/distance from the visited vertices
*/
struct rnn
{
    vector<int> path;
    int pathLen = INT_MAX;
};

/*
Function: Prints path using the alphabet (A=0, B=1, C=2...)
Input: Shortest path calculated by RNN algorithm (vector<int>)
Output: None
Time complexity: O(n)
*/
void printRNN(vector<int> v)
{
    for (int c : v) {
        cout << (char)('A' + c) << " ";
    }
    cout << endl;
}

/*
Function: Core part of the RNN, it is a greedy algorithm that chooses the shortest path in proximity from a starting vertex
Input: Index of vertex to start the algorithm (int), adjacency matrix (vector<vector<int>>)
Output: Object from struct rnn that contains the calculated path and total cost to visit every vertex and return to the start
Time complexity: O(n^2)
*/
rnn nearestNeighbor(int initialVertex, vector<vector<int>> m)
{
    int len = m.size();
    // Visited array to avoid already added verteces and cicles
    vector<bool> visited(len, 0);
    // Stores shortest path for this instance
    vector<int> path;
    // Start process from the initialVertex
    int curr = initialVertex;
    int pathLen = 0;
    path.push_back(curr);
    visited[curr] = 1;

    // Add every single vertex to the path at some point
    for (int i = 0; i < len; i++) {
        int minDist = INT_MAX;
        int pos = 0;
        // Search for the nearest vertex that has not been added yet
        for (int j = 0; j < len; j++) {
            if (m[curr][j] < minDist && m[curr][j] > 0 && !visited[j]) {
                minDist = m[curr][j];
                pos = j;
            }
        }
        // For every other loop when next nearest neighbor is found
        if (minDist != INT_MAX) {
            // Add total distance and vertex to the path
            pathLen += minDist;
            curr = pos;
            visited[curr] = 1;
            path.push_back(curr);
        }
        // For the last loop when all vertices had been visited
        else {
            // Return to the initial vertex
            path.push_back(initialVertex);
            pathLen += m[curr][initialVertex];
        }
    }

    // Return the calculated path and total distance
    rnn p;
    p.path = path;
    p.pathLen = pathLen;
    return p;
}

/*
Function: Main RNN function that compares multiple instances of nearest neighbor starting from a 
          different node each time and chooses the best shortest path it could find
Input: Size of the matrix (int), adjacency matrix (vector<vector<int>>)
Output: None
Time complexity: O(n^3)
*/
void repetitiveNearestNeighbor(int n, vector<vector<int>> m)
{
    // Stores best path found by RNN
    rnn bestAnswer;
    // Iterate over every vertex as an starting point
    for (int i = 0; i < n; i++) {
        rnn newAnswer = nearestNeighbor(i, m);
        // Choose the one with the lowest cost/distance
        if (newAnswer.pathLen < bestAnswer.pathLen) {
            bestAnswer = newAnswer;
        }
    }
    // Print best path found
    printRNN(bestAnswer.path);
}

/*
Function: Aux Ford-Fulkerson function to calculate the maximum flow through various paths, this is used
          in the Edmonds-Karp version of the algorithm
Input: Start and sink index of the graph (int), residual graph (vector<vector<int>>), reference to parent array (vector<vector<int>>)
Output: Condition to terminate or continue algorithm
Time complexity: O(V^2)
*/
bool bfs(int start, int sink, vector<vector<int>> residualGraph, vector<int>& parent)
{
    int len = residualGraph.size();
    // Array to mark all visited vertices
    vector<bool> visited(len, 0);
    // Start by adding the start vertex to the queue
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    parent[start] = -1;

    // Start BFS looping
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        for (int i = 0; i < len; i++) {
            // Mark vertices where there is a valid edge for it to reach the sink
            if (!visited[i] && residualGraph[vertex][i] > 0) {
                q.push(i);
                visited[i] = 1;
                parent[i] = vertex;
            }
        }
    }
    // Return true if the sink is reachable from the start, otherwise return false
    return (visited[sink] == 1);
}

/*
Function: Main Ford-Fulkerson function to find the maximum flow from a starting vertex to a sink vertex
Input: Start and sink index of the graph (int), adjacency matrix (vector<vector<int>>)
Output: None
Time complexity: O(EV^3)
*/
void fordFulkerson(int start, int sink, vector<vector<int>> m)
{
    int len = m.size();
    // Residual graph that starts with the capacities of the original graph
    vector<vector<int>> residualGraph = m;
    // Array to store the path calculated by the BFS
    vector<int> parent(len);
    int maxFlow = 0;
    int u, v;

    // Continue while there is a path to reach the sink from the start
    while (bfs(start, sink, residualGraph, parent)) {
        int pathFlow = INT_MAX;
        // Find the maximum flow through the path found
        v = sink;
        while (v != start) {
            u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
            v = parent[v];
        }
        // Update residual capacities of the edges
        v = sink;
        while (v != start) {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
            v = parent[v];
        }
        // Increase the maximum flow from current iteration of the path flow
        maxFlow += pathFlow;
    }
    // Display the maximum flow from this start and sink
    cout << maxFlow << endl;
}

/*
Function: Function to produce Voronoi diagram and find it's closest point to the query point
Input: Coordinates for the query point location query and Voronoi diagram (vector<vector<int>>)
Output: None
Time complexity: O(n * CGAL implementation)
*/
void voronoiQuery(vector<vector<int>> coor)
{
    // Voronoi diagram
    VD vd;
    // Query point
    Point_2 query(coor[0][0], coor[0][1]);

    // Create voronoi diagram
    for (int i = 1; i < coor.size(); i++) {
        Site_2 t(coor[i][0], coor[i][1]);
        vd.insert(t);
    }

    // Determine the closest central to the query point
    int count = 1;
    Locate_result qLocation = vd.locate(query);

    for (int i = 1; i < coor.size(); i++) {
        Point_2 center(coor[i][0], coor[i][1]);
        Locate_result cLocation = vd.locate(center);
        if (qLocation == cLocation) {
            break;
        }
        // Check if the query point lands on a vertex or edge
        Face_handle* face = boost::get<Face_handle>(&cLocation);
        if (Vertex_handle* v = boost::get<Vertex_handle>(&qLocation)) {
            if ((*v)->is_incident_face(*face)) { break; }
        }
        else if (Halfedge_handle* e = boost::get<Halfedge_handle>(&qLocation)) {
            if ((*face)->is_halfedge_on_ccb(*e)) { break; }
        }
        count++;
    }

    // Display nearest central to query point
    cout << "C" << count << " " << "(" << coor[count][0] << "," << coor[count][1] << ")" << endl;

}

int main()
{
    // Number of colonies
    int n;
    // Matrix or first and second part
    vector<vector<int>> m1;
    // Matrix or third part
    vector<vector<int>> m2;
    // Matrix for fourth part
    vector<vector<int>> coor;


    processFile("test.txt", n, m1, m2, coor);
 
    // Part 1: Minimum spanning tree
    cout << "Forma optima de cablear y unir cuales quiera dos colonias:" << endl;
    primAlgorithm(n, m1);
    cout << endl;
    // Part 2: Traveling salesman problem
    cout << "Ruta optima a seguir por el personal para visitar todas las colonias:" << endl;
    repetitiveNearestNeighbor(n,m1);
    cout << endl;
    // Part 3: Maximum flow
    cout << "Flujo maximo de informacion del nodo inicial al nodo final:" << endl;
    fordFulkerson(0,n-1,m2);
    cout << endl;
    // Part 4: Voronoi diagram point location queries
    cout << "Central mas cercana a la nueva contratacion:" << endl;
    voronoiQuery(coor);
    cout << endl;

    return 0;
}