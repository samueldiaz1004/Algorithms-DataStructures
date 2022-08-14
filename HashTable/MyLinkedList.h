/*/
header de clase "MyLinkedList"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 20/11/2020
Fecha de modificacion: 24/11/2020
/*/

#ifndef MY_LINKEDLIST_H
#define MY_LINKEDLIST_H
#include <iostream>
#include <string>
using namespace std;

struct MyNodoLL{
    string key;
    int data;
    MyNodoLL* next;

    MyNodoLL(string key,int data,MyNodoLL* next){
        this->key=key;
        this->data=data;
        this->next=next;
    }

    MyNodoLL(string key,int data):MyNodoLL(key,data,nullptr){}
};

class MyLinkedList{
    private:
        MyNodoLL* head;
        MyNodoLL* tail;
        int size;
    public:
        MyLinkedList();
        ~MyLinkedList();
        int length();
        bool isEmpty();
        MyNodoLL* getAt(int pos);
        int getAt(string key);
        void insertFirst(string key,int data);
        void removeFirst();
        void removeLast();
        void removeAt(string key);
        friend ostream& operator<<(ostream& os,const MyLinkedList& ll){
            MyNodoLL* current=ll.head;
            for(int i=0;i<ll.size;i++){
                os<<"["<<current->key<<",";
                os<<current->data<<"]";
                current=current->next;
            }
            return os;
        }
};
#endif
