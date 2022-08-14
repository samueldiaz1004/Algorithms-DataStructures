/*
Authors: Samuel Alejandro Díaz del Guante (A01637592) y Roberto López Cisneros (A01637335)
Last update: August 20, 2021

MergeSort
Descripcion: Código que ordena de mayor a menor un arreglo
Ecuacion: T(n) = 2T(n/2) + θ(n)
Complejidad: O(n*log(n)) 
Input: Numero entero (n), seguido de N valores reales (double, uno en cada línea) por la entrada estándar.
Output: Lista de los N valores ordenados de Mayor a menor

Instrucción ejecución:
> g++ main.cpp -o <exe file>
> <exe file> < <txt_file>

Ejemplo ejecución:
> g++ main.cpp -o mergeSort.exe
> mergeSort.exe < caso_prueba_1.txt
*/

#include <iostream>

using namespace std;

/*
Funcion merge(): Funcion que mezcla los subarrays en un solo array
Entrada: originalArray (Arreglo de double), first (primera posicion), last (ultima posicion), middle (mitad posicion array)
Complejidad: O(n) 
*/
void merge(double originalArray[], int first, int last, int middle) {
    int tmpArraySize = last - first + 1;
    double tmpArray[tmpArraySize];
    int firstIndex = first;
    int secondIndex = middle+1;

    for(int i = 0; i < tmpArraySize; i++){
        if (firstIndex <= middle && secondIndex <= last) {
            if(originalArray[firstIndex] > originalArray[secondIndex]){
                tmpArray[i] = originalArray[firstIndex++];
            } else {
                tmpArray[i] = originalArray[secondIndex++];
            }
        } else if (firstIndex <= middle) {
            tmpArray[i] = originalArray[firstIndex++];
        } else if (secondIndex <= last) {
            tmpArray[i] = originalArray[secondIndex++];
        }
    }

    for(int i = 0; i < tmpArraySize; i++) {
        originalArray[first+i] = tmpArray[i];
    }

}

/*
Funcion merge(): Funcion que divide array en dos subarrays
Entrada: originalArray (Arreglo de double), first (primera posicion), last (ultima posicion), middle (mitad posicion array
Complejidad: O(n*log(n)) 
*/
void mergeSort(double originalArray[], int first, int last) {
    if (first < last) {
        int middle = (last+first) / 2;

        // First half
        mergeSort(originalArray, first, middle);
        // Second half
        mergeSort(originalArray, middle+1, last);

        // Merge
        merge(originalArray, first, last, middle);
    }
}

/*
Funcion printDoubleArray(): Funcion que imprime arreglo de double
Entrada: Arreglo (Double), tamaño arreglo (integer)
Complejidad: O(n-1)
*/
void printDoubleArray(double array[], int n) {
    cout << "[";
    if (n > 0) {
        for (int i=0; i<n-1; i++) {
            cout << array[i] << ", ";
        }
        cout << array[n-1];
    } 
    cout << "]" << endl;
}

int main() {
    // Input array size
    int n;
    cin >> n;

    // Input array values
    double value;
    double originalArray[n];
    for (int i=0; i<n; i++) {
        cin >> value;
        originalArray[i] = value;
    }

    // Print input array
    cout << "Input array: ";
    printDoubleArray(originalArray, n);

    int initialPos = 0;
    int finalPos = n-1;

    // Starting merge sort
    mergeSort(originalArray, initialPos, finalPos);

    // Print sort array
    cout << "Sorted array: ";
    printDoubleArray(originalArray, n);

    return 0;
}


