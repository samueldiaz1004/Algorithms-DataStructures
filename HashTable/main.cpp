/*/
Act 5.1

Implementacion de una tabla hash, esta utiliza una estructura
adicional (listas enlazadas) para evitar colisiones (metodo de
encadenamiento externo).

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 20/11/2020
Fecha de modificacion: 24/11/2020
/*/

#include "MyHashTable.h"
using namespace std;

int main(){
    cout<<"Hola mundo HashTable"<<endl;
    MyHashTable ht;
    ht.put("Pablo",1637761);
    ht.put("Jaime",1638030);
    ht.put("Vale",1637865);
    ht.put("Sareli",1634841);
    ht.put("Marisol",1632636);

    string nombre="Pablo";
    cout<<"La matricula de "<<nombre<<" es "<<ht.get(nombre)<<endl;
    nombre="Jaime";
    cout<<"La matricula de "<<nombre<<" es "<<ht.get(nombre)<<endl;
    nombre="Vale";
    cout<<"La matricula de "<<nombre<<" es "<<ht.get(nombre)<<endl;
    nombre="Sareli";
    cout<<"La matricula de "<<nombre<<" es "<<ht.get(nombre)<<endl;
    nombre="Marisol";
    cout<<"La matricula de "<<nombre<<" es "<<ht.get(nombre)<<endl;
    cout<<"FIN"<<endl;

    return 0;
}
