/*/
Implementacion de clase "MyHashTable"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 20/11/2020
Fecha de modificacion: 24/11/2020
/*/

#include "MyHashTable.h"

using namespace std;

// La complejidad computacional de cada operación se calculo suponiendo que la funcion de dispersion:
//      Respeta un factor de balanceo menor a 0.75 y distribuye los valores de manera "equitativa".

// Constructor de la clase
// Colocar valores default en parametros
// Complejidad computacional: O(1)
MyHashTable::MyHashTable()
{
    this->size=0;
    this->cap=11;
    this->tabla=new MyLinkedList[this->cap];
}

// Destructor de clase
// Debe liberar toda la memoria dinamica para evitar memory leaks
// Complejidad computacional: O(n)
MyHashTable::~MyHashTable()
{
    for(int i = 0; i < this->cap; i++){
        while(!this->tabla[i].isEmpty()){
            this->tabla[i].removeFirst();
        }
    }
}

// Verificar si la tabla esta vacia
// Regresa valor booleano
// Complejidad computacional: O(1)
bool MyHashTable::isEmpty()
{
    return this->size==0;
}

// Ajustar tabla tal que su factor de carga sea menor a 0.75
// No recibe ni regresa algun valor
// Complejidad computacional:
//                Mejor caso: O(n)
//             Caso promedio: O(n)
//                 Peor caso: O(n^2)
void MyHashTable::rehashing()
{
    // Guardar el tamaño del arreglo viejo
    int tmpCap = this->cap;
    // Incrementar el tamaño del objeto al doble mas uno
    this->cap = 2 * this->cap + 1;
    // Generar una variable temporal para rehashing de elementos insertados
    MyLinkedList* tmp = this->tabla;
    // Cambiar el tamaño de la tabla
    this->tabla = new MyLinkedList[this->cap];
    // Recorrer cada nodo del arreglo viejo para generar una tabla con nuevos hash codes
    for(int i = 0; i < tmpCap; i++){
        // Mientras la lista actual de la tabla no este vacia...
        while(!tmp[i].isEmpty()){
            // Obtener el codigo hash del primer elemento de la lista
            int pos = getPos(tmp[i].getAt(0)->key);
            // Insertarlo en el tabla con su nueva distribucion
            tabla[pos].insertFirst(tmp[i].getAt(0)->key,tmp[i].getAt(0)->data);
            // Eliminar dicho elemento de la tabla temporal para evitar memory leaks
            tmp[i].removeFirst();
        }
    }
}

// Metodo para generar un hash code y asignar posicion de dato en la tabla
// Recibe uns string la cual servira para gnerar llave
// Regresa llave ya comprimida
// Complejidad computacional: O(1) [siempre hace las mismas cantidad de operaciones aritmeticas]
int MyHashTable::getPos(string key)
{
    // Metodo de libreria <function> para generar un hash code
    size_t hashT=hash<string>{}(key);
    // "Casting" para convertir de size_t a entero
    int hashCode=static_cast<int>(hashT);
    // Regresar hash code ya comprimido
    return abs(hashCode)%this->cap;
}

// Guardar llave con informacion segun su hash code generado
// Recibe llave e dato entero que se desea almacenar
// No regresa algun valor
// Complejidad computacional:
//                Mejor caso: O(1)
//             Caso promedio: O(1)
//                 Peor caso: O(n^2) [En caso de hacer rehashing]
void MyHashTable::put(string key,int value)
{
    // Si el factor de balanceo es mayor o igual a 0.75 se tiene que hacer
    // un remapeo completo antes de la insercion del nuevo elemento
    float loadFactor = (float)this->size/(float)this->cap;
    if(loadFactor >= 0.75){
        rehashing();
    }
    // Obtener el hash code en donde se va insertar el nuevo elemento
    int pos=getPos(key);
    // Insertar al principio de la lista segun su hash code
    this->tabla[pos].insertFirst(key,value);
    // Incrementar el numero representativo de elementos que contiene la tabla
    this->size++;
}

// Regresar dato guardado segun su llave
// Recibe una llave
// Regresa el valor guardado en dicha llave
// Complejidad computacional:
//                Mejor caso: O(1)
//             Caso promedio: O(1)
//                 Peor caso: O(n)
int MyHashTable::get(string key)
{
    // Obtener hash code para ubicar en que parte de la tabla se encuentra el dato
    int pos=getPos(key);
    // Consultar la lista enlazada en donde se encuentra el dato
    MyLinkedList* lista=&this->tabla[pos];
    // Buscar en secuencia por la lista enlazada hasta encontrar el dato
    // con la llave correspodiente y regresar el valor que guarda
    return lista->getAt(key);
}

// Borrar un elemento de la tabla
// Recibe una llave
// No regresa algun valor
// Complejidad computacional:
//                Mejor caso: O(1)
//             Caso promedio: O(1)
//                 Peor caso: O(n)
void MyHashTable::remove(string key)
{
    // Obtener hash code para ubicar en que parte de la tabla se encuentra el dato
    int pos = getPos(key);
    // Buscar en secuencia la llave en la lista con el hash code correspodiente y borrarlo
    this->tabla[pos].removeAt(key);
    // Reducir el numero representativo de elementos que contiene la tabla
    this->size--;
}
