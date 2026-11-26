#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

void ordenarInsercion(int listaOrdenar[], int cantidadDatos) {
    for (int posicion = 1; posicion < cantidadDatos; posicion++) {
        int valorInsertar = listaOrdenar[posicion];
        int anterior = posicion - 1;

        while (anterior >= 0 && listaOrdenar[anterior] > valorInsertar) {
            listaOrdenar[anterior + 1] = listaOrdenar[anterior];
            anterior--;
        }
        listaOrdenar[anterior + 1] = valorInsertar;
    }
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
    for (int numeroPrueba = 1; numeroPrueba <= 3; numeroPrueba++) {
        srand(1234 + numeroPrueba);
        for (int recorrido = 0; recorrido < cantidadDatos; recorrido++) datosPrueba[recorrido] = rand() % 100001;
        cout << "Ordenando prueba " << numeroPrueba << "..." << endl;
        auto inicioOrdenamiento = chrono::steady_clock::now();
        ordenarInsercion(datosPrueba.data(), cantidadDatos);
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
    cout << "Promedio: " << totalMilisegundos / 3 << " ms\n";
    return 0;
}
