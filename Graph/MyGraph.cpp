/*/
Implementacion de la clase "MyGraph"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 05/11/2020
Fecha de modificacion: 09/11/2020
/*/

#include "MyGraph.h"

// Constructor
MyGraph::MyGraph(vector<vector<int> >& matriz)
{
    // Llama al metodo loadGraph para copiar la matriz
    // de adyacencia al atributo del objeto
    loadGraph(matriz);
}

// Metodo para cargar grafo al atributo del objeto
// Recibe la referencia de un vector de vectores enteros
// No regresa algun valor
// Complejidad computacional: O(1)
void MyGraph::loadGraph(vector<vector<int> >& matriz)
{
    this->matriz = matriz;
}

// Metodo de recorrido "Depth First Search"
// Recibe como paramentros un vertice y una vector de booleanos como referencia (visitados)
// No regresa algun valor
// Complejidad computacional: O(n^2)
void MyGraph::DFS(int v, vector<bool>& status)
{
    // Imprimir vertice actual
    cout << v << ",";
    // Cambiar su estado a visitado
    status[v] = true;
    // Recorrer el resto del arreglo donde se encuentra el vertice
    for(int i = 0; i < this->matriz.size(); i++) {
        // Si existe el un arco y no ha sido visitado
        if(matriz[v][i] && (!status[i])){
            // Se llama recursivamente la funcion hasta que todos
            // los veertices esten visitados
            DFS(i,status);
        }
    }
}

// Metodo de preparacion para "Depth First Search"
// No recibe ni regresa algun valor
// El nodo de matriz[0] es considerado como nodo inicial
// Complejidad computacional (todos los casos): O(n^2)
void MyGraph::DFS()
{
    // Inicializar valores para metodo principal
    int len = this->matriz.size();
    vector<bool> status(len,false);
    // Llamar metodo recursivo
    DFS(this->matriz[0][0], status);
    cout << endl;
}

// Metodo de recorrido "Breadth First Search"
// No recibe ni regresa algun valor
// El nodo de matriz[0] es considerado como nodo inicial
// Complejidad computacional (todos los casos): O(n^2)
void MyGraph::BFS()
{
    // Tamaño de un lado de la matriz
    int len = this->matriz.size();
    // Vector tipo bandera que almacena el estado del nodo,
    // visitado o no visitado
    vector<bool> status(len,false);
    // Fila auxiliar para procesar los datos
    queue<int> fila;
    // Variable auxiliar para procesar los daros
    int data;

    // Recorrer por lo menos el vector de vectores
    for(int i = 0; i < len; i++){
        // Si el nodo actual no ha sido visitado, se procesa
        if(!status[i]){
            // Se agrega a la fila
            fila.push(i);
            // Se marca su estado como visitado
            status[i] = true;
            // Mientras la pila tenga por lo menos un elemento...
            while(!fila.empty()){
                // Se guarda el elemento mas antiguo de la fila en una variable
                data = fila.front();
                // Se elimina dicho elemento de la fila
                fila.pop();
                // Se imprime el elemento
                cout << data << ",";
                // Se recorre el vector de enteros actual
                for(int j = 0; j < len; j++){
                    // Y si el dato es diferente a cero (existe una conexion) y
                    // no ha sido visitado antes
                    if(this->matriz[data][j] && !status[j]){
                        // Entonces se agrega a la fila
                        fila.push(j);
                        // Se cambia el estado del nodo a visitado
                        status[j] = true;
                    }
                }
            }
        }
    }
    cout << endl;
}
