// El código fue adquirido desde aquí: https://www.geeksforgeeks.org/cpp-program-for-quicksort/
//Luego fue modificado para cumplir con el problema



//Se ocupa partition() para seleccionar un elemento pivote y reorganizar el arreglo
//de manera que todos los elementos menores al pivote se coloquen a su izquierda y los mayores a la derecha
//El punto donde se coloca el pivote se llama índice de partición y se retorna a quickSort()

//quickSort() es la función principal que divide el arreglo en dos subarreglos basados en el índice de partición
//luego se llama recursivamente a quickSort() para ordenar los subarreglos


//Si se quiere ocupar el programa los archivos con los datasets tienen que estar en la carpeta output

#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &vec, int low, int high) {

    //Como vimos en el informe ocupar como pivote el último número nos deja una recursión muy profunda 
    //y no se pueden utilizar todos los casos por lo que se modificó para que el pivote sea el número del medio 
    //y luego fuera cambiado con el de al final ya que el método en la ejecución siempre ocupa el último elemento como pivote
    int mid = low + (high - low) / 2;
    swap(vec[mid], vec[high]);

    int pivot = vec[high];

    //índice del elemento justo antes del último elemento, se usa para intercambiar
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // Se compara si el elemento actual es menor o igual al pivote
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    //Se coloca el pivote en su posición
    swap(vec[i + 1], vec[high]);

    //Retorna el punto de partición
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {

    //Esta parte se ejecutará hasta que el índice de inicio low sea menor que el índice final high
    if (low < high) {

        // p es el índice de partición , arr[p] está ahora en el lugar correcto
        int p = partition(vec, low, high);

        //Ordenar separadamente los elementos antes y después del índice de partición p
        quickSort(vec, low, p - 1);
        quickSort(vec, p + 1, high);
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

    int N = vec.size();
    
    //cout << "Unsorted Array: \n";
    //for (auto i : vec) {
    //    cout << i << " ";
    //}
    //cout << endl;
    
    //Se ordena y calcula el tiempo de ejecución del algoritmo y eso es lo que se muestra por pantalla

    clock_t inicio = clock();
    quickSort(vec, 0, N - 1);
    clock_t fin = clock();

    //cout << "Sorted Array: \n";
    //for (auto i : vec) {
    //    cout << i << " ";
    //}
    double tiempoEjecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion del algoritmo: " << tiempoEjecucion << " segundos" << endl;
    return 0;
}
