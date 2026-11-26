#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

void ordenarSeleccion(int listaOrdenar[], int cantidadDatos) {
    for (int posicion = 0; posicion < cantidadDatos - 1; posicion++) {
        int posicionMenor = posicion;
        for (int candidato = posicion + 1; candidato < cantidadDatos; candidato++) {
            if (listaOrdenar[candidato] < listaOrdenar[posicionMenor]) {
                posicionMenor = candidato;
            }
        }
        int valorGuardado = listaOrdenar[posicion];
        listaOrdenar[posicion] = listaOrdenar[posicionMenor];
        listaOrdenar[posicionMenor] = valorGuardado;
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
        // Una semilla fija permite repetir los datos en otros algoritmos.
        srand(1234 + numeroPrueba);
        for (int recorrido = 0; recorrido < cantidadDatos; recorrido++) datosPrueba[recorrido] = rand() % 100001;
        cout << "Ordenando prueba " << numeroPrueba << "..." << endl;
        auto inicioOrdenamiento = chrono::steady_clock::now();
        ordenarSeleccion(datosPrueba.data(), cantidadDatos);
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
