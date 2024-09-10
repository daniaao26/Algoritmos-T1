//El código fue sacado desde aquí:https://www.geeksforgeeks.org/sorting-a-vector-in-c/
//y luego fue modificado para cumplir con el problema

#include <bits/stdc++.h> 
using namespace std; 
  
//Si se quiere ocupar el programa los archivos con los datasets tienen que estar en la carpeta output

//Simplemente se toma un vector, se llama a la función sort
//se le da el inicio y final del vector y esta lo ordena
int main() 
{ 
    //Lectura de los datos y se agregan al vector
    string nombreArch="dataset de 10^6 numeros aleatorios ordenados de mayor a menor.txt";
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

    //Se calcula y muestra el tiempo de ejecución
    clock_t inicio = clock();
    sort(v.begin(), v.end());
    clock_t fin = clock();
    double tiempoEjecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion del algoritmo: " << tiempoEjecucion << " segundos" << endl;
 
  
    //cout << "Sorted \n"; 
    //for (auto x : v) 
    //    cout << x << " "; 
  
    return 0; 
} 