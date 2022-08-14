/*/
Implementacion de clase "MyLinkedList"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 20/11/2020
Fecha de modificacion: 24/11/2020
/*/

#include "MyLinkedList.h"

using namespace std;

MyLinkedList::MyLinkedList(){
    this->head=this->tail=nullptr;
    this->size=0;
}

MyLinkedList::~MyLinkedList(){
    MyNodoLL* tmp;
    while(tmp != nullptr){
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

int MyLinkedList::length(){
    return this->size;
}

bool MyLinkedList::isEmpty(){
    return this->size==0;
}

int MyLinkedList::getAt(string key){
    MyNodoLL* current=this->head;
    for(int i=0;i<this->size;i++){
        if(current->key==key){
            return current->data;
        }
        current=current->next;
    }
    throw invalid_argument("No se encontró "+key+" en la lista");
}

MyNodoLL* MyLinkedList::getAt(int pos){
    if(pos>=0 && pos<this->size){
        MyNodoLL* current=this->head;
        for(int i=0;i<pos;i++){
            current=current->next;
        }
        return current;
    }else{
        throw invalid_argument("No se puede insertar en la posición "+to_string(pos)+" en una lista de tamaño "+to_string(this->size));
    }
}

void MyLinkedList::insertFirst(string key,int data){
    this->head=new MyNodoLL(key,data,this->head);
    if(this->tail==nullptr){
        this->tail=this->head;
    }
    this->size++;
}

void MyLinkedList::removeFirst(){
    if(this->size>0){
        MyNodoLL* tmp=this->head;
        this->head=this->head->next;
        this->size--;
        if(this->size==0){
            this->tail=nullptr;
        }
        delete tmp;
    }else{
        throw invalid_argument("No se puede borrar el inicio de una lista vacía");
    }
}

void MyLinkedList::removeLast(){
    if(this->size<=1){
        removeFirst();
    }else{
        MyNodoLL* current=this->head;
        for(int i=0;i<this->size-2;i++){
            current=current->next;
        }
        this->tail=current;
        delete current->next;
        this->tail->next=nullptr;
        this->size--;
    }
}

// Se termino la implementacion de esta clase
// Lo unico que cambia es que en lugar de recibir un entero
// que representa la posicion del nodo, recibe su llave
void MyLinkedList::removeAt(string key){
    if(!isEmpty()){
        if(this->head->key == key){
            removeFirst();
        }
        else if(this->tail->key == key){
            removeLast();
        }
        else{
            MyNodoLL* current = this->head;
            MyNodoLL* previous;
            while(current->key != key && current->key != this->tail->key){
                previous = current;
                current = current->next;
            }
            if(current->key == key){
                previous->next = current->next;
                delete current;
                this->size--;
            }
            // Si no logra borrar/encontrar el objeto con la llave correpondiente
            else{
                throw invalid_argument("No se encontro "+key+" en la lista");
            }
        }
    }
    // En caso de que la lista se encuentre vacia
    else{
        throw invalid_argument("No se encontro "+key+" en la lista");
    }
}
