/*/
Act 3.2 - �rbol Heap: Implementando una fila priorizada

Header de clase MyHeap (priority queue)

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 21/10/2020
Ultima modificacion: 22/10/2020
/*/

#ifndef MYHEAP_H
#define MYHEAP_H

#include <iostream>
using namespace std;

class MyHeap
{
    private:
        int* values;
        int size;
        int len;
        void swap(int a, int b);
        void expand();

    public:
        MyHeap();
        void push(int n);
        void pop();
        int top();
        bool isEmpty();
        int length();
};

#endif
