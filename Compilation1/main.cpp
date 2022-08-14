/*
Actividad Integradora 1
Autor: Samuel Alejandro Díaz del Guante (A01637592)
Ultima actualizacion: 14/09/2021

Busqueda de substring
Descripcion: Algoritmo (Knuth-Morris-Pratt) que determina si existe una coincidencia
de subtring entre un archivo de transmición y un archivo de codigo malicioso
-Complejidad computacional: O(n)

Palíndromo más largo
Descripcion: Algortimo (Manacher) que determina la posicion de inicio y fin del
palindromo más largo dentro de un archivo de transmición
-Complejidad computacional: O(n)

Substring más largo común
Descripcion: Algoritmo (programación dinámica) que determina la posicion en que inicia
y termina del primer archivo de transición donde se encuentra el substring más largo en común
-Complejidad computacional: O(n*m)

input
     nada, solamente deben existir los 5 archivos en la misma ruta donde se ejecuta el programa

output
  parte 1
    (true | false) seguido de exactamente un espacio, seguido de la posición en el archivo de transmission1.txt donde inicia el código de mcode1.txt si es que transmission1.txt contiene el código dado en el archivo mcode1.txt
    (true | false) seguido de exactamente un espacio, seguido de la posición en el archivo de transmission1.txt donde inicia el código de mcode1.txt si es que transmission1.txt contiene el código dado en el archivo mcode2.txt
    (true | false) seguido de exactamente un espacio, seguido de la posición en el archivo de transmission1.txt donde inicia el código de mcode1.txt si es que transmission1.txt contiene el código dado en el archivo mcode3.txt
    (true | false) seguido de exactamente un espacio, seguido de la posición en el archivo de transmission2.txt donde inicia el código de mcode1.txt si es que transmission1.txt contiene el código dado en el archivo mcode1.txt
    (true | false) seguido de exactamente un espacio, seguido de la posición en el archivo de transmission2.txt donde inicia el código de mcode1.txt si es que transmission1.txt contiene el código dado en el archivo mcode2.txt
    (true | false) seguido de exactamente un espacio, seguido de la posición en el archivo de transmission2.txt donde inicia el código de mcode1.txt si es que transmission1.txt contiene el código dado en el archivo mcode3.txt

  parte2
    posiciónInicial posiciónFinal (para archivo de transmission1)
    posiciónInicial posiciónFinal (para archivo de transmission2)

  parte3
    posiciónInicial posiciónFinal (de substring común más largo entre archivos de transmisión)

=========================CONCIDERACIÓN IMPORTANTE==========================
    En las tres partes los indices de posición de los textos empiezan en 1.
    Ejemplo: string = ABCDEF | Posición = [1,2,3,4,5,6]
===========================================================================

Instrucción ejecución:
> g++ main.cpp -o <exe file>
> <exe file> < <txt_file>

Ejemplo ejecución:
> g++ main.cpp -o ActInt1.exe
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
Function: Reads file line by line and stores it in a string
Input: File name/path (string)
Output: Contents of the file in a sigle string with no line breaks (string)
Time complexity: O(n)
*/
string readFile(string fileName)
{
    // Open file
    fstream file(fileName);
    string line;
    string text;

    // Get string line by line from file ignoring blank lines
    while(file >> line){
        text = text + line;
    }
    // Return text in a single string
    return text;
}

/*
Function: Create an aux array for KMP algorithm
Input: Pattern to form the array (string)
Output: Aux array for KMP algorithm (vector of int)
Time complexity: O(n)
*/
vector<int> preprocessKmp(string pattern)
{
    int patternLen = pattern.size();
    // Instantiate empty aux array
    vector<int> lps(patternLen,0);
    lps[0] = 0;

    // Indices to fill the array
    int i = 1;
    int j = 0;

    // For each espace in the array
    while(i < patternLen){
        if(pattern[i] == pattern[j]){
            lps[i] = j + 1;
            i++;
            j++;
        }
        else if(j > 0){
            j = lps[j-1];
        }
        else{
            i++;
        }
    }
    // Return formed aux array
    return lps;
}

/*
Function: Main algorithm to find a substring within another string
Input: Text to find the substring (string), substring to search (string)
Output: None
Time complexity: O(n)
*/
void kmp(string text, string pattern)
{
    // Create lps aux array
    vector<int> lps = preprocessKmp(pattern);

    // Initialize pointers
    int i = 0;
    int j = 0;

    // Go through each character in the text once
    while(i < text.size()){
        if(text[i] == pattern[j]){
            i++;
            j++;
        }
        // The pattern is found within the text
        // Stop searching even if the pattern is found again latter in the string
        // Print the position where it starts in the text
        if(j == pattern.size()){
            // Adjust the index so it starts from 1
            int first = i - pattern.size() + 1;
            cout << "true " << first << endl;
            return;
        }
        if(text[i] != pattern[j]){
            if(j > 0){
                j = lps[j-1];
            }
            else{
                i++;
            }
        }
    }

    // The pattern is not found within the text
    cout << "false" << endl;
}

/*
Function: Determine the smallest number between two int
Input: Number to compare (int)
Output: Smallest number (int)
Time complexity: O(1)
*/
int minimum(int a, int b)
{
    return (a<b) ? a : b;
}

/*
Function: Main algorithm to find the largest palindrome within a string
Input: Text to search longest palindrome (string)
Output: None
Time complexity: O(n)
*/
void manacherAlgorithm(string text)
{
    // Lps parameters
    int textLen = 2*text.size()+1;
    vector<int> lps(textLen,0);
    lps[0] = 0;
    lps[1] = 1;

    // Center related positions
    int c = 1;
    int r = 2;

    // Indices for lps
    int maxCenter = 0;
    int maxLength = 0;

    // Search for the lps char by char once
    for(int i = 0; i < textLen; i++){
        int mirrorIndex = 2*c-i;
        lps[i] = 0;
        if(r-i > 0){
            lps[i] = minimum(r-i,lps[mirrorIndex]);
        }
        // Attempt to expand palindrome considering odd and even positions
        while (((i + lps[i]) < textLen && (i - lps[i]) > 0) &&
              (((i + lps[i] + 1) % 2 == 0) ||
              (text[(i + lps[i] + 1)/2] == text[(i - lps[i] - 1)/2] )))
        {
            lps[i]++;
        }
        // track the lenght and center position of the lps
        if(lps[i] > maxLength){
            maxLength = lps[i];
            maxCenter = i;
        }
        // Try to expand beyond the center right position
        if(i+lps[i] > r){
            c = i;
            r = i + lps[i];
        }
    }

    // Calculate first and final pos of the longest palindrome
    // and asjust it so start the cpount from 1
    int first = ((maxCenter-maxLength)/2) + 1;
    int last = first + maxLength - 1;
    cout << first << " " << last << endl;
}

/*
Function: Main algorithm to find the largest common substring between two texts
Input: Two texts to search the longest common substring (string)
Output: None
Time complexity: O(n*m)
*/
void lcs(string text1, string text2)
{
    // Indices to find the first and final position of the substring
    int largestStr = 0;
    int firstPos = 0;
    int finalPos = 0;

    int m = text1.size();
    int n = text2.size();
    // Matrix to store information used in dynamic programming
    vector<vector<int>> matrix(n+1, vector<int>(m+1, 0));

    // Go through the whole matrix
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // If there is a coincidence between two chars of each string
            // look for the data store in the upper left diagonal of the
            // curr cell and add one
            if(text1[j] == text2[i]){
                matrix[i+1][j+1] = matrix[i][j]+1;
                // Track lcs
                if(largestStr < matrix[i+1][j+1]){
                    finalPos = j;
                    largestStr++;
                }
            }
        }
    }

    // Calculate first and final pos of the lcs and asjust it
    // so start the cpount from 1
    finalPos++;
    firstPos = finalPos-largestStr+1;
    cout << firstPos << " " << finalPos << endl;
}

int main()
{
    // Read all files and store their data in strings
    string t1 = readFile("transmission1.txt");
    string t2 = readFile("transmission2.txt");
    string m1 = readFile("mcode1.txt");
    string m2 = readFile("mcode2.txt");
    string m3 = readFile("mcode3.txt");

    // Part 1: String matching between transmission and mcode files
    kmp(t1, m1);
    kmp(t1, m2);
    kmp(t1, m3);
    kmp(t2, m1);
    kmp(t2, m2);
    kmp(t2, m3);
    cout << endl;
    // Part 2: Longest palindromic string in transmission files
    manacherAlgorithm(t1);
    manacherAlgorithm(t2);
    cout << endl;
    // Part 3: Longest common substring between transmission files
    lcs(t1, t2);

    return 0;
}
