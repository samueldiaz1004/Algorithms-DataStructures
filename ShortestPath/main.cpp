/*
Actividad 3.2 Implementación de "Dijkstra and Floyd"
Authors: Samuel Alejandro Díaz del Guante (A01637592) y Roberto López Cisneros (A01637335)
Last update: September 30, 2021

Shortest Path
Descripcion: Código que encuentra la distancia más corta entre parejas de nodos 
  en un grafo dirigido por medio de "Dijkstra" y "Floyd"
-Complejidad de algoritmo Dijkstra: O(n^3) porque pasa por todos los nodos como origen
-Complejidad de algoritmo Floyd: O(n^3)

Input: Un numero n seguido de n x n valores enteros no negativos 
  que representan una matriz de adyacencias de un grafo dirigido.
  El primer número representa el número de nodos, los valores en la matriz representan
  el peso del arco del nodo i al nodo j. Si no hay un arco entre el nodo i y el nodo j,
  el valor en la matriz debe ser -1
Output: 
  Primero con el algoritmo de Dijkstra la distancia del nodo i al nodo j para todos los nodos.
  Segundo la matriz resultado del algoritmo de Floyd.

Instrucción ejecución:
> g++ main.cpp -o <exe file>
> <exe file> < <txt_file>

Ejemplo ejecución:
> g++ main.cpp -o path.exe
> path.exe < caso_prueba_1.txt
*/

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/*
Funcion: Convierte los valores "-1" de una matriz al valor maximo de un numero int
Entrada: Vector de vectores de tipo int
Salida: Vector de vectores de tipo int transformados
Complejidad: O(n^2)
*/
vector<vector<int>> transformMatrix(vector<vector<int>> m){
  for(int i = 0; i < m.size(); i++){
    for(int j = 0; j < m[0].size(); j++){
      if(m[i][j] == -1){
        m[i][j] = numeric_limits<int>::max();
      }
    }
  }
  return m;
}

/*
Funcion: Imprime la matriz resultante del algoritmo Floyd
Entrada: Vector de vectores de tipo int
Salida: Nada
Complejidad: O(n^2)
*/
void printFloyd(vector<vector<int>> matrix){
  for(int i = 0; i < matrix.size(); i++){
    for(int j = 0; j < matrix[0].size(); j++){
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

/*
Funcion: Imprime la distancia de un nodo a los demas nodos.
Entrada: Vector de tipo int representando distancia, y un numero entero del nodo origen
Salida: Nada
Complejidad: O(n)
*/
void printDijkstra(vector<int> dist, int s){
  for(int i = 0; i < dist.size(); i++){
    // No mostrar el resultado de un nodo a si mismo (en estos casos siempre es 0)
    if(s != i){
      cout << "node " << s+1 << " to node " << i+1 << ": ";
      // Cambiar el formato de impresion donde no hay arcos a como aparece en el input
      if(dist[i] != numeric_limits<int>::max()){
         cout << dist[i];
      }
      else{
        cout << -1;
      }
      cout << endl;
    }
  }
}

/*
Funcion: Funcion auxiliar del dijkstra que encuentra nodo con valor distancia minima
Entrada: Vector de tipo int representando distancia, 
  y vector de tipo bool representando los nodos visitados
Salida: Numero entero de posicion del nodo con valor de distancia minima
Complejidad: O(n)
*/
int minDist(vector<int> dist, vector<bool> visited){
  int min = numeric_limits<int>::max();
  int minIndex;
  
  for(int i = 0; i < dist.size(); i++){
    // Excluir nodos ya visitados y procesados y escoger el de menor valor
    if(visited[i]==false && dist[i]<=min){
      min = dist[i];
      minIndex = i;
    }
  }
  return minIndex;
}

/*
Funcion: Algoritmo Djikstra que permite conocer el camino corto de un nodo a otros nodos.
Entrada: Vector de tipo int representando matriz, 
  y numero entero del nodo origen
Salida: Nada
Complejidad: O(n^2)
*/
void dijkstra(vector<vector<int>> m, int s){
  int n = m.size();

  vector<bool> visited (n, 0);
  vector<int> dist (n, numeric_limits<int>::max());
  
  // Empezar algoritmo con el nodo fuente
  dist[s] = 0;

  for(int i = 0; i < n-1; i++){
    // Obtener el indice del arco con menor distancia
    int u = minDist(dist, visited);
    visited[u] = 1;

    for (int vertex = 0; vertex<n;  vertex++){
      // Actualizar arreglo de distancia minima
      if (!visited[vertex] 
        && m[u][vertex] 
        && dist[u] != numeric_limits<int>::max()
        && m[u][vertex] != numeric_limits<int>::max()
        && dist[u]+m[u][vertex] < dist[vertex]){
          dist[vertex] = dist[u] + m[u][vertex];
        }
    }
  }

  printDijkstra(dist, s);

}

/*
Funcion: Djikstra que permite conocer el camino corto de cada nodo a otros nodos.
Entrada: Vector de tipo int representando matriz, 
  y numero entero del size de la matriz
Salida: Nada
Complejidad: O(n^3)
*/
void initializeDijkstra(vector<vector<int>> m, int n) {
  for (int i=0; i<n; i++) {
    dijkstra(m, i);
  }
}

/*
Funcion: Floy que permite conocer el camino corto entre pares de nodos
Entrada: Vector de tipo int representando matriz
Salida: Nada
Complejidad: O(n^3)
*/
void floyd(vector<vector<int>> m){
    int n = m.size();
    // Copia de la matriz de adyacencia del grafo original
    vector<vector<int>> dist = m;

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                // Actualizar matriz de distancia minima
                if ((dist[i][j] > (dist[i][k] + dist[k][j])
                    && dist[k][j] != -1
                    && dist[i][k] != -1)
                    || ((dist[i][j] == -1) 
                    && (dist[k][j] != -1) 
                    && dist[i][k] != -1)){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printFloyd(dist);
}

int main() {
  // Inicializar variables
  int n;
  cin >> n;
  vector<vector<int>> matriz;

  // Input para matriz
  for(int i = 0; i < n; i++){
    vector<int> nodo;
    int value;
    for(int j = 0; j < n; j++){
      cin >> value;
      nodo.push_back(value);
    }
    matriz.push_back(nodo);
  }

  cout << endl;

  //Dijkstra
  cout << "Dijkstra: " << endl;
  vector<vector<int>> mTransform = transformMatrix(matriz);
  initializeDijkstra(mTransform, n);

  cout << endl;

  //Floyd
  cout << "Floyd: " << endl;
  floyd(matriz);
  
  return 0;
}