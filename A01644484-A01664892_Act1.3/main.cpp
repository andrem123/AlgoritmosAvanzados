/*
 * Actividad 1.3 - Backtracking: Subset Sum
 * A01644484 - A01664892
 *
 * Encuentra todas las combinaciones de estudiantes cuyas aportaciones
 * sumen exactamente el costo de la factura, usando backtracking con poda.
 *
 * Compilar: g++ -o main main.cpp
 * Ejecutar: ./main < inputFile.txt
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

int n, c;
vector<string> nombres;
vector<int> aportes;
vector<int> seleccion;    // índices seleccionados en la combinación actual
int totalCombinaciones = 0;

// suffixSum[i] = suma de aportes[i] + aportes[i+1] + ... + aportes[n-1]
vector<int> suffixSum;

/*
 * Backtracking con poda.
 *   idx:       índice actual en la lista de estudiantes.
 *   sumaActual: suma acumulada de los estudiantes seleccionados hasta ahora.
 *
 * Poda 1: si sumaActual ya excede c, cortar.
 * Poda 2: si sumaActual + la suma de todos los elementos restantes < c, cortar
 *          (no hay forma de alcanzar c ni tomando todos los restantes).
 *
 * Complejidad: O(2^n) en el peor caso, pero las podas reducen
 * significativamente el espacio de búsqueda.
 */
void backtrack(int idx, int sumaActual) {
    // Caso base: encontramos una combinación válida
    if (sumaActual == c) {
        for (int i : seleccion) {
            cout << nombres[i] << ": " << aportes[i] << endl;
        }
        cout << "--------------------------" << endl;
        cout << "Total: " << c << endl;
        cout << endl;
        totalCombinaciones++;
        return;
    }

    // Poda 1: la suma ya excede el objetivo
    if (sumaActual > c) return;

    // Ya recorrimos todos los estudiantes sin alcanzar c
    if (idx >= n) return;

    // Poda 2: incluso tomando todos los restantes no se alcanza c
    if (sumaActual + suffixSum[idx] < c) return;

    // Rama: incluir al estudiante idx
    seleccion.push_back(idx);
    backtrack(idx + 1, sumaActual + aportes[idx]);
    seleccion.pop_back();

    // Rama: no incluir al estudiante idx
    backtrack(idx + 1, sumaActual);
}

int main() {
    // Lectura de entrada
    cin >> n >> c;

    nombres.resize(n);
    aportes.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> nombres[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> aportes[i];
    }

    // Precalcular suffix sums para la poda
    suffixSum.resize(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        suffixSum[i] = suffixSum[i + 1] + aportes[i];
    }

    // Ejecutar backtracking
    cout << "Combinaciones posibles:" << endl;
    backtrack(0, 0);

    cout << endl;
    cout << "Total de combinaciones encontradas: " << totalCombinaciones << endl;

    return 0;
}
