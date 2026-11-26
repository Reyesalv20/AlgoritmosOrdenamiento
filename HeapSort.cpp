#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

void ajustarMonticulo(int listaOrdenar[], int cantidadDatos, int raiz) {
    int posicionMayor = raiz;
    int hijoIzquierdo = 2 * raiz + 1;
    int hijoDerecho = 2 * raiz + 2;

    if (hijoIzquierdo < cantidadDatos &&
        listaOrdenar[hijoIzquierdo] > listaOrdenar[posicionMayor]) {
        posicionMayor = hijoIzquierdo;
    }
    if (hijoDerecho < cantidadDatos &&
        listaOrdenar[hijoDerecho] > listaOrdenar[posicionMayor]) {
        posicionMayor = hijoDerecho;
    }

    if (posicionMayor != raiz) {
        int valorGuardado = listaOrdenar[raiz];
        listaOrdenar[raiz] = listaOrdenar[posicionMayor];
        listaOrdenar[posicionMayor] = valorGuardado;
        ajustarMonticulo(listaOrdenar, cantidadDatos, posicionMayor);
    }
}

void ordenarMonticulo(int listaOrdenar[], int cantidadDatos) {
    for (int raiz = cantidadDatos / 2 - 1; raiz >= 0; raiz--) {
        ajustarMonticulo(listaOrdenar, cantidadDatos, raiz);
    }
    for (int ultimo = cantidadDatos - 1; ultimo > 0; ultimo--) {
        int valorGuardado = listaOrdenar[0];
        listaOrdenar[0] = listaOrdenar[ultimo];
        listaOrdenar[ultimo] = valorGuardado;
        ajustarMonticulo(listaOrdenar, ultimo, 0);
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
        ordenarMonticulo(datosPrueba.data(), cantidadDatos);
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
