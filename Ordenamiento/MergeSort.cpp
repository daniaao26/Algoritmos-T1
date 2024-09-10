//El algoritmo fue extraído desde aquí: https://www.geeksforgeeks.org/cpp-program-for-merge-sort/
//y después fue modificado para cumplir con el problema

#include <bits/stdc++.h>

//Se divide el arreglo en subarreglos mas pequeños, luego se ordena cada subarreglo y se fusionan
//Se calcula el punto medio del arreglo
//Se divide el arreglo en mitades iguales usando el punto medio
//Para cada subarreglo se calcula el punto medio y se dividen los subarreglos 
//hasta alcanzar un arreglo donde no se pueden hacer mas divisiones
//Y desde ahí se empiezan combinar los elementos nuevamente utilizando el merge
//En el proceso de fusión se comparan los elementos de cada lista y luego
//se combinan en otra lista de manera ordenada



//Si se quiere ocupar el programa los archivos con los datasets tienen que estar en la carpeta output

using namespace std;

//Fusiona dos subarreglos del vector
//El primer subarreglo es vec[izquierda...centro]
//El segundo subarreglo es vec[centro+1...derecha]

void merge(vector<int>& vec, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //Vectores temporales
    vector<int> leftVec(n1), rightVec(n2);

    //Se copian los datos a los vectores temporales
    for (i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];
    for (j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];

    //Se fusionan los vectores temporales de vuelta en vec[izquierda]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    //Si es que los hay se copian los elementos restantes de leftVec[]
    while (i < n1) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    //Si es que los hay se copian los elementos restantes de rightVec[]
    while (j < n2) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}

//El subarreglo a ordenar está en el rango de índices[izq...der]
void mergeSort(vector<int>& vec, int left, int right) {
    if (left < right) {
      
        //Se calcula el punto medio
        int mid = left + (right - left) / 2;

        //Se ordenan la primera y la segunda mitad
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        //Se fusionan las mitades ordenadas
        merge(vec, left, mid, right);
    }
}

int main() {
    //Entrada del archivo que luego es pasado a vector para que lo ordene el programa
    string nombreArch="dataset de 10^3 numeros aleatorios.txt";
    ifstream archivo(nombreArch.c_str());

    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo.\n"; 
        exit(EXIT_FAILURE);
    }
    
    vector<int> vec;
    string linea;

    while (getline(archivo, linea)) {
        int numero = stoi(linea);
        vec.push_back(numero);
    }

    archivo.close();
    int n = vec.size();

    //Se ordena y calcula el tiempo de ejecución del algoritmo y eso es lo que se muestra por pantalla

    clock_t inicio = clock();
    mergeSort(vec, 0, n - 1);
    clock_t fin = clock();

    double tiempoEjecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion del algoritmo: " << tiempoEjecucion << " segundos" << endl;

    //for (auto i: vec)
    //    cout << i << " ";
    
    return 0;
}
