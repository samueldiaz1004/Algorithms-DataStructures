/*/
Act 1.2 - Algoritmos de Búsqueda y Ordenamiento
Aplicación que ordena numeros almacenados en un vector y
hace la busqueda de un elemento en el vector ordenado
por varios algoritmos basicos

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 10/09/2020
Ultima modificacion: 13/09/202
/*/

#include <iostream>
#include <vector>
using namespace std;

/*/
Complejidad computacional en el peor de los casos: O(n^2)
Ordena numeros de forma ascendente con el metodo Insertion
Datos de entrada: vector de enteros (como referencia)
Valor de retorno: un numero de comparaciones que realiza
/*/
long ordenaInsercion(vector<int> &v)
{
    int temp;
    long cont = 0;
    for(int i = 1; i < v.size(); i++){
        for(int j = i-1; j >= 0; j--){
            cont++;
            if(v[j] > v[j+1]){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
            else{
                break;
            }
        }
    }
    return cont;
}

/*/
Complejidad computacional en el peor de los casos: O(n^2)
Ordena numeros de forma ascendente con el metodo Burbuja optimizado
Datos de entrada: vector de enteros (como referencia)
Valor de retorno: un numero de comparaciones que realiza
/*/
long ordenaBurbuja(vector<int> &v)
{
    int temp;
    long cont = 0;
    bool bandera = false;
    for(int i = 1; i < v.size() && !bandera; i++){
        bandera = true;
        for(int j = 0; j < v.size()-i; j++){
            cont++;
            if(v[j] > v[j+1]){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
                bandera = false;
            }
        }
    }
    return cont;
}

/*/
Complejidad computacional en el peor de los casos: O(n)
Ordena los datos de una sublista de manera ascendete
Datos de entrada: vector de enteros (como referencia)
                  posicion del inicio de la sublista
                  posicion del final de la sublista
                  numero comparaciones que realiza (como referencia)
Valor de retorno: ninguno
/*/
void mezcla(vector<int> &v, int ini, int fin, long &cont)
{
    int centro = (ini+fin) / 2;
    int j = ini;
    int k = centro + 1;
    int s = fin - ini + 1;
    int temp[s];

    for(int i = 0; i < s; i++){
        if(j <= centro && k <= fin){
            cont++;
            if(v[j] < v[k]){
                temp[i] = v[j++];
            }
            else{
                temp[i] = v[k++];
            }
        }
        else{
            if(j <= centro){
                temp[i] = v[j++];
            }
            else{
                temp[i] = v[k++];
            }
        }
    }
    for(int m = 0; m < s; m++){
        v[ini+m] = temp[m];
    }
}

/*/
Complejidad computacional en el peor de los casos: O(logn)
Divide el vector por sublistas para despues ser
ordenadas por la funcion "mezcla"
Datos de entrada: vector de enteros (como referencia)
                  posicion del inicio de la sublista
                  posicion del final de la sublista
                  numero comparaciones que realiza (como referencia)
Valor de retorno: ninguno
/*/
void ordenaMerge(vector<int> &v, int ini, int fin, long &cont)
{
    if(ini < fin){
        int centro = (ini+fin) / 2;
        ordenaMerge(v, ini, centro, cont);
        ordenaMerge(v, centro+1, fin, cont);
        mezcla(v, ini, fin, cont);
    }
}

/*/
Complejidad computacional en el peor de los casos: O(nlogn)
Ordena numeros de forma ascendente con el metodo Merge
Datos de entrada: vector de enteros (como referencia)
Valor de retorno: un numero de comparaciones que realiza
/*/
long ordenaMerge(vector<int> &v)
{
    long cont = 0;
    ordenaMerge(v, 0, v.size()-1, cont);
    return cont;
}

/*/
Complejidad computacional en el peor de los casos: O(n)
Buscar con la busqueda secuencial un dato entero dentro del vector
Datos de entrada: vector de enteros (como referencia),
                  dato que desea buscar y
                  contador de revisiones (como referencia)
Valor de retorno: indice donde se encuentra el dato o -1
/*/
long busqSecuencial(vector<int> &v, int dato, int &cantBS)
{
    for(int i = 0; i < v.size(); i++){
        cantBS++;
        if(v[i] == dato){
            return i;
        }
    }
    return -1;
}

/*/
Complejidad computacional en el peor de los casos: O(logn)
Buscar con la busqueda binaria un dato entero dentro del vector
Datos de entrada: vector de enteros (como referencia),
                  dato que desea buscar y
                  contador de revisiones (como referencia)
Valor de retorno: indice donde se encuentra el dato o -1
/*/
long busqBinaria(vector<int> &v, int dato, int &cantBB)
{
    int min = 0,
    max = v.size() - 1,
    avg;
    while(min <= max){
        avg = (min+max)/2;
        cantBB++;
        if(dato == v[avg]){
            return avg;
        }
        else if(dato < v[avg]){
            max = avg - 1;
        }
        else{
            min = avg + 1;
        }
        cantBB++;
    }
    return -1;
}

int main(){
	vector<int> v1, v2, v3;
	int n, dato;
	cin >> n;
	for (int i=0; i<n; i++){
		cin >> dato;
		v1.push_back(dato);
		v2.push_back(dato);
		v3.push_back(dato);
	}
	cout << ordenaInsercion(v1) << " " << ordenaBurbuja(v2) << " " << ordenaMerge(v3) << endl;
	int q, pos;
	int cantBS, cantBB;
	cin >> q;
	for (int i=0; i<q; i++){
		cantBS = 0;
		cantBB = 0;
		cin >> dato;
		pos = busqSecuencial(v1, dato, cantBS);
		pos = busqBinaria(v1, dato, cantBB);
		cout << pos << " " << cantBS << " " << cantBB << endl;
	}
}
