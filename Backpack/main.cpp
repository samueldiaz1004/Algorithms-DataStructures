/*
Actividad 3.3 Implementación de "Knapsack problem"
Authors: Samuel Alejandro Díaz del Guante (A01637592) y Roberto López Cisneros (A01637335)
Last update: October 7, 2021

0/1 Knapsack 
Descripcion: 
  Código que resuelve el problema de la mochila, y en que se muestra la ganancia óptima
-Complejidad de algoritmo Knapsack: O(n*w)
Donde "n" es el numero de elementos y "w" es el peso maximo de la mochila

Input: 
  Primera linea: Entero "n" que representa el número de elementos posibles disponibles
  Seguido "n" lineas: Enteros que representan el valor de cada uno de esos elementos.
  Seguido "n" lineas: Enteros que representan los pesos asociados a cada elemento.
  Ultima linea: Entero "w" que representa el peso máximo o capacidad de la mochila.
Output: 
  Entero que representa la ganancia (o beneficio) óptimo

Instrucción ejecución:
> g++ main.cpp -o <exe file>
> <exe file> < <txt_file>

Ejemplo ejecución:
> g++ main.cpp -o knapsack.exe
> knapsack.exe < caso_prueba_1.txt
*/

#include <iostream>

using namespace std;

/*
Estructura: Estructura de un nodo para representar cada elemento con su valor y peso
*/
struct node{
    int value;
    int weight;
};

/*
Funcion: Auxiliar del mergeSort que permite mezclar ordenadamente dos mitades
Entrada: Array de tipo node
  Enteros de la posicion inicial, final y media del arreglo respectivamente
Salida: Nada
Complejidad: O(n)
*/
void merge(node originalArray[], int first, int last, int middle) {
    int tmpArraySize = last - first + 1;
    node tmpArray[tmpArraySize];
    int firstIndex = first;
    int secondIndex = middle+1;

    for(int i = 0; i < tmpArraySize; i++){
        if (firstIndex <= middle && secondIndex <= last) {
            if(originalArray[firstIndex].weight < originalArray[secondIndex].weight){
                tmpArray[i] = originalArray[firstIndex++];
            } else {
                tmpArray[i] = originalArray[secondIndex++];
            }
        } else if (firstIndex <= middle) {
            tmpArray[i] = originalArray[firstIndex++];
        } else if (secondIndex <= last) {
            tmpArray[i] = originalArray[secondIndex++];
        }
    }

    for(int i = 0; i < tmpArraySize; i++) {
        originalArray[first+i] = tmpArray[i];
    }
}

/*
Funcion: Funcion que permite ordenar un arreglo de una manera eficiente conforme a los pesos
Entrada: Array de tipo node
  Enteros de la posicion inicial, y final del arreglo respectivamente
Salida: Nada
Complejidad: O(nlogn)
*/
void mergeSort(node originalArray[], int first, int last) {
    if (first < last) {
        int middle = (last+first) / 2;
        mergeSort(originalArray, first, middle);
        mergeSort(originalArray, middle+1, last);
        merge(originalArray, first, last, middle);
    }
}

/*
Funcion: Funcion Knapsack que nos ayuda a obtener el beneficio optimo.
Entrada: Array de tipo node
  Enteros de la cantidad de elementos y peso maximo respectivamente
Salida: Nada
Complejidad: O(n*w)
*/
void knapsack(node items[], int n, int w){
  // Matriz auxiliar necesaria para programacion dinamica
  int m[n+1][w+1]; // Añadir una columna y fila extra

  // Inicilizar primera fila en 0
  for(int i=0; i<=n; i++){
    m[i][0] = 0;
  }

  // Inicilizar primera columna en 0
  for(int i=0; i<=w; i++){
    m[0][i] = 0;
  }

  // Recorrer toda la matriz desde m[1][1]
  for(int i=0; i<=n; i++){
    for(int j=0; j<=w; j++){
      // Ignorar primera fila y columna
      if (i==0 || w==0){
        continue;
      }
      // Revisar que el item actual sea menor o igual al peso a comparar
      else if (items[i-1].weight <= j) { 
        // Revisar que la suma sea de mayor valor que el default
        if (items[i-1].value + m[i-1][j-items[i-1].weight] > m[i-1][j]){
          m[i][j] = items[i-1].value + m[i-1][j-items[i-1].weight];
        }
        // Default: poner el valor de la celda superior a la actual
        else{
          m[i][j] = m[i-1][j];
        }
      }
      // Default: poner el valor de la celda superior a la actual
      else{
        m[i][j] = m[i-1][j];
      }
    }
  }

  // Ganancia optima
  cout << m[n][w] << endl;

}

int main() {
  
  // Inicilizar variables inputs
  int n, w; // Numero de elementos y peso maximo
  cin >> n;

  int weights[n];
  int values[n];
  node items[n];

  // Recibir inputs de "n" valores
  for(int i = 0; i < n; i++){
      int val;
      cin >> val;
      values[i] = val;
  }

  // Recibir inputs de "n" pesos
  for(int i = 0; i < n; i++){
      int weight;
      cin >> weight;
      weights[i] = weight;
  }

  // LLenar arreglo de nodos con el valor y peso de cada elemento
  for(int i = 0; i < n; i++){
      node item;
      item.value = values[i];
      item.weight = weights[i];
      items[i] = item;
  }

  // Input de peso maximo
  cin >> w;

  // Ordenar arreglo de nodos conforme a los pesos de cada nodo
  mergeSort(items,0,n-1);

  // Calcular con knapsack
  knapsack(items, n, w);

  return 0;
}