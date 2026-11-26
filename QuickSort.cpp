#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

void ordenarRapido(int listaOrdenar[], int inicio, int fin) {
    if (inicio >= fin) return;

    int pivote = listaOrdenar[inicio + (fin - inicio) / 2];
    int izquierda = inicio;
    int derecha = fin;

    while (izquierda <= derecha) {
        while (listaOrdenar[izquierda] < pivote) izquierda++;
        while (listaOrdenar[derecha] > pivote) derecha--;

        if (izquierda <= derecha) {
            int valorGuardado = listaOrdenar[izquierda];
            listaOrdenar[izquierda] = listaOrdenar[derecha];
            listaOrdenar[derecha] = valorGuardado;
            izquierda++;
            derecha--;
        }
    }

    if (inicio < derecha) ordenarRapido(listaOrdenar, inicio, derecha);
    if (izquierda < fin) ordenarRapido(listaOrdenar, izquierda, fin);
}

int main() {
    int cantidadDatos;
    cout << "Cantidad de elementos: ";
    if (!(cin >> cantidadDatos) || cantidadDatos <= 0) {
        cout << "Escribe un entero mayor que cero.\n";
        return 1;
    }
    vector<int> datosPrueba(cantidadDatos);
    double totalMilisegundos = 0;
    cout << fixed << setprecision(6);
    for (int numeroPrueba = 1; numeroPrueba <= 6; numeroPrueba++) {
        srand(1234 + numeroPrueba);
        for (int recorrido = 0; recorrido < cantidadDatos; recorrido++) datosPrueba[recorrido] = rand() % 100001;
        cout << "Ordenando prueba " << numeroPrueba << "..." << endl;
        auto inicioOrdenamiento = chrono::steady_clock::now();
        ordenarRapido(datosPrueba.data(), 0, cantidadDatos - 1);
        auto finOrdenamiento = chrono::steady_clock::now();
        double milisegundos = chrono::duration<double, milli>(finOrdenamiento - inicioOrdenamiento).count();
        for (int recorrido = 1; recorrido < cantidadDatos; recorrido++) {
            if (datosPrueba[recorrido - 1] > datosPrueba[recorrido]) {
                cout << "Error: el arreglo no quedo ordenado.\n";
                return 1;
            }
        }
        cout << "Prueba " << numeroPrueba << ": " << milisegundos << " ms" << endl;
        totalMilisegundos += milisegundos;
    }
    cout << "Promedio: " << totalMilisegundos / 6 << " ms\n";
    return 0;
}
