// Programa para detectar cadenas de metadatos corruptas en documentos usando la funcion Z.
// Autores: Oscar Orlando de la Paz Ibarra (A01644484), Ricardo André Mancera Ortega (A01664892)
// Fecha: 02/03/2026

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Calcula el arreglo Z de un string.
// La funcion Z en la posicion i indica cuantos caracteres desde i coinciden con el prefijo del string.
// param s: el string a analizar
// retorna: vector con los valores Z de cada posicion
// Complejidad: O(m), m es la longitud del string
vector<int> calcularFuncionZ(const string &s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// Busca la cadena de metadatos corrupta mas larga en un documento.
// Una cadena corrupta debe ser prefijo, sufijo, y aparecer al menos una vez en medio del documento.
// param doc: el contenido del documento
// retorna: la cadena corrupta si existe, o string vacio si no hay ninguna
// Complejidad: O(m), donde m es la longitud del documento
string buscarCadenaCorrupta(const string &doc) {
    int n = doc.size();
    if (n == 0) {
        return "";
    }

    vector<int> z = calcularFuncionZ(doc);

    // prefixMax[i] guarda el maximo de z[1..i] para consultar rapidamente si hay coincidencia en el medio
    vector<int> prefixMax(n, 0);
    for (int i = 1; i < n; i++) {
        prefixMax[i] = (i == 1) ? z[1] : max(prefixMax[i - 1], z[i]);
    }

    for (int longitud = n - 1; longitud >= 1; longitud--) {
        int inicioSufijo = n - longitud;

        bool esSufijo = (z[inicioSufijo] >= longitud);

        bool apareceMedio = (inicioSufijo - 1 >= 1) && (prefixMax[inicioSufijo - 1] >= longitud);

        if (esSufijo && apareceMedio) {
            return doc.substr(0, longitud);
        }
    }

    return "";
}

int main() {
    int n = 0;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string documento = "";
        getline(cin, documento);

        string cadenaCorrupta = buscarCadenaCorrupta(documento);

        if (cadenaCorrupta.empty()) {
            cout << "El documento no requiere reparacion" << endl;
        } else {
            cout << "Cadena de metadatos corrupta: " << cadenaCorrupta
                 << ", con longitud: " << cadenaCorrupta.size() << endl;
        }
    }

    return 0;
}