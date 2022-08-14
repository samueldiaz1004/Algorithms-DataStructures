/*/
Act 2.2 - Verificación de las funcionalidades de una estructura de datos lineal
Programa principal todos los casos de prueba para verificar que la implementación
de cada método de la clase "MyLinkedList"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 01/10/2020
Ultima modificacion: 04/10/202
/*/

#include <iostream>
#include "MyLinkedList.h"
using namespace std;

int main()
{
    // *Estas pruebas cubren la mayoria de los casos de prueba VALIDOS

    // Objetos de lista ligada
    MyLinkedList lista1,
                 lista2,
                 lista3,
                 lista4,
                 lista5;

    cout << "isEmpty:" << endl;
    // Revisar que la lista se encuentre vacia
    // Valor esperado: 1
    cout << lista1.isEmpty() << endl;
    // Insertar un valor en la lista para comprobar que cambia el valor de retorno
    lista1.insertFirst(2);
    // Valor esperado: 0
    cout << lista1.isEmpty() << endl << endl;

    cout << "length:" << endl;
    // Revisar el tamaño de lista1
    // Valor esperado: 1
    cout << lista1.length() << endl << endl;

    cout << "isertFirst:" << endl;
    // Insertar valor al principio de una lista vacia
    lista2.insertFirst(10);
    // Valor esperado: 10
    cout << lista2;
    // Insertar otro valor al principio
    lista2.insertFirst(5);
    // Valor esperado: 5 10
    cout << lista2 << endl;

    cout << "first:" << endl;
    // Revisar el primer valor de lista2
    // Valor esperado: 5
    cout << lista2.first() << endl << endl;

    cout << "insertLast:" << endl;
    // Insertar valor al final de una lista vacia
    lista3.insertLast(4);
    // Valor esperado: 4
    cout << lista3;
    // Insertar otro valor al final
    lista3.insertLast(8);
    // Valor esperado: 4 8
    cout << lista3 << endl;

    cout << "last:" << endl;
    // Revisar el ultimo valor de lista3
    // Valor esperado: 8
    cout << lista3.last() << endl << endl;

    cout << "insertAt:" << endl;
    //Insertar al principio en una lista vacia
    lista4.insertAt(13,0);
    // Valor esperado: 13
    cout << lista4;
    // Insertar al final de la lista
    // Decidi permitir al usuario insertar un valor igual al tamaño de la lista
    lista4.insertAt(4,lista4.length());
    // Valor esperado: 13 4
    cout << lista4;
    // Insertar en medio de dos nodos
    lista4.insertAt(7,1);
    // Valor esperado: 13 7 4
    cout << lista4 << endl;

    cout << "getAt:" << endl;
    // Poblar una lista vacia con varios datos
    for(int i = 0; i < 10; i++){
        lista5.insertLast(i*3);
    }
    // Valor esperado: 0 3 6 9 12 15 18 21 24 27
    cout << lista5;
    // Revisar el primer valor manualmente
    // Valor esperado: 0
    cout << lista5.getAt(0) << endl;
    // Revisar el ultimo valor manualmente
    // Valor esperado: 27
    cout << lista5.getAt(lista5.length()-1) << endl;
    // Revisar un valor en medio de la lista
    // valor esperado: 15
    cout << lista5.getAt(5) << endl << endl;

    cout << "setAt:" << endl;
    cout << lista5;
    //Sustituir un valor al principio de lista5
    lista5.setAt(100,0);
    // Al final
    lista5.setAt(200,lista5.length()-1);
    // En medio
    lista5.setAt(300,5);
    //Valor esperado: 100 3 6 9 12 300 18 21 24 200
    cout << lista5 << endl;

    cout << "removeFirst:" << endl;
    cout << lista5;
    // Remover el primer valor de lista5
    lista5.removeFirst();
    // Valor esperado: 3 6 9 12 300 18 21 24 200
    cout << lista5 << endl;

    cout << "removeLast:" << endl;
    cout << lista5;
    // Remover el ultimo valor de lista5
    lista5.removeLast();
    // Valor esperado: 3 6 9 12 300 18 21 24
    cout << lista5 << endl;

    cout << "removeAt:" << endl;
    cout << lista5;
    // Remover un valor en medio de lista5
    // Para removeAt no es necesario probar remover al principio o final
    // porque esta validado por los metodos removeLast removeFirst
    lista5.removeAt(4);
    // Valor esperado: 3 6 9 12 18 21 24
    cout << lista5;

    // Destructor de objetos
    lista1.~MyLinkedList();
    lista2.~MyLinkedList();
    lista3.~MyLinkedList();
    lista4.~MyLinkedList();
    lista5.~MyLinkedList();

    return 0;
}
