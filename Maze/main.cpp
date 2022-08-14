/*
Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"
Authors: Samuel Alejandro Díaz del Guante (A01637592) y Roberto López Cisneros (A01637335)
Last update: September 2, 2021

Laberinto
Descripcion: Código que resuelve el laberinto de dos maneras,
  por medio de "backtracking" y "ramificación y poda"
-Complejidad de algoritmo backtracking: O(2^(mn))
-Complejidad de algoritmo branch and bound: O(mn)

Input: Numero renglones matriz (m), seguido del numero de columnas matriz (n),
  seguido de m lineas de n valores booleanos (0|1) separados por espacio, 
  por la entrada estándar que representan el laberinto.  
  Un 1 representa una casilla en la que es posible moverse, 
  un 0 es una casilla por la que NO se puede pasar.
Output: Matriz de valores booleanos (0|1) que representan el camino para salir del laberinto. 
  Primero utilizando la técnica de backtracking.
  Segundo utilizando la técnica de ramificación y poda.

Instrucción ejecución:
> g++ main.cpp -o <exe file>
> <exe file> < <txt_file>

Ejemplo ejecución:
> g++ main.cpp -o maze.exe
> maze.exe < caso_prueba_1.txt
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Estructura de un nodo
struct Node{
    int x;
    int y;
    string direction;
};

/*
Funcion: Imprime de forma legible matriz de tipo char 
Entrada: Vector de vectores de tipo char 
Salida: Ninguna
Complejidad: O(n*m)
*/
void printMatrix(vector<vector<char>> matrix){
    for(int i = 0; i < matrix.size(); i++){
      for(int j = 0; j < matrix[0].size(); j++){
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
}

/*
Funcion: Funcion auxiliar a "Branch and Bround"; distribuye el camino correcto
en forma de matriz
Entrada: Un string con las direcciones para resolver el laberinto y una matriz
de caracteres que va a representar la solucion del laberinto
Salida: Ninguna
Complejidad: O(m*n)
*/
void mapPath(string directions, vector<vector<char>> path)
{
    int i = 0;
    int j = 0;
    path[i][j] = '1';

    for(char& c : directions) {
        if(c == 'R'){ j++; }
        if(c == 'D'){ i++; }
        if(c == 'L'){ j--; }
        if(c == 'U'){ i--; }
        path[i][j] = '1';
    }

    printMatrix(path);
}

/*
Funcion: Resuelve laberinto en forma similar al BFS
Entrada: Laberinto en vector de vectores de tipo char
Salida: Un booleano para saber si existe una solucion al laberinto procesadool si hay camino o no
Complejidad: O(m*n)
*/
bool branchAndBound(vector<vector<char>> maze)
{
    vector<vector<char>> visited(maze.size(), vector<char>(maze[0].size(), '0'));
    vector<vector<char>> path(maze.size(), vector<char>(maze[0].size(), '0'));

    queue<Node> q;
    Node firstNode = {0,0,""};
    q.push(firstNode);

    while(!q.empty()){

        Node curr = q.front();

        if(curr.x == maze.size()-1 && curr.y == maze[0].size()-1){
            mapPath(curr.direction, path);
            return true;
        }

        q.pop();

        // Right
        if(curr.y+1 < maze[0].size() && maze[curr.x][curr.y+1] == '1' && visited[curr.x][curr.y+1] == '0'){
            visited[curr.x][curr.y+1] = '1';
            string dir = curr.direction + "R";
            Node newNode = {curr.x,curr.y+1,dir};
            q.push(newNode);
        }
        // Down
        if(curr.x+1 < maze.size() && maze[curr.x+1][curr.y] == '1' && visited[curr.x+1][curr.y] == '0'){
            visited[curr.x+1][curr.y] = '1';
            string dir = curr.direction + "D";
            Node newNode = {curr.x+1,curr.y,dir};
            q.push(newNode);
        }
        // Left
        if(curr.y-1 >= 0 && maze[curr.x][curr.y-1] == '1' && visited[curr.x][curr.y-1] == '0'){
            visited[curr.x][curr.y-1] = '1';
            string dir = curr.direction + "L";
            Node newNode = {curr.x,curr.y-1,dir};
            q.push(newNode);
        }
        // Up
        if(curr.x-1 >= 0 && maze[curr.x-1][curr.y] == '1' && visited[curr.x-1][curr.y] == '0'){
            visited[curr.x-1][curr.y] = '1';
            string dir = curr.direction + "U";
            Node newNode = {curr.x-1,curr.y,dir};
            q.push(newNode);
        }

    }

    return 0;
}

/*
Funcion: Resuelve laberinto en forma similar al DFS recursivo
Entrada: dos enteros que representar las coordenadas en el plano, dos matrices de
caracteres que representan el laberinto y el camnio solucion respectivamente y una
matriz de valores booleanos para llevar registro de las casillas ya visitadas
Salida: Un booleano para saber si existe una solucion al laberinto procesado
Complejidad: O(2^(m*n)) 
*/
bool backtracking(int i, int j, vector<vector<char>> maze, vector<vector<char>> &path, vector<vector<bool>> &visited)
{
    if(i == maze.size()-1 && j == maze[0].size()-1){
        path[i][j] = '1';
        return 1;
    }

    if(maze[i][j] == '1' && !visited[i][j]){
        path[i][j] = '1';
        visited[i][j] = 1;
        //Right
        if (j<maze[0].size()-1){
          if(backtracking(i,j+1,maze,path, visited) == 1){
              return 1;
          }
        }
        // Down
        if(i<maze.size()-1){
          if(backtracking(i+1,j,maze,path, visited) == 1){
            return 1;
          }
        }
        // Up
        if (i>0){
          if(backtracking(i-1,j,maze,path, visited) == 1){
            return 1;
          }
        }
        // Left
        if (j>0){
          if(backtracking(i,j-1,maze,path, visited) == 1){
            return 1;
          }
        }
        path[i][j] = '0';
    }
    return 0;
}

int main() {
  // Inicializar variables
  int m;
  int n;
  string line;

  // Input
  cin >> m; // Lineas
  cin >> n; // Columnas

  // Check if matrix dimensions (m,n) are greater than 0
  if(m <= 0 || n <= 0){
    cout << "m and n must be greater than 0" << endl;
    return 0;
  }

  // Inicializar arreglo
  vector<vector<char>> maze(m, vector<char>(n, '0'));

  // Input arreglo para laberinto
  cin.get();
  for(int i = 0; i < m; i++){
    getline(cin, line);
    int j = 0;
    for(char& c : line){
      if(c != ' ' && j < n) {
        maze[i][j] = c;
        j++;
      }
    }
  }

  // Backtracking
  vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), 0));
  vector<vector<char>> path(m, vector<char>(n, '0'));
  bool flag = backtracking(0,0,maze,path,visited);
  // Check if there is a valid solution
  cout << "Backtracking:" << endl;
  if (flag) {
    printMatrix(path);
  } else {
    cout << "There is no direct path to the exit" << endl;
  }

  // Branch and bound
  cout << "Branch and bound:" << endl;
  if(!branchAndBound(maze)){
    cout << "There is no direct path to the exit" << endl;
  }

  return 0;
}