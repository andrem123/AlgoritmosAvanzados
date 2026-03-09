# Casos de Prueba — Finding Unique Substrings

## Caso 1: `banana`

**Justificación:** Cadena con muchas repeticiones parciales ("an", "ana", "na", "a", "n"). 
Permite verificar que el programa distingue correctamente entre subcadenas repetidas y únicas.

**Subcadenas repetidas (NO deben aparecer):**
- `"a"` aparece 3 veces → NO es única
- `"an"` aparece 2 veces → NO es única  
- `"ana"` aparece 2 veces → NO es única
- `"n"` aparece 2 veces → NO es única
- `"na"` aparece 2 veces → NO es única

**Resultado esperado: 10 subcadenas únicas**
```
"anan", "anana", "b", "ba", "ban", "bana", "banan", "banana", "nan", "nana"
```

---

## Caso 2: `abcabc`

**Justificación:** Cadena formada por una repetición exacta (`"abc"` + `"abc"`).
Verifica que las subcadenas compartidas por ambas mitades (`"a"`, `"b"`, `"c"`, `"ab"`, `"bc"`, `"abc"`) 
se excluyan correctamente al aparecer más de una vez.

**Subcadenas repetidas (NO deben aparecer):**
- `"a"`, `"b"`, `"c"` aparecen 2 veces cada una
- `"ab"`, `"bc"`, `"abc"` aparecen 2 veces cada una

**Resultado esperado: 9 subcadenas únicas**
```
"abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "ca", "cab", "cabc"
```

---

## Caso 3: `abcdef`

**Justificación:** Cadena sin ningún carácter repetido. 
Cada subcadena posible aparece exactamente una vez, por lo que TODAS son únicas.
El total de subcadenas de una cadena de longitud n es n*(n+1)/2 = 6*7/2 = 21.

**Resultado esperado: 21 subcadenas únicas**
```
"a", "ab", "abc", "abcd", "abcde", "abcdef",
"b", "bc", "bcd", "bcde", "bcdef",
"c", "cd", "cde", "cdef",
"d", "de", "def",
"e", "ef",
"f"
```