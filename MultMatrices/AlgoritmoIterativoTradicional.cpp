// De esta página se adquirió el código: https://www.geeksforgeeks.org/cpp-matrix-multiplication/
//Que luego fue modificado para que pudieran leerse correctamente los archivos

#include <bits/stdc++.h>
using namespace std;
 
/*
Para probar los algoritmos los archivos con los datos de las matrices deben estar en la carpeta output
Podemos multiplicar matrices si el número de columnas de la primera matriz es igual al número
de filas de la segunda matriz y la matriz resultante tendrá el mismo número de filas
que la primera matriz y el mismo número de columnas que la segunda

Se utilizan tres bucles anidados para realizar la multiplicación de matrices.
Los primeros dos bucles recorren las filas y columnas de la matriz resultado, respectivamente.
El bucle más interno realiza la multiplicación de los elementos correspondientes 
de las filas de la primera matriz y las columnas de la segunda matriz.
Se suman estos productos para obtener el elemento de la matriz resultante
Se repite esto hastan completar la matriz resultante
*/

//se entregan como constantes porque no vamos a cambiar los valores de estas matrices
void mulMat(const vector<vector<int>>& matrizA, const vector<vector<int>>& matrizB)
{
    int R1 = matrizA.size();//número de filas de A
    //int C1 = matrizA[0].size();//número de columnas de A 
    int R2 = matrizB.size();//número de filas de B
    int C2 = matrizB[0].size();//número de columnas de B



    vector<vector<int>> rslt(R1, vector<int>(C2,0));
    //Matriz resultado con R1 filas y C2 columnas inicializada en 0
 
   // cout << "Multiplicacion de la matriz:\n";
 
    for (int i = 0; i < R1; i++) {//Recorre filas de la primera matriz
        for (int j = 0; j < C2; j++) {//Recorre columnas de la segunda matriz
            rslt[i][j] = 0;
 
            for (int k = 0; k < R2; k++) {//Se realiza la multiplicación de los elementos de la fila de la primera
            //matriz y la columna de la segunda, sumando los resultados
                rslt[i][j] += matrizA[i][k] * matrizB[k][j];
            }
 
            //cout << rslt[i][j] << "\t";
        }
 
        //cout << endl;
    }
}
 int main()
{
    //se leen los valores de los archivos que contienen las matrices
    string nombreArch1="matriz A de dimensiones 1800x2048 rango de numeros de -1000000 a 1000000.txt";
    ifstream archivo1(nombreArch1.c_str());

    if (!archivo1.is_open()) {
        std::cout << "Error al abrir el archivo 1.\n"; 
        exit(EXIT_FAILURE);
    }

    //Matriz A
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

    string nombreArch2="matriz B de dimensiones 2048x1800 rango de numeros de -1000000 a 1000000.txt";
    ifstream archivo2(nombreArch2.c_str());

    if (!archivo2.is_open()) {
        std::cout << "Error al abrir el archivo 2.\n"; 
        exit(EXIT_FAILURE);
    }

    //Matriz b
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
 
    if (a[0].size() != b.size()) {
        cout << "El número de columnas de la Matriz A debe ser igual al número de filas de la Matriz B "<< endl;
        exit(EXIT_FAILURE);
    }
 
    //Se llama al algoritmo y se calcula el tiempo de ejecución que se muestra por la terminal
    clock_t inicio = clock();
    mulMat(a, b);
    clock_t fin = clock();
    double tiempoEjecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion del algoritmo: " << tiempoEjecucion << " segundos" << endl;
 
    return 0;
}