
///El código usado para este algoritmo fue sacado desde aquí: https://martin-thoma.com/strassen-algorithm-in-python-java-cpp/
//fue modificado para que leyera correctamente los archivos de las matrices

//El código original referencia esta página: http://en.wikipedia.org/w/index.php?title=Strassen_algorithm&oldid=498910018#Source_code_of_the_Strassen_algorithm_in_C_language


/*Para probar los algoritmos los archivos con los datos de las matrices deben estar en la carpeta output
El Algoritmo de Strassen divide dos matrices A y B en cuatro sub-matrices cada una
Luego calcula 7 producto intermedios combinando las sub-matrices
Combina los 7 productos intermedios para obtener las sub-matrices de la matriz resultado
*/


#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
int leafsize=1;//Como esta versión del algoritmo esta optimizada para que cuando llegue
//al tamaño minimo del leafsize ocupe la forma tradicional de multiplicar matrices
//por lo que se deja en 1 para que solo ejecute el algoritmo de Strassen

void strassen(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, unsigned int tam);
unsigned int nextPowerOfTwo(int n);
void strassenR(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C,
              int tam);
void sum(vector< vector<int> > &A,
         vector< vector<int> > &B,
         vector< vector<int> > &C, int tam);
void subtract(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, int tam);

void read(string filename, vector<vector<int>> &matrix);

//Esta es la función que se usa para optimizar el tiempo si modificamos el leafsize
void ikjalgorithm(vector< vector<int> > A,
                                   vector< vector<int> > B,
                                   vector< vector<int> > &C, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
///////////////////////////////////////

void strassenR(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, int tam) {
    if (tam <= leafsize) {//tamaño matriz menor o igual a leafsize se ocupa esto, que en este caso no se hace
        ikjalgorithm(A, B, C, tam);
        return;
    }

    // Se inicializan las variables a ocupar
    else {
        int newTam = tam/2;
        vector<int> inner (newTam);
        vector< vector<int> >
            a11(newTam,inner), a12(newTam,inner), a21(newTam,inner), a22(newTam,inner),
            b11(newTam,inner), b12(newTam,inner), b21(newTam,inner), b22(newTam,inner),
              c11(newTam,inner), c12(newTam,inner), c21(newTam,inner), c22(newTam,inner),
            p1(newTam,inner), p2(newTam,inner), p3(newTam,inner), p4(newTam,inner),
            p5(newTam,inner), p6(newTam,inner), p7(newTam,inner),
            aResult(newTam,inner), bResult(newTam,inner);

        int i, j;

        //Se dividen las matrices en 4 sub-matrices
        for (i = 0; i < newTam; i++) {
            for (j = 0; j < newTam; j++) {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + newTam];
                a21[i][j] = A[i + newTam][j];
                a22[i][j] = A[i + newTam][j + newTam];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + newTam];
                b21[i][j] = B[i + newTam][j];
                b22[i][j] = B[i + newTam][j + newTam];
            }
        }

        // Se calculan los 7 productos

        sum(a11, a22, aResult, newTam); // a11 + a22
        sum(b11, b22, bResult, newTam); // b11 + b22
        strassenR(aResult, bResult, p1, newTam); // p1 = (a11+a22) * (b11+b22)

        sum(a21, a22, aResult, newTam); // a21 + a22
        strassenR(aResult, b11, p2, newTam); // p2 = (a21+a22) * (b11)

        subtract(b12, b22, bResult, newTam); // b12 - b22
        strassenR(a11, bResult, p3, newTam); // p3 = (a11) * (b12 - b22)

        subtract(b21, b11, bResult, newTam); // b21 - b11
        strassenR(a22, bResult, p4, newTam); // p4 = (a22) * (b21 - b11)

        sum(a11, a12, aResult, newTam); // a11 + a12
        strassenR(aResult, b22, p5, newTam); // p5 = (a11+a12) * (b22)

        subtract(a21, a11, aResult, newTam); // a21 - a11
        sum(b11, b12, bResult, newTam); // b11 + b12
        strassenR(aResult, bResult, p6, newTam); // p6 = (a21-a11) * (b11+b12)

        subtract(a12, a22, aResult, newTam); // a12 - a22
        sum(b21, b22, bResult, newTam); // b21 + b22
        strassenR(aResult, bResult, p7, newTam); // p7 = (a12-a22) * (b21+b22)

        // La matriz resultado se construye de las sub-matrices c12, c21, c11 y c22

        sum(p3, p5, c12, newTam); // c12 = p3 + p5
        sum(p2, p4, c21, newTam); // c21 = p2 + p4

        sum(p1, p4, aResult, newTam); // p1 + p4
        sum(aResult, p7, bResult, newTam); // p1 + p4 + p7
        subtract(bResult, p5, c11, newTam); // c11 = p1 + p4 - p5 + p7

        sum(p1, p3, aResult, newTam); // p1 + p3
        sum(aResult, p6, bResult, newTam); // p1 + p3 + p6
        subtract(bResult, p2, c22, newTam); // c22 = p1 + p3 - p2 + p6

        // Se agrupan las 4 sub-matrices en la matriz resultado

        for (i = 0; i < newTam ; i++) {
            for (j = 0 ; j < newTam ; j++) {
                C[i][j] = c11[i][j];
                C[i][j + newTam] = c12[i][j];
                C[i + newTam][j] = c21[i][j];
                C[i + newTam][j + newTam] = c22[i][j];
            }
        }
    }
}


//Redondea el tamaño de la matriz a la siguiente potencia de dos lo
//que asegura que el algoritmo pueda dividir las matrices sin problemas y de manera eficiente
unsigned int nextPowerOfTwo(int n) {
    return pow(2, int(ceil(log2(n))));
}


//Las matrices se ajustan al tamaño más cercano de 2^k x 2^k y se realiza la multiplicación usando el algoritmo
void strassen(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, unsigned int n) {
    //unsigned int n = tam;
    unsigned int m = nextPowerOfTwo(n);
    vector<int> inner(m);
    vector< vector<int> > APrep(m, inner), BPrep(m, inner), CPrep(m, inner);

    for(unsigned int i=0; i<n; i++) {
        for (unsigned int j=0; j<n; j++) {
            APrep[i][j] = A[i][j];
            BPrep[i][j] = B[i][j];
        }
    }

    strassenR(APrep, BPrep, CPrep, m);
    for(unsigned int i=0; i<n; i++) {
        for (unsigned int j=0; j<n; j++) {
            C[i][j] = CPrep[i][j];
        }
    }
}


//Suma de matrices
void sum(vector< vector<int> > &A,
         vector< vector<int> > &B,
         vector< vector<int> > &C, int tam) {
    int i, j;

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


//Resta de matrices
void subtract(vector< vector<int> > &A,
              vector< vector<int> > &B,
              vector< vector<int> > &C, int tam) {
    int i, j;

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}


//Esta función lee las matrices desde un archivo y agrega los datos a los vectores
void read(string filename, vector<vector<int>> &matrix) {
   ifstream archivo(filename.c_str());

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo " << filename << ".\n";
        exit(EXIT_FAILURE);
    }

    string linea;
    while (getline(archivo, linea)) {
        vector<int> fila;
        istringstream iss(linea);
        int num;

        while (iss >> num) {
            fila.push_back(num);
        }
        matrix.push_back(fila);
    }
    archivo.close();

}

int main () {
    string nombreArch1 = "matriz A de dimensiones 4x4 rango de numeros de -1000 a 1000.txt";
    string nombreArch2 = "matriz B de dimensiones 4x4 rango de numeros de -1000 a 1000.txt";

    vector<vector<int>> A, B, C;

    read(nombreArch1, A);
    read(nombreArch2, B);

    if (A[0].size() != B.size()) {
        cout << "El número de columnas en la matriz A debe ser igual al número de filas en la matriz B.\n";
        exit(EXIT_FAILURE);
    }

    int n= A.size();
    C.resize(n, vector<int>(n, 0));//inicializa y establece el tamaño de la matriz C para almacenar el resultado de
    //la multiplicación de matrices
    

    //Se llama a la función y se calcula el tiempo de ejecución que es lo que se muestra por la terminal
    clock_t inicio = clock();
    
    strassen(A, B, C, n);

    clock_t fin = clock();
    double tiempoEjecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion del algoritmo: " << tiempoEjecucion << " segundos" << endl;

    /*cout << "Resultado de la multiplicacion:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
    */

    return 0;
}
