# Casos de Prueba — Análisis de Marcadores Genéticos Únicos en ADN

## Caso 1: `ATCGATCGATCG`

**Justificación bioinformática:** Secuencia con patrón repetitivo `ATCG` (4 nucleótidos repetidos 3 veces).
Simula regiones repetitivas del genoma (microsatélites / STRs). Las repeticiones internas
harán que muchas subcadenas cortas aparezcan más de una vez, filtrando los falsos marcadores.

- **Longitud:** 12 nt
- **GC Content:** 50.0% (equilibrado)
- Solo las subcadenas que cruzan los límites de la repetición de manera asimétrica serán únicas.
- Subcadenas como `"ATC"`, `"TCG"`, `"CGA"`, `"GAT"` aparecen múltiples veces → NO son únicas.

---

## Caso 2: `AAACCCGGGTTT`

**Justificación bioinformática:** Secuencia con bloques homopoliméricos (runs de la misma base).
Representa regiones de baja complejidad comunes en genomas reales. El algoritmo debe
identificar correctamente que runs internos como `"AAA"`, `"CCC"`, etc. son únicos
(aparecen una sola vez cada bloque).

- **Longitud:** 12 nt
- **GC Content:** 50.0%
- Las subcadenas que están completamente dentro de un bloque son interesantes
  porque cada base solo aparece en un bloque contiguo.

---

## Caso 3: `ACGTACGT`

**Justificación bioinformática:** Secuencia palindrómica corta (ACGT repetido).
En genomas reales, los palíndromos son sitios de reconocimiento de enzimas de restricción.
Verifica comportamiento con repeticiones exactas de 4 nt, donde muchas subcadenas se
duplican entre las dos mitades.

- **Longitud:** 8 nt
- **GC Content:** 50.0%
- Subcadenas repetidas (NO marcadores): `"A"`, `"C"`, `"G"`, `"T"`, `"AC"`, `"CG"`, `"GT"`, `"ACG"`, `"CGT"`, `"ACGT"`
- Solo las subcadenas que cruzan la frontera entre las dos repeticiones serán únicas.

---

## Notas sobre el filtro de longitud

El programa filtra marcadores en el rango **[3, 8] nucleótidos** para las secuencias de demo.
En aplicaciones reales de PCR, los primers tienen entre 18-25 nucleótidos. El rango corto
se usa aquí para que los resultados sean visibles con secuencias de entrada cortas.