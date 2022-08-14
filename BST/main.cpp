/*/
Act 3.1 - Operaciones avanzadas en un BST

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 08/10/2020
Fecha de modificacion: 16/10/2020
/*/

#include <iostream>
#include "MyBST.h"
using namespace std;

int main()
{
    MyBST arbol;
    arbol.insert(8);
    arbol.insert(3);
    arbol.insert(10);
    arbol.insert(1);
    arbol.insert(6);
    arbol.insert(14);
    arbol.insert(4);
    arbol.insert(7);
    arbol.insert(13);

    arbol.ancestors(13);
    return 0;
}
