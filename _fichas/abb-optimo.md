---
nombre: "ABB óptimo (Gilbert y Moore)"
orden: 3
nombre_corto: "ABB óptimo"
creador: "Edgar Gilbert y Edward Moore"
fecha: "1959"
escuela: "Programación dinámica"
tiempo: "O(n³)"
espacio: "O(n²)"
---

## Para qué sirve

Construye el árbol binario de búsqueda con el menor número promedio de comparaciones cuando se conoce la probabilidad de buscar cada llave. Sirve para conjuntos fijos que se consultan mucho: tablas de palabras reservadas en un compilador, diccionarios o correctores con frecuencias de uso conocidas, y menús o catálogos donde unas opciones se consultan mucho más que otras.

## Restricciones y limitaciones

- Las llaves y sus probabilidades deben conocerse de antemano.
- Si se agregan llaves o cambian las frecuencias, hay que reconstruir el árbol.
- Para datos que cambian seguido conviene un árbol que se ajuste solo, como un AVL o un splay tree.
- Knuth (1971) lo bajó a O(n²) limitando dónde buscar la raíz; la versión básica es O(n³).

## Cómo funciona

A[i,j] es el promedio mínimo de comparaciones para un árbol con las llaves de la i a la j. Un árbol de una sola llave cuesta su probabilidad: A[i,i] = p[i]. Para los demás se prueba cada llave k como raíz; los dos subárboles bajan un nivel, así que se suman todas las probabilidades del tramo:

A[i,j] = mín k (A[i,k-1] + A[k+1,j]) + Σ p[i..j]
{: .formula}

Se llena por diagonales, igual que Godbole, y la respuesta queda en A[1,n]. Una matriz R guarda la raíz de cada tramo para construir el árbol de forma recursiva.

## Paradigma conveniente

Imperativo con matrices para la tabla y recursivo para construir el árbol a partir de R, con nodos y apuntadores.

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
for i = 1 to n
    A[i,i-1] = 0
    A[i,i] = p[i]
    R[i,i] = i
A[n+1,n] = 0
for diag = 1 to n-1
    for i = 1 to n-diag
        j = i + diag
        A[i,j] = ∞
        for k = i to j
            costo = A[i,k-1] + A[k+1,j]
            if costo < A[i,j]
                A[i,j] = costo
                R[i,j] = k
        A[i,j] = A[i,j] + suma(p[i..j])
return A[1,n]
```
{% endraw %}

</div>
<div class="pestana" data-nombre="C++" markdown="1">

{% raw %}
```cpp
#include <iostream>
#include <vector>
#include <string>

// p[1..n] son las probabilidades de las llaves ordenadas (p[0] no se usa).
// Regresa el promedio mínimo de comparaciones; R[i][j] guarda la raíz del tramo i..j.
double abbOptimo(std::vector<double>& p, std::vector<std::vector<int>>& R) {
    int n = p.size() - 1;
    std::vector<std::vector<double>> A(n + 2, std::vector<double>(n + 1, 0));
    R.assign(n + 2, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        A[i][i] = p[i];
        R[i][i] = i;
    }
    for (int diag = 1; diag <= n - 1; diag++) {
        for (int i = 1; i <= n - diag; i++) {
            int j = i + diag;
            double suma = 0;
            for (int t = i; t <= j; t++) {
                suma += p[t];
            }
            A[i][j] = -1;
            for (int k = i; k <= j; k++) {
                double costo = A[i][k - 1] + A[k + 1][j] + suma;
                if (A[i][j] < 0 || costo < A[i][j]) {
                    A[i][j] = costo;
                    R[i][j] = k;
                }
            }
        }
    }
    return A[1][n];
}

// Muestra el árbol en preorden: raíz, subárbol izquierdo, subárbol derecho.
void mostrar(std::vector<std::vector<int>>& R, std::vector<std::string>& llaves, int i, int j, int nivel) {
    if (i > j) {
        return;
    }
    int k = R[i][j];
    std::cout << std::string(nivel * 4, ' ') << llaves[k] << std::endl;
    mostrar(R, llaves, i, k - 1, nivel + 1);
    mostrar(R, llaves, k + 1, j, nivel + 1);
}

int main() {
    // Ejercicio de clase, con las llaves en orden alfabético
    std::vector<std::string> llaves = {"", "a", "con", "de", "el", "y"};
    std::vector<double> p = {0, 0.25, 0.17, 0.25, 0.20, 0.13};
    std::vector<std::vector<int>> R;
    double promedio = abbOptimo(p, R);
    std::cout << "Promedio de comparaciones: " << promedio << std::endl;
    mostrar(R, llaves, 1, p.size() - 1, 0);
    return 0;
}
```
{% endraw %}

</div>
<div class="pestana" data-nombre="Python" markdown="1">

{% raw %}
```python
def abb_optimo(p):
    # p[1..n] son las probabilidades; p[0] no se usa
    n = len(p) - 1
    A = [[0.0] * (n + 1) for _ in range(n + 2)]
    R = [[0] * (n + 1) for _ in range(n + 2)]
    for i in range(1, n + 1):
        A[i][i] = p[i]
        R[i][i] = i
    for diag in range(1, n):
        for i in range(1, n - diag + 1):
            j = i + diag
            suma = sum(p[i:j + 1])
            A[i][j] = None
            for k in range(i, j + 1):
                costo = A[i][k - 1] + A[k + 1][j] + suma
                if A[i][j] is None or costo < A[i][j]:
                    A[i][j] = costo
                    R[i][j] = k
    return A[1][n], R


def mostrar(R, llaves, i, j, nivel=0):
    if i > j:
        return
    k = R[i][j]
    print("    " * nivel + llaves[k])
    mostrar(R, llaves, i, k - 1, nivel + 1)
    mostrar(R, llaves, k + 1, j, nivel + 1)


# Ejercicio de clase, con las llaves en orden alfabético
llaves = ["", "a", "con", "de", "el", "y"]
p = [0, 0.25, 0.17, 0.25, 0.20, 0.13]
promedio, R = abb_optimo(p)
print("Promedio de comparaciones:", round(promedio, 2))
mostrar(R, llaves, 1, len(p) - 1)
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
Promedio de comparaciones: 2.05
de
    a
        con
    el
        y
```

## Ligas recomendadas

- [Optimal Binary Search Tree (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/optimal-binary-search-tree-dp-24/): recurrencia y tabla con frecuencias.
- [Optimal binary search tree, problema de práctica (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/optimal-binary-search-tree2214/1): para practicar con casos de prueba.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Al principio no entendía por qué regresar a búsqueda si ya teníamos búsqueda binaria y árboles AVL. Me hizo sentido cuando vi que aquí ya conoces la probabilidad de buscar cada dato, y entonces el árbol balanceado deja de ser el mejor. Lo terminé de entender con la comparación con Godbole

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Solo en casos donde los datos no cambian y sí sé qué se busca más, como una tabla de palabras reservadas o un diccionario con frecuencias conocidas. Si los datos cambian seguido, me quedaría con un AVL.

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Pasar de la tabla al árbol, usar la matriz R para construirlo de forma recursiva con nodos y apuntadores. Además, como se parece tanto a Godbole, me ha pasado confundir los dos en cuanto a qué se suma en cada uno.

</div>
