---
nombre: "Algoritmo de Kruskal"
orden: 6
nombre_corto: "Kruskal"
creador: "Joseph Kruskal"
fecha: "1956"
escuela: "Algoritmos voraces"
tiempo: "O(m log m)"
espacio: "O(n + m)"
---

## Para qué sirve

También encuentra el árbol de extensión mínima, pero trabajando sobre los arcos en lugar de los nodos. Conviene en redes con pocas conexiones (carreteras, cableado, redes de sensores) y en agrupamiento de datos: si se detiene antes de unir todo, los subconjuntos que quedan son clusters. También se usa para segmentar imágenes y para generar laberintos.

## Restricciones y limitaciones

- Solo funciona en grafos no dirigidos.
- Necesita ordenar todos los arcos, y eso domina el costo.
- En grafos muy densos, con cerca de n(n−1)/2 arcos, Prim con matriz es mejor.
- Requiere una estructura de unión de conjuntos (union-find) para detectar ciclos rápido; sin ella se vuelve lento.
- Si el grafo no es conexo, entrega un bosque en lugar de un árbol.

## Cómo funciona

Empieza con cada nodo en su propio conjunto y ordena los arcos de menor a mayor peso. Recorre los arcos en ese orden: si un arco une dos nodos de conjuntos distintos, lo agrega al árbol y une los conjuntos; si ambos ya están en el mismo, lo descarta porque formaría un ciclo. Termina cuando queda un solo conjunto.

A diferencia de Prim, no es every case: puede terminar antes de revisar todos los arcos.

## Paradigma conveniente

Imperativo, con una lista de arcos ordenada y un arreglo de padres para union-find (con compresión de caminos y unión por rango).

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
S = ∅
crear un conjunto {v} por cada vértice v
ordenar los arcos de menor a mayor peso
mientras S tenga menos de n − 1 arcos
    (u, v) = siguiente arco más barato
    if buscar(u) ≠ buscar(v)
        unir(u, v)
        S = S ∪ {(u, v)}
return S
```
{% endraw %}

</div>
<div class="pestana" data-nombre="C++" markdown="1">

{% raw %}
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Arco {
    int u, v, peso;
};

bool menorPeso(const Arco& a, const Arco& b) {
    return a.peso < b.peso;
}

// Union-find: cada nodo apunta a su padre; la raíz representa al conjunto.
int buscar(std::vector<int>& padre, int x) {
    if (padre[x] != x) {
        padre[x] = buscar(padre, padre[x]); // compresión de caminos
    }
    return padre[x];
}

// Regresa el costo del árbol de extensión mínima y deja sus arcos en arbol.
int kruskal(int n, std::vector<Arco> arcos, std::vector<Arco>& arbol) {
    std::sort(arcos.begin(), arcos.end(), menorPeso);
    std::vector<int> padre(n);
    for (int i = 0; i < n; i++) {
        padre[i] = i;
    }
    arbol.clear();
    int total = 0;
    for (int i = 0; i < arcos.size() && arbol.size() < n - 1; i++) {
        int a = buscar(padre, arcos[i].u);
        int b = buscar(padre, arcos[i].v);
        if (a != b) { // están en conjuntos distintos: no forma ciclo
            padre[a] = b;
            arbol.push_back(arcos[i]);
            total += arcos[i].peso;
        }
    }
    if (arbol.size() < n - 1) {
        return -1; // grafo desconectado
    }
    return total;
}

int main() {
    int n = 5;
    std::vector<Arco> arcos = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8},
        {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
    };
    std::vector<Arco> arbol;
    int total = kruskal(n, arcos, arbol);
    for (int i = 0; i < arbol.size(); i++) {
        std::cout << arbol[i].u << " - " << arbol[i].v << " : " << arbol[i].peso << std::endl;
    }
    std::cout << "Costo total: " << total << std::endl;
    return 0;
}
```
{% endraw %}

</div>
<div class="pestana" data-nombre="Python" markdown="1">

{% raw %}
```python
def buscar(padre, x):
    if padre[x] != x:
        padre[x] = buscar(padre, padre[x])  # compresión de caminos
    return padre[x]


def kruskal(n, arcos):
    padre = list(range(n))
    arbol = []
    total = 0
    for u, v, peso in sorted(arcos, key=lambda a: a[2]):
        a, b = buscar(padre, u), buscar(padre, v)
        if a != b:  # conjuntos distintos: no forma ciclo
            padre[a] = b
            arbol.append((u, v, peso))
            total += peso
            if len(arbol) == n - 1:
                break
    if len(arbol) < n - 1:
        return None, arbol  # grafo desconectado
    return total, arbol


arcos = [(0, 1, 2), (0, 3, 6), (1, 2, 3), (1, 3, 8), (1, 4, 5), (2, 4, 7), (3, 4, 9)]
total, arbol = kruskal(5, arcos)
for u, v, peso in arbol:
    print(f"{u} - {v} : {peso}")
print("Costo total:", total)
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
0 - 1 : 2
1 - 2 : 3
1 - 4 : 5
0 - 3 : 6
Costo total: 16
```

## Ligas recomendadas

- [Kruskal’s Minimum Spanning Tree Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/): explicación con union-find.
- [Time and Space Complexity Analysis of Kruskal Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/time-and-space-complexity-analysis-of-kruskal-algorithm/): de dónde sale el O(m log m).
- [Which Minimum Spanning Tree Algorithm is better? (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/which-minimum-spanning-tree-algorithm-is-better/): cuándo conviene Kruskal y cuándo Prim.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Entiendo como funciona, ordenar los arcos y unir pedacitos sueltos sin formar ciclos. pero todavia lo tengo menos practicado que Prim

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Más o menos. Sé que conviene en grafos con pocos arcos y que, si los arcos ya vienen ordenados, casi siempre gana. Lo que no tenía claro era el corte exacto con Prim

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Implementar union-find para detectar ciclos rápido. Es una estructura que no he programado antes, se puede sin el union pero es mucho mas lento

</div>
