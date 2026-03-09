/*
 * Análisis de Marcadores Genéticos Únicos en ADN
 * ────────────────────────────────────────────────
 * Aplicación real del algoritmo de Suffix Array + LCP Array para
 * encontrar subsecuencias únicas en fragmentos de ADN.
 *
 * Problemática:
 *   En bioinformática, identificar subsecuencias que aparecen exactamente
 *   UNA vez en un fragmento de ADN es crucial para:
 *     • Diseño de primers para PCR (Polymerase Chain Reaction)
 *     • Identificación de marcadores genéticos específicos
 *     • Detección de regiones diagnósticas únicas de un organismo
 *
 * Entrada: secuencias de ADN (caracteres A, C, G, T), una por línea.
 * Salida:  para cada secuencia, análisis completo de marcadores únicos
 *          filtrados por longitud y con estadísticas bioinformáticas.
 *
 * Uso:  ./dna_markers < input.txt
 *
 * Complejidad:
 *   - Suffix Array:  O(n log²n)
 *   - LCP (Kasai):   O(n)
 *   - Total:         O(n log²n)
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

// ── Construcción del Suffix Array con el algoritmo O(n log²n) ──────────

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

vector<string> findUniqueSubstrings(const string &s,
                                     int minLen = 1,
                                     int maxLenLimit = -1) {
    int n = s.size();
    if (n == 0) return {};

    vector<int> sa  = buildSuffixArray(s);
    vector<int> lcp = buildLCPArray(s, sa);

    if (maxLenLimit == -1) maxLenLimit = n;

    vector<string> unique_subs;

    for (int i = 0; i < n; i++) {
        int lcpPrev = lcp[i];
        int lcpNext = (i + 1 < n) ? lcp[i + 1] : 0;

        int lo = max(lcpPrev, lcpNext) + 1;
        int hi = n - sa[i];

        // Aplicar filtro de longitud
        lo = max(lo, minLen);
        hi = min(hi, maxLenLimit);

        for (int len = lo; len <= hi; len++) {
            unique_subs.push_back(s.substr(sa[i], len));
        }
    }

    sort(unique_subs.begin(), unique_subs.end());
    return unique_subs;
}

// ── Utilidades bioinformáticas ─────────────────────────────────────────

// Validar que la secuencia solo contenga nucleótidos válidos
bool isValidDNA(const string &seq) {
    for (char c : seq) {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') return false;
    }
    return !seq.empty();
}

// Calcular el contenido GC% de una secuencia
double gcContent(const string &seq) {
    int gc = 0;
    for (char c : seq) {
        if (c == 'G' || c == 'C') gc++;
    }
    return (seq.empty()) ? 0.0 : (100.0 * gc / seq.size());
}

// Obtener la cadena complementaria reversa (reverse complement)
string reverseComplement(const string &seq) {
    string rc(seq.rbegin(), seq.rend());
    for (char &c : rc) {
        switch (c) {
            case 'A': c = 'T'; break;
            case 'T': c = 'A'; break;
            case 'C': c = 'G'; break;
            case 'G': c = 'C'; break;
        }
    }
    return rc;
}

// ── Main ───────────────────────────────────────────────────────────────

int main() {
    string line;
    int caso = 1;

    // Longitudes de filtro para marcadores genéticos
    // En PCR real: 18-25 nt, aquí usamos 3-8 para secuencias cortas de demo.
    const int MIN_MARKER_LEN = 3;
    const int MAX_MARKER_LEN = 8;

    cout << "+=========================================================+" << endl;
    cout << "|   Analizador de Marcadores Geneticos Unicos en ADN      |" << endl;
    cout << "|   Suffix Array + LCP Array                              |" << endl;
    cout << "+=========================================================+" << endl;
    cout << endl;
    cout << "Filtro de longitud de marcadores: ["
         << MIN_MARKER_LEN << ", " << MAX_MARKER_LEN << "] nucleotidos" << endl;
    cout << endl;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        // Convertir a mayúsculas por si acaso
        for (char &c : line) c = toupper(c);

        cout << "=========================================================" << endl;
        cout << "  Caso " << caso++ << endl;
        cout << "=========================================================" << endl;

        // Validación de ADN
        if (!isValidDNA(line)) {
            cout << "  [!] Secuencia invalida (solo A, C, G, T): \"" << line << "\"" << endl;
            cout << endl;
            continue;
        }

        cout << "  Secuencia:   5'-" << line << "-3'" << endl;
        cout << "  Longitud:    " << line.size() << " nt" << endl;
        cout << "  GC Content:  " << fixed << setprecision(1)
             << gcContent(line) << "%" << endl;
        cout << "  Complemento: 3'-" << reverseComplement(line) << "-5'" << endl;
        cout << endl;

        // --- Todas las subcadenas únicas (sin filtro) ---
        vector<string> allUnique = findUniqueSubstrings(line);
        cout << "  Total subcadenas unicas (todas las longitudes): "
             << allUnique.size() << endl;

        // --- Marcadores filtrados por longitud ---
        vector<string> markers = findUniqueSubstrings(line,
                                                       MIN_MARKER_LEN,
                                                       MAX_MARKER_LEN);

        cout << "  Marcadores unicos [" << MIN_MARKER_LEN << "-"
             << MAX_MARKER_LEN << " nt]: " << markers.size() << endl;
        cout << endl;

        if (!markers.empty()) {
            // Distribución por longitud
            map<int, int> distrib;
            for (const string &m : markers) distrib[m.size()]++;

            cout << "  Distribucion por longitud:" << endl;
            for (auto &[len, cnt] : distrib) {
                cout << "    " << len << " nt: " << cnt << " marcador(es)" << endl;
            }
            cout << endl;

            // Listar los marcadores con su info
            cout << "  Marcadores encontrados:" << endl;
            cout << "  +-------+--------------+---------+----------------+" << endl;
            cout << "  |  #    |  Marcador    |  GC%    |  Rev. Compl.   |" << endl;
            cout << "  +-------+--------------+---------+----------------+" << endl;

            int idx = 1;
            for (const string &m : markers) {
                string rc = reverseComplement(m);
                cout << "  | " << setw(4) << idx++ << "  | "
                     << setw(12) << left << m << " | "
                     << setw(6) << right << fixed << setprecision(1)
                     << gcContent(m) << "% | "
                     << setw(14) << left << rc << " |" << endl;
            }
            cout << "  +-------+--------------+---------+----------------+" << endl;
        } else {
            cout << "  (No se encontraron marcadores en el rango especificado)" << endl;
        }
        cout << endl;
    }

    return 0;
}