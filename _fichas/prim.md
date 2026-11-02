---
nombre: "Algoritmo de Prim"
orden: 5
nombre_corto: "Prim"
creador: "Robert C. Prim (antes Vojtěch Jarník, 1930; después Edsger Dijkstra, 1959)"
fecha: "1957"
escuela: "Algoritmos voraces"
tiempo: "O(n²) con matriz; O(m log n) con heap"
espacio: "O(n)"
---

## Para qué sirve

Encuentra el árbol de extensión mínima: el conjunto de conexiones que une todos los puntos de una red con el menor costo total y sin ciclos. Se usa para diseñar redes de fibra óptica, eléctricas, de agua o de carreteras, y como paso dentro de otros algoritmos, por ejemplo en la aproximación del problema del viajero o en agrupamiento de datos.

## Restricciones y limitaciones

- Solo funciona en grafos no dirigidos.
- Si el grafo no es conexo, solo cubre la componente donde empezó.
- No optimiza rutas entre dos puntos: el camino entre dos nodos dentro del árbol puede ser largo.
- En grafos con pocos arcos, Kruskal o Prim con heap son más rápidos que la versión con matriz.

## Cómo funciona

Empieza en cualquier nodo con Y = {v1}. En cada paso elige el arco más barato que une un nodo de Y con uno que todavía está fuera, agrega ese nodo a Y y el arco al árbol. Termina cuando Y contiene todos los nodos. Como siempre conecta un nodo nuevo, nunca forma ciclos.

La versión con matriz es every case O(n²), porque en cada paso revisa todos los nodos; con una cola de prioridad baja a O(m log n).

## Paradigma conveniente

Imperativo, con un arreglo de “costo para conectar” por nodo en grafos densos, o con una cola de prioridad (heap) en grafos dispersos.

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
S = ∅
Y = {v1}
mientras Y ≠ V
    elegir el arco (u, v) de menor peso con u en Y y v en V − Y
    Y = Y ∪ {v}
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

const int INF = 1000000000;

// W es la matriz de adyacencias de un grafo no dirigido (0 = no hay arco).
// Regresa el costo del árbol de extensión mínima; padre[v] es el nodo con el que se conecta v.
int prim(std::vector<std::vector<int>>& W, std::vector<int>& padre) {
    int n = W.size();
    std::vector<bool> enArbol(n, false);
    std::vector<int> costo(n, INF);
    padre.assign(n, -1);
    costo[0] = 0;
    int total = 0;

    for (int paso = 0; paso < n; paso++) {
        // Nodo fuera del árbol más barato de conectar
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!enArbol[v] && (u == -1 || costo[v] < costo[u])) {
                u = v;
            }
        }
        if (costo[u] == INF) {
            return -1; // grafo desconectado
        }
        enArbol[u] = true;
        total += costo[u];

        // Actualizar el costo de conectar a los vecinos de u
        for (int v = 0; v < n; v++) {
            if (!enArbol[v] && W[u][v] > 0 && W[u][v] < costo[v]) {
                costo[v] = W[u][v];
                padre[v] = u;
            }
        }
    }
    return total;
}

int main() {
    std::vector<std::vector<int>> W = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    std::vector<int> padre;
    int total = prim(W, padre);
    for (int v = 1; v < W.size(); v++) {
        std::cout << padre[v] << " - " << v << " : " << W[padre[v]][v] << std::endl;
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
INF = float("inf")


def prim(W):
    n = len(W)
    en_arbol = [False] * n
    costo = [INF] * n
    padre = [-1] * n
    costo[0] = 0
    total = 0
    for _ in range(n):
        u = min((v for v in range(n) if not en_arbol[v]), key=lambda v: costo[v])
        if costo[u] == INF:
            return None, padre  # grafo desconectado
        en_arbol[u] = True
        total += costo[u]
        for v in range(n):
            if not en_arbol[v] and 0 < W[u][v] < costo[v]:
                costo[v] = W[u][v]
                padre[v] = u
    return total, padre


W = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0],
]
total, padre = prim(W)
for v in range(1, len(W)):
    print(f"{padre[v]} - {v} : {W[padre[v]][v]}")
print("Costo total:", total)
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
0 - 1 : 2
1 - 2 : 3
0 - 3 : 6
1 - 4 : 5
Costo total: 16
```

## Ligas recomendadas

- [Prim’s Algorithm for Minimum Spanning Tree (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/prims-minimum-spanning-tree-mst-greedy-algo-5/): versión con matriz y con heap.
- [Prim's Algorithm in C++ (GeeksforGeeks)](https://www.geeksforgeeks.org/cpp/prims-algorithm-in-cpp/): implementación en C++.
- [Difference between Prim's and Kruskal's algorithm for MST (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/difference-between-prims-and-kruskals-algorithm-for-mst/): comparación directa entre los dos.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Lo entiendo bien, hace crecer una sola red desde un nodo eligiendo siempre el arco más barato hacia un nodo que todavía está fuera. 

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Sí, para diseñar redes que conecten todos los puntos con el menor costo, como fibra óptica entre sucursales. Sé que conviene más en grafos densos

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Elegir la estructura correcta con matriz es O(n²), pero en grafos con pocos arcos conviene usar un heap, y las colas de prioridad todavía no las domino.

</div>
