#include "MyLinkedList.h"

/*/
Constructor
Inicializa parametros de una lista ligada vacia
/*/
MyLinkedList::MyLinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

/*/
Destructor
Vacia la lista ligada
/*/
MyLinkedList::~MyLinkedList()
{
    MyNode* tmp;
    while(tmp != nullptr){
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

/*/
Regresa el tamaño de la lista
Complejidad computacional: O(1)
/*/
int MyLinkedList::length()
{
    return this->size;
}

/*/
Regresa un valor booleano dependiendo del tamaño de la lista
Complejidad computacional: O(1)
/*/
bool MyLinkedList::isEmpty()
{
    if(this->head == nullptr){
      return true;
    }
    else{
     return false;
    }
}

/*/
Regresa el valor que se encuentra al principio de la lista
Complejidad computacional: O(1)
/*/
int MyLinkedList::first()
{
    return this->head->data;
}

/*/
Regresa el valor que se encuentra al final de la lista
Complejidad computacional: O(1)
/*/
int MyLinkedList::last()
{
    return this->tail->data;
}

/*/
Recibe la posicion del dato que se quiere obtener
Regresa el dato de la posicion solicitada
Complejidad computacional: O(n)
/*/
int MyLinkedList::getAt(int pos)
{
    if(pos >= 0 && pos < this->size){
        // Nodo auxiliar para buscar el dato en la posicion dada
        MyNode* current = this->head;
        for(int i = 0; i < pos; i++){
            // Nodo apunta a la siguiente direccion en la lista
            current = current->next;
        }
        // Regresa dato a que esta apuntando
        return current->data;
    }
    // En caso de que la posicion dada no exista en la lista se arroja una excepcion
    else{
        throw invalid_argument("Cannot access this element in the list");
    }
}

/*/
Recibe entero y posicion en la lista en la que sera sustituida por el nuevo dato
No regresa algun dato
Complejidad computacional: O(n)
/*/
void MyLinkedList::setAt(int data, int pos)
{
    if(pos >= 0 && pos < this->size){
        // Nodo auxiliar para navegar secuencialmente por la lista
        MyNode* current = this->head;
        for(int i = 0; i  < pos; i++){
            // Nodo apunta a la siguiente direccion en la lista
            current = current->next;
        }
        // Una vez encontrado, sustituye el nuevo valor en el nodo que apunta
        current->data = data;
    }
    // En caso de que la posicion dada no exista en la lista se arroja una excepcion
    else{
        throw invalid_argument("Cannot access this element in the list");
    }
}

/*/
Recibe entero que sera insertado al principio de la lista
No regresa algun valor
Complejidad computacional: O(1)
/*/
void MyLinkedList::insertFirst(int data)
{
    this->head = new MyNode(data, this->head);
    // Si la lista esta vacia se asegura tambien de actualizar el apuntador tail
    if(this->size == 0){
        this->tail = this->head;
    }
    // Incrementar el tamaño representativo de la lista
    this->size++;
}

/*/
Recibe entero que sera insertado al final de la lista
No regresa algun valor
Complejidad Computacional: O(1)
/*/
void MyLinkedList::insertLast(int data)
{
    // Cubre el caso de que la lista se encuentre vacia
    if(this->size == 0){
        insertFirst(data);
    }
    // Sino se crea un apuntador tipo nodo con el dato a insertar
    else{
        MyNode* nvo = new MyNode(data);
        // El antes ultimo dato apunta a el nuevo nodo
        this->tail->next = nvo;
        // Se actualiza el apuntador tail
        this->tail = nvo;
        // Se incrementa el tamaño representativo de la lista
        this->size++;
    }
}

/*/
Recibe entero y posicion del nuevo nodo a insertar en la lista
Ejemplo:
    lista {0,1,2,3,4}
    lista.insertAt(100,2)
    lista {0,1,100,2,3,4}
No regresa algun valor
Complejidad computacional: O(n)
/*/
void MyLinkedList::insertAt(int data, int pos)
{
    if(pos <= this->size && pos >= 0){
        // Cubre el caso de que la lista se encuentre vacia o se requiera insertar el nodo al principio
        if(pos == 0){
            insertFirst(data);
        }
        // Cubre el caso de que la el nodo se requiera insertar al final
        else if(pos == this->size){
            insertLast(data);
        }
        // Sino busca secuencialmente la posicion a la que se requiere insertar el nuevo nodo
        else{
            MyNode* nuevo = new MyNode(data);
            // Nodos auxiliares
            MyNode* previous;
            MyNode* current = this->head;
            for(int i = 0; i < pos; i++){
                // Es imperativo seguir este orden para no perder la secuencia en el desplazamiento
                previous = current;
                current = current->next;
            }
            // Enlazar nuevo nodo a la lista con ayuda de previo y actual
            nuevo->next = current;
            previous->next = nuevo;
            // Se incrementa el tamaño representativo de la lista
            this->size++;
        }
    }
    else{
        // En caso de que la posicion dada no exista en la lista se arroja una excepcion
        throw invalid_argument("Position exceedes the current max size of the list");
    }
}

/*/
Remueve el primer elemento de la lista
No recibe ni regresa algun dato
Complejidad computacional: O(1)
/*/
void MyLinkedList::removeFirst()
{
    if(this->size > 0){
        // Nodo auxiliar que apunta al primer dato en la lista a borrar
        MyNode* current = this->head;
        // Head ahora apunta a el segundo elemento en la lista
        this->head = this->head->next;
        // // Se decrece el tamaño representativo de la lista
        this->size--;
        // Si la lista queda vacia tambien es necesario actualizar tail
        if(this->size == 0){
            this->tail = nullptr;
        }
        // Se borra objeto al que apunta nodo auxiliar
        delete current;
    }
    else{
        // Arroja una excepcion si la lista se encuentra vacia
        throw invalid_argument("Cannot delete an element from an empty list");
    }
}

/*/
Remueve el ultimo elemento de la lista
No recibe ni regresa algun dato
Complejidad computacional: O(n)
/*/
void MyLinkedList::removeLast()
{
    if(this->size > 0){
        // Cubre el caso solo exista un dato en la lista
        if(this->head == this->tail){
            removeFirst();
        }
        //Sino es necesario desarrollar un busqueda secuencial
        else{
            // Nodos auxiliares para la busqueda y destruccion del elemento
            MyNode* current = head;
            MyNode* previous;
            // Continuar con la busqueda hasta que current llegue al final de la lista
            while(current != tail){
                // Previous mantiene una distancia de un elemento detras de current
                previous = current;
                current = current->next;
            }
            // El penultimo nodo ahora apunta a una direccion nula
            previous->next = nullptr;
            // Tail apunta al nueva cola de la lista
            tail = previous;
            // Se borra el elemento aislado de la lista
            delete current;
            // Se decrementa el tamaño representativo de la lista
            this->size--;
        }
    }
    else{
        // Arroja una excepcion si la lista se encuentra vacia
        throw invalid_argument("Cannot delete an element from an empty list");
    }

}

/*/
Recibe la posicion del elemento que se desea eliminar de la lista
No regresa algun dato
Complejidad computacional: O(n)
/*/
void MyLinkedList::removeAt(int pos)
{
    if(pos < this->size && pos >= 0){
        // Cubre el caso que el elemento a eliminar se encuentre al principio de la lista
        if(pos == 0){
            removeFirst();
        }
        // Cubre el caso que el elemento a eliminar se encuentre al final de la lista
        else if(pos == this->size-1){
            removeLast();
        }
        // Sino busca secuencialmente la posicion del elemento a eliminar
        else{
            // Nodos auxiliares para ubicar el elemento y no estropear la secuencia de la lista
            MyNode* current = this->head;
            MyNode* previous;
            for(int i = 0; i < pos; i++){
                // Desplazamiento de los nodos hasta llegar a la posicion deseada
                previous = current;
                current = current->next;
            }
            // Se enlaza el nodo anterior con el subsecuente al nodo por eliminar
            previous->next = current->next;
            // Se elimina el elemento apuntado por actual
            delete current;
            // Se decrece el tamaño representativo de la lista
            this->size--;
        }
    }
    else{
        // En caso de que la posicion dada no exista en la lista se arroja una excepcion
        throw invalid_argument("Position exceedes the current max size of the list");
    }
}
