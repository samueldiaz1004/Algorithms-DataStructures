/*/
Act 2.1 - Implementación de un ADT de estructura de datos lineales
Estructura de un nodo y clase de una lista ligada con sus
repesctivos atributos y metodos

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 01/10/2020
Ultima modificacion: 04/10/202
/*/

#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include <iostream>
#include <limits>
using namespace std;

// Es la unidad de una lista ligada
// Un nodo contiene un valor a guardar y un apuntador a otra estructura tipo nodo
struct MyNode
{
    int data;
    MyNode* next;

    // Constructor
    // Recibe numero entero y apuntador a otro nodo
    MyNode(int data, MyNode* next)
    {
        this->data = data;
        this->next = next;
    }

    // Constructor
    // Solo recibe numero entero, apunta a NULL por default
    MyNode(int data):MyNode(data, nullptr){}
};

// ADT lineal que consiste en el enlazamiento de nodos
// Utiliza apuntadores auxiliares (head y tail) y un indice de
// tamanño para reducir la complejidad de ciertos metodos
class MyLinkedList
{
    private:
        MyNode* head;
        MyNode* tail;
        int size;

    public:
        MyLinkedList();
        ~MyLinkedList();
        int length();
        bool isEmpty();
        int first();
        int last();
        int getAt(int pos);
        void setAt(int data, int pos);
        void insertFirst(int data);
        void insertLast(int data);
        void insertAt(int data, int pos);
        void removeFirst();
        void removeLast();
        void removeAt(int pos);
        friend ostream& operator<<(ostream& os, const MyLinkedList& LL){
            MyNode* current = LL.head;
            for(int i = 0; i < LL.size; i++){
                os << current->data << " ";
                current = current->next;
            }
            os << endl;
            return os;
        }
};

#endif
