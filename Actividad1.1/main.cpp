// =================================================================
// Actividad 1.1 - Implementación de Merge Sort (Divide y Vencerás)
// =================================================================
// Nombre: Oscar Orlando de la Paz Ibarra
// Matricula: A01644484 
//
// Nombre: Ricardo André Mancera Ortega
// Matricula: A01664892
//
// Descripción:
//   Programa que implementa el algoritmo Merge Sort utilizando la
//   técnica de divide y vencerás para ordenar N valores reales
//   (double) de mayor a menor.
//
// Entrada:
//   - Un entero N (cantidad de valores)
//   - N valores reales (double), uno por línea
//
// Salida:
//   - Los N valores ordenados de mayor a menor, uno por línea
//
// Compilación:
//   g++ -o a.out main.cpp
//
// Ejecución:
//   ./a.out < in.txt
// =================================================================

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// -----------------------------------------------------------------
// mergeDesc
//
// Descripción:
//   Función auxiliar que combina (merge) dos sub-arreglos ordenados
//   de mayor a menor en un solo sub-arreglo ordenado de mayor a
//   menor. Los sub-arreglos corresponden a a[left..mid] y
//   a[mid+1..right].
//
// Parámetros:
//   a     - vector de doubles con los datos a ordenar (por ref.)
//   temp  - vector auxiliar para la mezcla (por referencia)
//   left  - índice inicial del sub-arreglo izquierdo
//   mid   - índice final del sub-arreglo izquierdo
//   right - índice final del sub-arreglo derecho
//
// Valor de retorno:
//   void (modifica el vector 'a' in-place)
//
// Complejidad:
//   Tiempo:  O(n) donde n = right - left + 1
//   Espacio: O(n) por el uso del arreglo temporal
// -----------------------------------------------------------------
void mergeDesc(vector<double>& a, vector<double>& temp,
               int left, int mid, int right) {
    int i = left;      // índice para recorrer sub-arreglo izquierdo
    int j = mid + 1;   // índice para recorrer sub-arreglo derecho
    int k = left;      // índice para escribir en temp

    // Combinar ambos sub-arreglos en orden descendente
    while (i <= mid && j <= right) {
        if (a[i] >= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    // Copiar elementos restantes del sub-arreglo izquierdo
    while (i <= mid) {
        temp[k++] = a[i++];
    }

    // Copiar elementos restantes del sub-arreglo derecho
    while (j <= right) {
        temp[k++] = a[j++];
    }

    // Copiar resultado de temp de vuelta a 'a'
    for (int idx = left; idx <= right; idx++) {
        a[idx] = temp[idx];
    }
}

// -----------------------------------------------------------------
// mergeSortDesc
//
// Descripción:
//   Implementación recursiva del algoritmo Merge Sort utilizando
//   divide y vencerás. Ordena el sub-arreglo a[left..right] de
//   mayor a menor.
//
//   Divide y vencerás:
//     1. DIVIDE:   Partir el arreglo a la mitad (mid)
//     2. VENCE:    Ordenar recursivamente cada mitad
//     3. COMBINA:  Mezclar las dos mitades ordenadas (mergeDesc)
//
// Parámetros:
//   a     - vector de doubles con los datos a ordenar (por ref.)
//   temp  - vector auxiliar para la mezcla (por referencia)
//   left  - índice inicial del rango a ordenar
//   right - índice final del rango a ordenar
//
// Valor de retorno:
//   void (modifica el vector 'a' in-place)
//
// Complejidad:
//   Tiempo:  O(n log n) donde n = right - left + 1
//            La recurrencia es T(n) = 2T(n/2) + O(n), cuya
//            solución por el Teorema Maestro es O(n log n).
//   Espacio: O(n) por el arreglo temporal + O(log n) por la pila
//            de recursión, es decir O(n) en total.
// -----------------------------------------------------------------
void mergeSortDesc(vector<double>& a, vector<double>& temp,
                   int left, int right) {
    if (left >= right) {
        return;  // Caso base: 0 o 1 elementos, ya está ordenado
    }

    int mid = left + (right - left) / 2;  // Evita overflow

    // DIVIDE y VENCE: ordenar cada mitad recursivamente
    mergeSortDesc(a, temp, left, mid);
    mergeSortDesc(a, temp, mid + 1, right);

    // COMBINA: mezclar las dos mitades ordenadas
    mergeDesc(a, temp, left, mid, right);
}

// -----------------------------------------------------------------
// main
//
// Descripción:
//   Función principal. Lee N valores reales de la entrada estándar,
//   los ordena de mayor a menor utilizando Merge Sort y los imprime.
//
// Complejidad:
//   Tiempo:  O(n log n) dominado por el Merge Sort
//   Espacio: O(n) para el vector de datos y el vector temporal
// -----------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<double> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n > 1) {
        vector<double> temp(n);
        mergeSortDesc(a, temp, 0, n - 1);
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << "\n";
    }

    return 0;
}
