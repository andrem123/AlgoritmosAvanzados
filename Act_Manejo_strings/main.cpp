/*
 * Finding Unique Substrings
 * Encuentra todas las subcadenas que aparecen exactamente una vez
 * en una cadena dada, usando Suffix Array + LCP Array.
 *
 * Aplicacion practica:
 *   En bioinformatica, encontrar secuencias unicas de ADN sirve
 *   para disenar primers de PCR que identifiquen organismos especificos.
 *
 * Entrada: cadenas por linea (redireccion de archivo)
 * Salida:  subcadenas unicas ordenadas lexicograficamente
 *
 * Compilar: g++ -std=c++17 -o main main.cpp
 * Ejecutar: main < input.txt       (Windows)
 *           ./main < input.txt     (Linux/Mac)
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Construir Suffix Array - O(n log^2 n)
vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
    vector<int> sa(n), rank_(n), tmp(n);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank_[i] = s[i];
    }

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rank_[a] != rank_[b]) return rank_[a] < rank_[b];
            int ra = (a + k < n) ? rank_[a + k] : -1;
            int rb = (b + k < n) ? rank_[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rank_ = tmp;

        if (rank_[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

// Construir LCP Array con algoritmo de Kasai - O(n)
vector<int> buildLCPArray(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank_(n), lcp(n, 0);

    for (int i = 0; i < n; i++) rank_[sa[i]] = i;

    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rank_[i] > 0) {
            int j = sa[rank_[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[rank_[i]] = h;
            if (h > 0) h--;
        } else {
            h = 0;
        }
    }
    return lcp;
}

// Encontrar subcadenas unicas (aparecen exactamente 1 vez)
vector<string> findUniqueSubstrings(const string &s) {
    int n = s.size();
    if (n == 0) return {};

    vector<int> sa  = buildSuffixArray(s);
    vector<int> lcp = buildLCPArray(s, sa);

    vector<string> result;

    for (int i = 0; i < n; i++) {
        int lcpPrev = lcp[i];
        int lcpNext = (i + 1 < n) ? lcp[i + 1] : 0;

        int minLen = max(lcpPrev, lcpNext) + 1;
        int maxLen = n - sa[i];

        for (int len = minLen; len <= maxLen; len++)
            result.push_back(s.substr(sa[i], len));
    }

    sort(result.begin(), result.end());
    return result;
}

int main() {
    string line;
    int caso = 1;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        vector<string> unicas = findUniqueSubstrings(line);

        cout << "=== Caso " << caso++ << " ===" << endl;
        cout << "Cadena: \"" << line << "\"" << endl;
        cout << "Subcadenas unicas: " << unicas.size() << endl;

        for (const string &s : unicas)
            cout << "  \"" << s << "\"" << endl;
        cout << endl;
    }

    return 0;
}