#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

void ordenarBurbuja(int listaOrdenar[], int cantidadDatos) {
    for (int recorrido = 0; recorrido < cantidadDatos - 1; recorrido++) {
        bool huboIntercambio = false;
        for (int vecino = 0; vecino < cantidadDatos - 1 - recorrido; vecino++) {
            if (listaOrdenar[vecino] > listaOrdenar[vecino + 1]) {
                int valorGuardado = listaOrdenar[vecino];
                listaOrdenar[vecino] = listaOrdenar[vecino + 1];
                listaOrdenar[vecino + 1] = valorGuardado;
                huboIntercambio = true;
            }
        }
        if (!huboIntercambio) break;
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
        ordenarBurbuja(datosPrueba.data(), cantidadDatos);
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
