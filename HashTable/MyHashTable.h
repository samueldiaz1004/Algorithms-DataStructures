/*/
Header de clase "MyHashTable"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 20/11/2020
Fecha de modificacion: 24/11/2020
/*/

#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include <string>
#include <iostream>
#include <functional>
#include <cmath>
#include "MyLinkedList.h"

class MyHashTable{
    private:
        int size; // Numero de elementos en el arreglo
        int cap; // Capacidad maxima del arreglo
        MyLinkedList* tabla;
        void rehashing();
        int getPos(string key);
    public:
        MyHashTable();
        ~MyHashTable();
        bool isEmpty();
        void put(string key,int value);
        int get(string key);
        void remove(string key);
};
#endif
