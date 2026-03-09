/*
 * Finding Unique Substrings
 * -------------------------
 * Encuentra todas las subcadenas únicas (que aparecen exactamente una vez)
 * en una cadena dada, utilizando Suffix Array + LCP Array.
 *
 * Entrada: una cadena por línea (se procesan múltiples casos hasta EOF).
 * Salida:  para cada caso, la cantidad de subcadenas únicas y la lista
 *          ordenada lexicográficamente de dichas subcadenas.
 *
 * Uso:  ./unique_substrings < input.txt
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// ── Construcción del Suffix Array con el algoritmo O(n log n) ──────────

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

        if (rank_[sa[n - 1]] == n - 1) break;   // ya todos son distintos
    }
    return sa;
}

// ── Construcción del LCP Array (Kasai's algorithm) O(n) ────────────────

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

// ── Encontrar subcadenas únicas ────────────────────────────────────────
//
// Una subcadena que inicia en sa[i] con longitud L es única si:
//   L > lcp[i]     (no coincide completamente con el sufijo anterior)
//   L > lcp[i+1]   (no coincide completamente con el sufijo siguiente)
//
// Las longitudes válidas para el sufijo sa[i] van desde
//   max(lcp[i], lcp[i+1]) + 1  hasta  n - sa[i]
//
// Esto nos da TODAS las subcadenas que aparecen exactamente una vez.

vector<string> findUniqueSubstrings(const string &s) {
    int n = s.size();
    if (n == 0) return {};

    vector<int> sa  = buildSuffixArray(s);
    vector<int> lcp = buildLCPArray(s, sa);

    vector<string> unique_subs;

    for (int i = 0; i < n; i++) {
        int lcpPrev = lcp[i];                         // lcp con el anterior
        int lcpNext = (i + 1 < n) ? lcp[i + 1] : 0;  // lcp con el siguiente

        int minLen = max(lcpPrev, lcpNext) + 1;
        int maxLen = n - sa[i];

        for (int len = minLen; len <= maxLen; len++) {
            unique_subs.push_back(s.substr(sa[i], len));
        }
    }

    sort(unique_subs.begin(), unique_subs.end());
    return unique_subs;
}

// ── Main ───────────────────────────────────────────────────────────────

int main() {
    string line;
    int caso = 1;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        vector<string> result = findUniqueSubstrings(line);

        cout << "=== Caso " << caso++ << " ===" << endl;
        cout << "Cadena: \"" << line << "\"" << endl;
        cout << "Subcadenas unicas: " << result.size() << endl;

        for (const string &sub : result) {
            cout << "  \"" << sub << "\"" << endl;
        }
        cout << endl;
    }

    return 0;
}