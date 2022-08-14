/*
Actividad 1.2 Implementación de la técnica de programación "Programación dinámica" y "algoritmos avaros"
Authors: Samuel Alejandro Díaz del Guante (A01637592) y Roberto López Cisneros (A01637335)
Last update: August 27, 2021

Coin Change
Descripcion: Código que ayuda a conocer que cantidades de ciertas denominaciones de monedas
  podrían cubrir cierta cantidad de cambio.
-Complejidad de algoritmo dinamico: O(n^2)
-Complejidad de algoritmo avaro: O(n)
Input: Numero entero (n), seguido de N valores enteros (uno en cada línea), P y Q (P es el precio del producto y Q es la cantidad pagada) en cada linea por la entrada estándar.
Output: Lista de N valores correspondientes al número de monedas de cada denominación, 
  de mayor a menor, una en cada línea, que se tienen que dar para dar el cambio por el producto pagado-

Instrucción ejecución:
> g++ main.cpp -o <exe file>
> <exe file> < <txt_file>

Ejemplo ejecución:
> g++ main.cpp -o coinChange.exe
> coinChange.exe < caso_prueba_1.txt
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

/*
Funcion coinChangeDynamic(): Funcion que obtiene el número minimo de monedas de cada denominación para dar un cambio de monedas. Funciona bajo los conceptos de programacion dinamica
Entrada: Vector tipo long para denominaciones de monedas disponibles, entero de cantidad de cambio
Salida: Ninguna
Complejidad: O(n^2) 
*/
void coinChangeDynamic(vector<long> coins, int n){
  // Crear un matriz de ceros
  int matrix[coins.size()+1][n+1];
  fill(*matrix, *matrix + (coins.size()+1)*(n+1), 0);

  // Llenar ascendentemente primer renglon con numero de monedas
  for(int i = 1; i < n+1; i++){
    matrix[0][i] = i;
  }

  // Llenar matriz con con algoritmo dinamico
  for(int col = 1; col < coins.size()+1; col++){
    for(int row = 1; row < n+1; row++){
      if(coins[col-1] == row){
        matrix[col][row] = 1;
      } 
      else if(coins[col-1] > row){
        matrix[col][row] = matrix[col-1][row];
      }
      else{
        matrix[col][row] = min(matrix[col-1][row], 1 + matrix[col][row-coins[col-1]]);
      }
    }
  }

  // Inicializar variables
  int i = coins.size();
  int j = n;
  map<long, long> map; 
  int suma = 0;

  // Inicializar ceros map en denominaciones de monedas
  for (int k=0; k < i; k++) {
    map.insert(pair<long, long>(coins[k], 0));
  } 

  // Calcular la cantidad de monedas por denominacion
  while(j != 0 && i > 0){
    if(matrix[i][j - coins[i-1]] == matrix[i][j]-1){
      suma += coins[i-1];
      map[coins[i-1]] += 1;
      j = j - coins[i-1];
    }
    else{
      i--;
    }
  }

  // En caso de no coincidir con cambio no imprime nada
  if(suma != n || i<=0){
    cout << "Change is not exact" << endl;
    return;
  }
  
  // Imprimir en forma de lista, cantidad de monedas minimas para el cambio de mayor a menor denominacion. 
  // Formato de impresion [denominacion de moneda: numero de monedas]
  while(coins.size()){
    long value = coins[coins.size()-1];
    coins.pop_back();
    cout << value << ": " << map[value] << endl;
  }
}

/*
Funcion coinChangeDynamic(): Funcion que obtiene el número minimo de monedas de cada denominación para dar un cambio de monedas. Funciona bajo los conceptos de un algoritmo avaro
Entrada: Vector tipo long para denominaciones de monedas disponibles, entero de cantidad de cambio
Salida: Ninguna
Complejidad: O(n) 
*/
void coinChangeGreedy(vector<long> coins, int n){
  // Inicializar variables
  int pos = coins.size() - 1;
  long suma = 0;
  map<long, long> map; 

  // Inicializar ceros map en denominaciones de monedas
  for (int k=0; k < coins.size(); k++) {
    map.insert(pair<long, long>(coins[k], 0));
  } 

  // Conocer cantidad de monedas de cada denominacion
  while (suma < n && pos >= 0) {
    int cantidad = (n-suma)/coins[pos];
    map[coins[pos]] = cantidad;
    suma += coins[pos] * cantidad;
    pos--;
  }
  
  // En caso de que no se logre un cambio exacto
  if(suma != n){
    cout << "Change is not exact" << endl;
    return;
  }

  // Imprimir en forma de lista, cantidad de monedas minimas para el cambio de mayor a menor denominacion. 
  // Formato de impresion [denominacion de moneda: numero de monedas]
  while(coins.size()){
    long value = coins[coins.size()-1];
    coins.pop_back();
    cout << value << ": " << map[value] << endl;
  }

}

int main() {
  // Inicializacion variables
  int n; // Numero de monedas
  long coin; // Denominacion de moneda
  vector<long> coins; // Arreglo de denominaciones de monedas
  int p; // Precio de un producto dado
  int q; // Billete o moneda con que se paga dicho producto
  int cambio; // Cantidad de cambio

  // Input
  cin >> n;

  if(!n){
    cout << "There are no coin denominations" << endl;
    return 0;
  }
  
  for (int i=0; i<n; i++) {
    cin >> coin;
    coins.push_back(coin);
  }

  // Ordenar vector de menor a mayor
  sort(coins.begin(), coins.end());

  // Input
  cin >> p;
  cin >> q;

  // Validar y realizar cambio
  if (q<p) {
    cout << "Underpayment" << endl;
  } else {
    cambio = q-p;
    // Llamada a algoritmo de programacion dinamica
    cout << endl; 
    cout << "Programacion Dinamica: " << endl; 
    coinChangeDynamic(coins, cambio);
    // Llamada a algoritmo avaros 
    cout << endl; 
    cout << "Programacion Avara: " << endl; 
    coinChangeGreedy(coins, cambio);
  }

  return 0;
}
