# Casos de Prueba — Finding Unique Substrings

## Caso 1: `panama`

Cadena con repeticiones parciales ("a" aparece 3 veces, "pa" no se repite). Verifica que las subcadenas repetidas se excluyan.

**Resultado esperado: 18 subcadenas unicas**
```
"am", "ama", "an", "ana", "anam", "anama", "m", "ma",
"n", "na", "nam", "nama", "p", "pa", "pan", "pana", "panam", "panama"
```

---

## Caso 2: `abcabc`

Cadena formada por "abc" repetido dos veces. Las subcadenas compartidas ("a", "b", "c", "ab", "bc", "abc") no son unicas.

**Resultado esperado: 9 subcadenas unicas**
```
"abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "ca", "cab", "cabc"
```

---

## Caso 3: `abcdef`

Cadena sin caracteres repetidos. Todas las subcadenas posibles son unicas: n*(n+1)/2 = 6*7/2 = 21.

**Resultado esperado: 21 subcadenas unicas**
```
"a", "ab", "abc", "abcd", "abcde", "abcdef",
"b", "bc", "bcd", "bcde", "bcdef",
"c", "cd", "cde", "cdef",
"d", "de", "def",
"e", "ef",
"f"
```