// El código fue sacado desde aquí: https://www.geeksforgeeks.org/bubble-sort-in-cpp/ 
// y luego fue modificado para cumplir con los requisitos del problema. 

#include <bits/stdc++.h>

using namespace std;

//Si se quiere ocupar el programa los archivos con los datasets tienen que estar en la carpeta output
//Se comparan los dos primeros elementos y si están en el orden incorrecto se intercambian
//Se continúa este proceso con todos los elementos, moviendose de izquierda a derecha
//Después del primer paso el elemento mas grande se encuentra en la ultima posición
//Se repite hasta que el arreglo esté ordenado

void bubbleSort(vector<int>& v) {
    int n = v.size();

    //Loop exterior que corresponde al número de elementos a ordenar}}
    for (int i = 0; i < n - 1; i++) {

        //los últimos i elementos ya están en su lugar
        for (int j = 0; j < n - i - 1; j++) {
          
            //Se comparan los elementos adyacentes
            if (v[j] > v[j + 1])
              
                //Se intercambian si están en el orden incorrecto
                swap(v[j], v[j + 1]);
        }
    }
}

int main() {

    //Entrada del archivo que luego es pasado a vector para que lo ordene el programa
    string nombreArch="dataset 2 de 10^6 numeros aleatorios ordenados de mayor a menor.txt";
    ifstream archivo(nombreArch.c_str());


    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo.\n"; 
        exit(EXIT_FAILURE);
    }


    vector<int> v;
    string linea;


    while (getline(archivo, linea)) {
        int numero = stoi(linea);
        v.push_back(numero);
    }

    archivo.close();

    //Se calcula el tiempo de ejecución del algoritmo y eso es lo que se muestra por pantalla
    clock_t inicio = clock();
    bubbleSort(v);
    clock_t fin = clock();
    double tiempoEjecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion del algoritmo: " << tiempoEjecucion << " segundos" << endl;
    
    //for (auto i : v){
    //    cout << i <<endl;
    //}

    
    
    return 0;
}
