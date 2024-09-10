
//Los códigos para este algoritmo fueron sacados de estos links:
//https://www.geeksforgeeks.org/cpp-matrix-multiplication/
//https://www.geeksforgeeks.org/cpp-program-to-find-transpose-of-a-matrix/
//https://leetcode.com/problems/transpose-matrix/solutions/3676961/c-easy-implementation-using-vectors/
//Se modificaron para lograr que se ejecutara correctamente el programa

#include <bits/stdc++.h>
using namespace std;
 
/*
Para probar los algoritmos los archivos con los datos de las matrices deben estar en la carpeta output
Este algoritmo desarrolla de la misma forma la multiplicación de matrices
que el iterativo clasico pero se le agrega la transposición de la matriz
para lograr una optimización en el tiempo de ejecución
*/

//Esta función devuelve la matriz transpuesta de la matriz B
vector<vector<int>> transpose(const vector<vector<int>> &matrizB) //no se cambia el valor de la matriz original
{ 
    int filas = matrizB.size();
    int columnas = matrizB[0].size();

    vector<vector<int>> transpuesta(columnas, vector<int>(filas));//matriz transpuesta
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            transpuesta[j][i] = matrizB[i][j];//se cambian las filas y columnas
        }
    }

    return transpuesta;
}
 
void mulMat(const vector<vector<int>>& matrizA, vector<vector<int>>& matrizB)
{
    vector<vector<int>> matrizBTranspuesta = transpose(matrizB);//se transpone B

    /*for (size_t i = 0; i < matrizBTranspuesta.size(); ++i) {
        for (size_t j = 0; j < matrizBTranspuesta[0].size(); ++j) {
            cout << matrizBTranspuesta[i][j] << "\t";
        }
        cout << endl;
    }
    */
    
    int R1 = matrizA.size();//número de filas de A
    //int C1 = matrizA[0].size();//número de columnas de A
    int R2 = matrizBTranspuesta.size();//número de filas de B
    int C2 = matrizBTranspuesta[0].size();//número de columnas de B

    vector<vector<int>> rslt(R1, vector<int>(C2,0));//Matriz con R1 filas y C2 columnas inicializada en 0

    //cout << "Multiplicacion de la matriz:\n";
 
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            rslt[i][j] = 0;
 
            for (int k = 0; k < R2; k++) {
                rslt[i][j] += matrizA[i][k] *matrizBTranspuesta[k][j];
            }
 
            //cout << rslt[i][j] << "\t";
        }
 
        //cout << endl;
    }
}
 
int main()
{
    string nombreArch1="matriz A de dimensiones 1800x2048 rango de numeros de -1000000 a 1000000.txt";
    ifstream archivo1(nombreArch1.c_str());

    if (!archivo1.is_open()) {
        std::cout << "Error al abrir el archivo 1.\n"; 
        exit(EXIT_FAILURE);
    }


    vector<vector<int>> a;
    string linea1;

    while(getline(archivo1, linea1)){
        vector<int> fila1;
        istringstream iss(linea1);
        int num;

        while(iss>>num){
            fila1.push_back(num);
        }
        a.push_back(fila1);
    }
    archivo1.close();

    string nombreArch2="matriz B de dimensiones 1800x2048 rango de numeros de -1000000 a 1000000.txt";
    ifstream archivo2(nombreArch2.c_str());

    if (!archivo2.is_open()) {
        std::cout << "Error al abrir el archivo 2.\n"; 
        exit(EXIT_FAILURE);
    }
    vector<vector<int>> b;
    string linea2;

    while(getline(archivo2, linea2)){
        vector<int> fila2;
        istringstream iss(linea2);
        int num;

        while(iss>>num){
            fila2.push_back(num);
        }
        b.push_back(fila2);
    }
    archivo2.close();

    /*
    for (size_t i = 0; i < b.size(); ++i) {
        for (size_t j = 0; j  < b[i].size(); ++j) {
            cout << b[i][j] << "\t";
        }
        cout << endl;
    }
    */
 
    clock_t inicio= clock();
    mulMat(a, b);
    clock_t fin = clock();
    double tiempoEjecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion del algoritmo: " << tiempoEjecucion << " segundos" << endl;

 
    return 0;
}