---
nombre: "Multiplicación encadenada de matrices (Godbole)"
orden: 2
nombre_corto: "Godbole"
creador: "S. S. Godbole"
fecha: "1973"
escuela: "Programación dinámica"
tiempo: "O(n³)"
espacio: "O(n²)"
---

## Para qué sirve

Encuentra el orden de asociación que minimiza las multiplicaciones escalares al multiplicar una cadena de matrices. No multiplica las matrices: solo dice dónde poner los paréntesis. Lo usan librerías numéricas para productos de varias matrices (por ejemplo, `numpy.linalg.multi_dot`), y la misma estructura resuelve la triangulación de costo mínimo de un polígono convexo y el orden de unión de tablas en bases de datos.

## Restricciones y limitaciones

- Solo sirve si conoces todas las dimensiones de antemano.
- La tabla ocupa O(n²) aunque solo te interese el resultado final.
- O(n³) basta para cadenas normales; existe un algoritmo de Hu y Shing en O(n log n), mucho más difícil de implementar.
- Con matrices pequeñas, calcular el orden puede costar más que lo que ahorra.

## Cómo funciona

La matriz k mide d[k-1] × d[k], y multiplicar n×m por m×p cuesta n·m·p. D[i,j] es el mínimo de multiplicaciones para el tramo de la matriz i a la j. Un tramo de una sola matriz cuesta 0; para los demás se prueba cada corte k:

D[i,j] = mín k (D[i,k] + D[k+1,j] + d[i-1]·d[k]·d[j])
{: .formula}

La tabla se llena por diagonales, de tramos cortos a largos, y la respuesta queda en D[1,n]. Una segunda matriz guarda la k del mínimo para reconstruir los paréntesis.

## Paradigma conveniente

Imperativo con matrices, llenado de abajo hacia arriba. También se puede escribir de forma recursiva con memorización, que es más directa de leer pero usa pila.

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
for i = 1 to n
    D[i,i] = 0
for diag = 1 to n-1
    for i = 1 to n-diag
        j = i + diag
        D[i,j] = ∞
        for k = i to j-1
            costo = D[i,k] + D[k+1,j] + d[i-1]·d[k]·d[j]
            if costo < D[i,j]
                D[i,j] = costo
                K[i,j] = k
return D[1,n]
```
{% endraw %}

</div>
<div class="pestana" data-nombre="C++" markdown="1">

{% raw %}
```cpp
#include <iostream>
#include <vector>
#include <string>

// d tiene n + 1 dimensiones: la matriz i (1..n) mide d[i-1] x d[i].
// Regresa el mínimo de multiplicaciones escalares; K guarda el mejor corte de cada tramo.
long long godbole(std::vector<int>& d, std::vector<std::vector<int>>& K) {
    int n = d.size() - 1;
    std::vector<std::vector<long long>> D(n + 1, std::vector<long long>(n + 1, 0));
    K.assign(n + 1, std::vector<int>(n + 1, 0));
    for (int diag = 1; diag <= n - 1; diag++) {
        for (int i = 1; i <= n - diag; i++) {
            int j = i + diag;
            D[i][j] = -1;
            for (int k = i; k < j; k++) {
                long long costo = D[i][k] + D[k + 1][j] + 1LL * d[i - 1] * d[k] * d[j];
                if (D[i][j] == -1 || costo < D[i][j]) {
                    D[i][j] = costo;
                    K[i][j] = k;
                }
            }
        }
    }
    return D[1][n];
}

std::string parentesis(std::vector<std::vector<int>>& K, int i, int j) {
    if (i == j) {
        return "M" + std::to_string(i);
    }
    int k = K[i][j];
    return "(" + parentesis(K, i, k) + " x " + parentesis(K, k + 1, j) + ")";
}

int main() {
    // Ejercicio de clase: 8x5, 5x9, 9x3, 3x15, 15x4
    std::vector<int> d = {8, 5, 9, 3, 15, 4};
    std::vector<std::vector<int>> K;
    long long minimo = godbole(d, K);
    int n = d.size() - 1;
    std::cout << "Multiplicaciones minimas: " << minimo << std::endl;
    std::cout << "Orden: " << parentesis(K, 1, n) << std::endl;
    return 0;
}
```
{% endraw %}

</div>
<div class="pestana" data-nombre="Python" markdown="1">

{% raw %}
```python
def godbole(d):
    n = len(d) - 1
    D = [[0] * (n + 1) for _ in range(n + 1)]
    K = [[0] * (n + 1) for _ in range(n + 1)]
    for diag in range(1, n):
        for i in range(1, n - diag + 1):
            j = i + diag
            D[i][j] = None
            for k in range(i, j):
                costo = D[i][k] + D[k + 1][j] + d[i - 1] * d[k] * d[j]
                if D[i][j] is None or costo < D[i][j]:
                    D[i][j] = costo
                    K[i][j] = k
    return D[1][n], K


def parentesis(K, i, j):
    if i == j:
        return f"M{i}"
    k = K[i][j]
    return f"({parentesis(K, i, k)} x {parentesis(K, k + 1, j)})"


# Ejercicio de clase: 8x5, 5x9, 9x3, 3x15, 15x4
d = [8, 5, 9, 3, 15, 4]
minimo, K = godbole(d)
print("Multiplicaciones minimas:", minimo)
print("Orden:", parentesis(K, 1, len(d) - 1))
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
Multiplicaciones minimas: 531
Orden: ((M1 x (M2 x M3)) x (M4 x M5))
```

## Ligas recomendadas

- [Matrix Chain Multiplication (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/matrix-chain-multiplication-dp-8/): recursión, memorización y tabla.
- [Python Program for Matrix Chain Multiplication (GeeksforGeeks)](https://www.geeksforgeeks.org/python/python-program-for-matrix-chain-multiplication-dp-8/): implementación en Python.
- [Brackets in Matrix Chain Multiplication (GeeksforGeeks)](https://www.geeksforgeeks.org/videos/brackets-in-matrix-chain-multiplication-dsa-problem/): video sobre cómo reconstruir los paréntesis.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Fue de los temas que menos intuitivos me parecieron. Nunca había pensado que el orden en que multiplicas cambia tanto el trabajo. Lo que más me costó fue leer la tabla por diagonales, con el simulador entendí que cada diagonal es un tamaño de subsecuencia, pero todavía lo tengo que pensar despacio.

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Más o menos. Entiendo que sirve cuando hay que multiplicar varias matrices seguidas y conviene decidir el orden antes. Lo que más claro me quedó es que la misma estructura sirve para otros problemas: en la Misión #7 la usé para la triangulación de costo mínimo de un polígono convexo.

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Llenar la tabla por diagonales en lugar de renglón por renglón, porque los índices i, j y k los confundo fácil. En la Misión #7 la recurrencia la saqué rápido, pero tuve que cuidar los rangos de cada ciclo.

</div>
