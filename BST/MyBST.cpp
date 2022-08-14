/*/
Implementacion de la clase "Binary Search Tree"

Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 08/10/2020
Fecha de modificacion: 16/10/2020
/*/

#include "MyBST.h"

// Constructor
// Inicializa parametros del BST
MyBST::MyBST()
{
    this->size = 0;
    this->root = nullptr;
}

// Regresa la cantidad de nodos en el BST
int MyBST::length()
{
    return this->size;
}

// Revisa si el BST esta vacio,
// de si serlo regresa verdadero
bool MyBST::isEmpty()
{
    return this->size == 0;
}

// Realiza una busqueda iterativa a traves del BST
// Recibe como paramentro el dato que se desea buscar
// Si el dato se encuentra, regresa verdadero
// Complejidad computacional: O(n)
//                  Promedio: O(height)
bool MyBST::search(int data)
{
    // Apuntador auxiliar para recorrer el BST
    MyNodeBST* current = this->root;
    while(current != nullptr){
        // Si el dato al que se apunto es igual al dato
        // que se esta buscando, termina el ciclo y regresa verdadero
        if(current->data == data){
            return true;
        }
        // Si es menor al nodo apuntado, se desplaza hacia el nodo izquierdo
        else if(data < current->data){
            current = current->left;
        }
        // Si es mayor al nodo apuntado, se desplaza hacia el nodo derecho
        else{
            current = current->right;
        }
    }
    // Regresar falso si se llego a una hoja
    // y no se encontro el dato deseado
    return false;
}

// Metodo de insercion de un nuevo nodo
// Recibe el dato que se desea almacenar en el BST
// Regresa un verdadero/falso dependiendo si se pudo
// colocar correctamente
// Complejidad computacional: O(n)
//                  Promedio: O(height)
bool MyBST::insert(int data)
{
    // Se crea un nuevo nodo con la informacion que se
    // desea colocar en el BST
    MyNodeBST* nvo = new MyNodeBST(data);
    // Caso 1:
    // El BST esta vacio
    if(this->root == nullptr){
        // Se asigna a root el nuevo nodo
        this->root = nvo;
        // Se incrementa el tamaño representativo
        this->size++;
        // La operacion se realizo correctamente
        return true;
    }
    // Nodos auxiliares para insertar nuevo nodo
    // en caso de que ya tenga elementos el BST
    MyNodeBST* current = this->root;
    MyNodeBST* previous;
    // Recorrer el BST hasta una adecuada para
    // insertar el nuevo elemento
    while(current != nullptr){
        if(data < current->data){
            previous = current;
            current = current->left;
        }
        else if(data > current->data){
            previous = current;
            current = current->right;
        }
        else{
            // Caso 2
            // Si el nodo a insertar ya se encuentra en
            // el BST, termina la funcion y se regresa
            // falso indicando que la insercion no fue realizada
            return false;
        }
    }
    // Caso 3:
    // Se encontro el nodo hoja donde se va insertar
    // nuevo nodo
    // En este punto, current apunta fuera a una direccion
    // fuera del BST pero previous va un paso atras por lo
    // que apunta a una hoja
    // Solo falta revisar si el dato es major o menor al dato
    // a insertar
    if(data < previous->data){
        previous->left = nvo;
    }
    else{
        previous->right = nvo;
    }
    // Se incrementa el tamaño representativo
    this->size++;
    // La operacion se realizo correctamente
    return true;
}

// Funcion auxiliar para encontrar el predecesor
// con respecto a un nodo
// Recibe un apuntador a un nodo que actua como raiz
// Regresa un apuntador del predecesor al nodo actual
// Complejidad computacional: O(n)
//                  Promedio: O(height)
MyNodeBST* MyBST::findMax(MyNodeBST* current)
{
    // Revisar que no este apuntando a un espacio vacio
    if(current == nullptr){
        return nullptr;
    }
    // Desplazar el apuntador hasta el elemento mas hacia
    // su derecha
    while(current->right != nullptr){
        current = current->right;
    }
    // Regresar predecesor
    return current;
}

// Remover, de manera recursiva, un data particular del BST
// Recibe como parametros un apuntador, el dato a quitar y
// un valor booleano por referencia
// Regresa un apuntador a un nodo
// Complejidad computacional: O(n)
//                  Promedio: O(height)
MyNodeBST* MyBST::remove(MyNodeBST* current, int data, bool& exists)
{
    // Primero es encontrar el dato a eliminar por medio de una
    // busqueda recursiva
    if(current == nullptr){
        return current;
    }
    else if(data < current->data){
        current->left = remove(current->left,data,exists);
    }
    else if(data > current->data){
        current->right = remove(current->right,data,exists);
    }
    // Si el dato al que apunta current es igual al dato del parametro
    // se puede confirmar la existencia del elemento y se analizan los
    // diferentes casos de prueba
    else{
        // La operacion va ser realizada
        exists = true;
        // Caso 1:
        // El nodo a eliminar es un nodo hoja por lo que
        // se puede borrar de memoria sin alguna consecuencia
        if(current->left == nullptr && current->right == nullptr){
            delete current;
            current = nullptr;
        }
        // Caso 2 & 3:
        // El nodo a eleminar tiene un hijo a su derecha o izquierda
        else if(current->left == nullptr){
            // Apuntador auxiliar para conservar direccion de nodo a borrar
            MyNodeBST* tmp = current;
            // Redireccionar nodo abuelo con sucesor
            current = current->right;
            // Liberar memoria basura
            delete tmp;
        }
        // Extension de caso 2 & 3
        else if(current->right == nullptr){
            MyNodeBST* tmp = current;
            current = current->left;
            delete tmp;
        }
        // Caso 4:
        // El nodo a eliminar cuenta con dos hijos
        else{
            // Apuntador temporal que va a buscar el
            // nodo predesecor de actual
            MyNodeBST* tmp = findMax(current->left);
            // El nodo que se iba a eliminar asume la
            // informacion de su nodo predecesor
            current->data = tmp->data;
            // Se hace una llamada recursiva para eliminar el dato
            // duplicado que se encuentra ahora en un nodo hoja (Caso 1)
            current->left = remove(current->left,tmp->data,exists);
        }
    }
    // regresar el apuntador actual
    return current;
}

// Funcion de preparacion para elimiar un elemento del BST
bool MyBST::remove(int data)
{
    bool exists = false;
    remove(this->root,data,exists);
    // Si se removio el elemento tambien decrese
    // el tamaño representativo del BST
    if(exists){
        this->size--;
    }
    // Regresar el estatus de la operacion,
    // verdadero si fue exitoso el metodo
    return exists;
}

// Recorrido recursivo de BST en preorder
// Recibe como parametro un apuntador a nodo
// No regresa algun valor pero despliega el BST
// Complejidad computacional: O(n)
void MyBST::preorder(MyNodeBST* current)
{
    // Visita la raiz antes del recorrido a los subarboles
    // izquierdo y derecho
    // Es un recorrido de arriba hacia abajo pero difiere
    // del recorrido por niveles
    if(current != nullptr){
        cout << current->data << " ";
        preorder(current->left);
        preorder(current->right);
    }
}

// Funcion de preparacion para impresion en preorder
void MyBST::preorder()
{
    // Llamar funcion recursiva
    preorder(this->root);
    cout << endl;
}

// Recorrido recursivo de BST en inorder
// Recibe como parametro un apuntador a nodo
// No regresa algun valor pero despliega el BST
// Complejidad computacional: O(n)
void MyBST::inorder(MyNodeBST* current)
{
    // La raiz se visita entre el recorrido los
    // subarboles izquierdo y derecho
    // Efectivamente desplegando el BST en orden asendente
    if(current != nullptr){
        inorder(current->left);
        cout << current->data << " ";
        inorder(current->right);
    }
}

// Funcion de preparacion para impresion en inorder
void MyBST::inorder()
{
    // Llamar funcion recursiva
    inorder(this->root);
    cout << endl;
}

// Recorrido recursivo de BST en postorder
// Recibe como parametro un apuntador a nodo
// No regresa algun valor pero despliega el BST
// Complejidad computacional: O(n)
void MyBST::postorder(MyNodeBST* current)
{
    // La raiz se visita al final del recorrido
    // de los subarboles izquierdo y derecho
    // Efectivamente realizando un recorrido de abajo hacia arriba
    if(current != nullptr){
        postorder(current->left);
        postorder(current->right);
        cout << current->data << " ";
    }
}

// Funcion de preparacion para impresion en postorder
void MyBST::postorder()
{
    // Llamar funcion recursiva
    postorder(this->root);
    cout << endl;
}

// Recorrido iterativo de BST por nivel
// Recibe como parametro un apuntador a nodo
// No regresa algun valor pero despliega el BST
// Complejidad computacional: O(n)
void MyBST::level()
{
    // Crear una fila y adjuntar el primer nodo (root)
    queue<MyNodeBST*> q;
    q.push(this->root);
    // Apuntador auxiliar para recorrer todo el arbol
    MyNodeBST* tmp;
    // Mientras la fila no este vacia se va ejecutar el algoritmo
    while(q.size() != 0){
        // Se guarda la entrada en una variable temporal
        tmp = q.front();
        // Se saca de la fila
        q.pop();
        // Se imprime la informacion guarda en tmp
        cout << tmp->data << " ";
        // Se forman en la fila el hijo derecho o izquierdo
        // del ultimo dato impreso
        if(tmp->left != nullptr){
            q.push(tmp->left);
        }
        if(tmp->right != nullptr){
            q.push(tmp->right);
        }
    }
    cout << endl;
}

// Metodo para acceder a cualquier tipo de recorrido implementado
// Recibe un entero indicando el tipo de recorrido a ejecutar
// No regresa algun valor
void MyBST::visit(int type)
{
    if(type == 1){
        preorder();
    }
    else if(type == 2){
        inorder();
    }
    else if(type == 3){
        postorder();
    }
    else if(type == 4){
        level();
    }
    // En caso de pasar un numero fuera del rango,
    // se imprime el siguiente mensaje
    else{
        cout << "Invalid input. Range is 1-4" << endl;
    }
}

// Metodo recursivo para conocer la altura maxima de un BST
// Por ejemplo: un arbol puede tener varias hojas que llegan
// a difetentes niveles pero en este caso se considera a partir
// del nivel 0 (desde la raiz) hasta la hoja mas alejada
// Recibe un puntero a nodo
// Regresa un entero (altura maxima)
// Complejidad computacional: O(n)
int MyBST::height(MyNodeBST* current)
{
    // Si el puntero actual esta fuera del BST
    // regresa cero (stoping condition)
    if (current == nullptr){
        return 0;
    }
    // Contadores que llaman recursivamente al metodo
    int lefth = height(current->left);
    int righth = height(current->right);
    // Se compara el valor de retorno en la ultima llamada
    // reursiva y suma y regresa el valor major
    // De no serlo seria como un contador general para
    // la cantidad de nodos
    if (lefth > righth){
        return lefth + 1;
    }
    else{
        return righth + 1;
    }
}

// Funcion de preparacion para conocer la altura maxima del arbol
int MyBST::height()
{
    return height(this->root);
}

// Metodo iterativo que despliega de forma ascendete
// (de raiz al dato) los ancestros de un nodo especifico
// Recibe un dato especifico
// No regresa algun valor
// Complejidad computacional: O(n)
//                  Promedio: O(height)
void MyBST::ancestors(int data)
{
    // Nodo auxiliar para recorrer el BST
    MyNodeBST* current = this->root;
    // Misma implementacion que en metodo "search"
    while(current != nullptr){
        if(current->data == data){
            // En este caso se considera el nodo del dato
            // que se esta buscando como ancestro de si mismo
            cout << current->data << endl;
            return;
        }
        // Sin embargo mientras va visitando los nodos
        // los va imprimiendo a pantalla (a excepcion del nodo buscado)
        else if(data < current->data){
            cout << current->data << " ";
            current = current->left;
        }
        else{
            cout << current->data << " ";
            current = current->right;
        }
    }
    // En caso de no encontrarlo solo realiza un salto de linea
    cout << endl;
}

// Metodo iterativo que busca el nivel en el que se
// encuentra un nodo en especifico
// Los niveles parten de cero en la raiz hasta el nodo(s)
// en la altura maxima del BST
// Recibe un dato especifico
// Regresa el nivel en el que se encuentra el dato
// Complejidad computacional: O(n)
//                  Promedio: O(height)
int MyBST::whatLevelAmI(int data)
{
    // Misma implementacion que en metodo "search"
    // la unica excepcion es que cuenta con un contador
    int cont = -1;
    MyNodeBST* current = this->root;
    // Podemos conocer el nivel del dato por medio
    // de la cantidad de comparaciones -1 que tiene
    // que hacer el apuntador auxiliar para llegar a
    // dicho nodo
    while(current != nullptr){
        cont++;
        if(current->data == data){
            return cont;
        }
        else if(data < current->data){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    // Regresar -1 si no se encuentra el dato en BST actual
    return -1;
}
