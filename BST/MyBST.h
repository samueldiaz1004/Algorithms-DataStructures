/*/
Act 3.1 - Operaciones avanzadas en un BST

Es una estructura de datos que almacena informacion en una
estructura de nodos que a su vez puenden apuntar a otro nodo
izquierdo o derecho. Contiene las operaciones basicas de un
BST (insertar, remover, recorrer, etc.)

Header de la clase "Binary Search Tree"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 08/10/2020
Fecha de modificacion: 16/10/2020
/*/

#ifndef MYBST_H
#define MYBST_H

#include <iostream>
#include <queue>
using namespace std;

// Es la unidad de un BST
// Un nodo almacena informacion y cuenta con
// un par de apuntadores (right y left)
struct MyNodeBST{
    int data;
    MyNodeBST* left;
    MyNodeBST* right;

    MyNodeBST(int data)
    {
        this->data = data;
        this->left=this->right=nullptr;
    }
};

class MyBST
{
    private:
        MyNodeBST* root;
        int size;
        MyNodeBST* findMax(MyNodeBST* current);
        MyNodeBST* remove(MyNodeBST* current, int data, bool& exists);
        void preorder(MyNodeBST* current);
        void inorder(MyNodeBST* current);
        void postorder(MyNodeBST* current);
        int height(MyNodeBST* current);

    public:
        MyBST();
        int length();
        bool isEmpty();
        bool search(int data);
        bool insert(int data);
        bool remove(int data);
        void preorder();
        void inorder();
        void postorder();
        void level();
        void visit(int type);
        int height();
        void ancestors(int data);
        int whatLevelAmI(int data);
};

#endif
