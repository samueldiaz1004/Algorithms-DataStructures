/*/
Implementacion de metodos de una "Priority queue"

Samuel Alejandro Diaz del Guante Ochoa - A01637592
/*/

#include "MyHeap.h"

// Constructor de clase
// Inicializar datos
// Complejidad computacional: O(1)
MyHeap::MyHeap()
{
    // len representa la capacidad maxima del arreglo
    this->len = 7;
    // size representa cuantos valores tiene almacenado el arreglo
    this->size = 0;
    // values es un apuntador a un arreglo de enteros
    this->values = new int[len];
}

// Intercambia de posicion dos valores en el arreglo
// Recibe los indices de los numeros en donde sucedera el intercambio
// No regresa algun valor
// Complejidad computacional: O(1)
void MyHeap::swap(int a, int b)
{
    // Variable temporal para guardar dato "a"
    int tmp = this->values[a];
    // Sobreescibir el dato en "b" en lugar del dato "a"
    this->values[a] = this->values[b];
    // Poner el dato guardado en la variable temporal en el lugar de "b"
    this->values[b] = tmp;
}

// Aumenta de manera dinamica el tama�o maximo del arreglo
// No recibe ni regresa algun valor
// Complejidad computacional: O(n)
//      Ya sea en peor, mejor o caso promedio; la complejidad siempre
//      es la misma ya que necesita se necesita recorrer todo el arreglo
//      para copiar todos los datos del arreglo viejo al nuevo
void MyHeap::expand()
{
    // Se aumenta el tama�o del arreglo para permitir un nivel completo
    // para nuevas inserciones. Ejemplo de crecimiento: 7,15,31,63,etc.
    this->len = 2 * this->len + 1;
    // Apuntador a arreglo con nuevo tama�o
    int* temp = new int[this->len];
    // Copiar todos los valores al arreglo nuevo
    for(int i = 0; i < this->size; i++){
        temp[i] = values[i];
    }
    // Borrar arreglo viejo
    delete[] values;
    // Apuntar a nuevo arreglo
    values = temp;
}

// Insertar un valor nuevo a la fila de prioridad conservando sus propiedades
// Recibe el dato a insertar
// No regresa algun valor

// Complejidad computacional:
//      Peor de los casos: o(n)
//      No importa si se inserta con menor prioridad, si el dato se coloca
//      justo cuando se lleno el arreglo es necesario recorrer toda la lista
//      de nuevo para copiar todos los datos a un nuevo arreglo mas amplio para
//      despues situar el valor en cualquiera sea su posicion correcta

//      Mejor de los casos: O(1)
//      Esto ocurre cuando el arreglo esta vacio y solo se necesita
//      ejecutar la primer parte del algoritmo sin necesidad de entrar al ciclo
void MyHeap::push(int n)
{
    // Si el tama�o y capacidad son iguales, la siguiente vez que
    // se desee insetar un dato se tendra que expandi su capacidad total
    if(this->size == this->len){
        expand();
    }
    // Incrementar el tama�o representativo del arreglo
    this->size++;
    // Posicionar el nuevo valor al final de la fila
    this->values[this->size-1] = n;
    // "Apuntador" auxiliar para realizar los intercambios necesarios
    int current = this->size-1;
    // Indice del "nodo" padre del dato recien insertado
    int parent;
    // Mientras el apuntador actual no sobrepase la posicion de la raiz, el proceso de
    // heapify hacia arriba va a continuar
    while(current > 0){
        // Actualizar la posicion del nodo padre
        parent = (current-1)/2;
        // Si el valor nuevo tiene mayor prioridad que su padre se ejecuta
        // un interbambio entre ambos elementos
        if(this->values[parent] < this->values[current]){
            swap(parent,current);
            // Como ocurrio el cambio tambien se debe actualizar el apuntador
            // al valor nuevo
            current = parent;
        }
        // Si el dato ya se encuentra en su nivel adecuado significa que
        // ya termino el metodo
        else{
            return;
        }
    }
}

// Eliminar el valor con mayor prioridad de la lista conservando sus propiedades
// Recibe el dato a insertar
// No regresa algun valor

// Complejidad computacional:
//      Peor de los casos: O(logn) = O(altura)
//      Dado a que el arbol casi siempre esta casi balanceado, eliminar un dado
//      significa hacer un recorrido (similar al binario) de la raiz para
//      acomodar el dato fuera de lugar a su nivel correspondiente y mantener las
//      propiedades de la fila con prioridad

//      Mejor de los casos: O(1)
//      Se tiene que eliminar solo un dato (el que esta en la raiz) por lo que solo se
//      ejecutan las intrucciones de orden constante ignorando el ciclo por completo
void MyHeap::pop()
{
    // Si el arreglo ya se encuentra vacio, termina el metodo para evitar modificar
    // el tama�o representativo del arreglo y no ejecutar el resto del codigo
    if(isEmpty()){
        return;
    }
    // Eliminar el primer dato del arreglo sobrescribiendo con el ultimo
    this->values[0] = values[this->size-1];
    // Eliminar el ultimo dato del arreglo
    this->values[this->size-1] = 0;
    // Decrecer tama�o representativo del arreglo
    this->size--;
    // "Apuntador" auxiliar para mover el valor en la raiz a su posicion correcta
    int current = 0;
    // Valores representativos de los hijos del nodo actual visto desde un arreglo
    int left = current*2+1;
    int right = current*2+2;
    // Ejecutar intercambios mientras el valor actual tenga por lo menos un hijo disponible
    while(left <= this->size || right <= this->size){
        // Si el hijo izquierdo existe y es mayor que hermano derecho
        if(this->values[left] > this->values[right] && left <= this->size){
            // Ocurre un cambio entre el valor actual y su hijo izquierdp
            swap(current,left);
            // El valor actual se deplaza al hijo izquierdo
            current = left;
        }
        // Mismo procedimiento pero con hijo derecho
        else if(this->values[left] < this->values[right] && right <= this->size){
            swap(current,right);
            current = right;
        }
        // Sino termina el proceso
        else{
            return;
        }
        // Actualizar la posicion del hijo izquierdo y derecho en relacion
        // al nuevo padre
        left = current*2+1;
        right = current*2+2;
    }
}

// Revisar el siguiente valor en la lista de prioridad
// No recibe algun dato
// Regresa un entero
// Complejidad computacional: O(1)
int MyHeap::top()
{
    // Regresa el valor en el primer indice del arreglo
    return this->values[0];
}

// Revisar si el arreglo esta vacio
// No recibe algun dato
// Regresa un dato booleano
// Complejidad computacional: O(1)
bool MyHeap::isEmpty()
{
    // Si el tama�o representativo de la lista es "0"
    // regresa true, sino false
    return this->size == 0;
}

// Revisar el cantidad de datos en el arreglo
// No recibe algun dato
// Regresa un entero
// Complejidad computacional: O(1)
int MyHeap::length()
{
    // Regresa el valor representativo del numero de
    // valores almacenados
    return this->size;
}
