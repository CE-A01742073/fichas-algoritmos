---
nombre: "Algoritmo de Dijkstra"
orden: 7
nombre_corto: "Dijkstra"
creador: "Edsger W. Dijkstra"
fecha: "1959"
escuela: "Algoritmos voraces"
tiempo: "O(n²) con arreglos; O((n + m) log n) con heap"
espacio: "O(n)"
---

## Para qué sirve

Calcula el camino más corto desde un nodo origen hacia todos los demás y entrega el árbol del camino más corto. Es la base de la navegación GPS, de protocolos de ruteo de redes como OSPF e IS-IS, de la búsqueda de rutas en videojuegos y de cualquier sistema que necesite rutas desde un punto fijo.

## Restricciones y limitaciones

- No funciona con pesos negativos; para eso existe Bellman-Ford.
- Resuelve un solo origen; para todos contra todos, Floyd es más simple.
- El árbol del camino más corto no es el árbol de extensión mínima: optimiza rutas desde el origen, no el costo total de conectar todo.
- En mapas muy grandes se combina con heurísticas (A*) para no explorar todo el grafo.

## Cómo funciona

Empieza con Y = {v1} y la distancia de cada nodo igual al arco directo desde v1. En cada paso elige el nodo fuera de Y con la menor distancia acumulada, lo agrega a Y y actualiza a sus vecinos si pasar por él les da un camino más corto. Termina cuando Y contiene todos los nodos.

Es la misma estrategia que Prim, pero en lugar del peso del arco compara el costo acumulado del camino. Guardar el padre de cada nodo permite reconstruir las rutas.

## Paradigma conveniente

Imperativo, con arreglos de distancia, padre y visitado en grafos densos, o con una cola de prioridad (heap) y lista de adyacencias en grafos dispersos.

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
dist[v] = ∞ para todo v
dist[origen] = 0
Y = ∅
mientras Y ≠ V
    u = vértice de V − Y con menor dist[u]
    Y = Y ∪ {u}
    for cada vecino v de u fuera de Y
        if dist[u] + W[u,v] < dist[v]
            dist[v] = dist[u] + W[u,v]
            padre[v] = u
return dist, padre
```
{% endraw %}

</div>
<div class="pestana" data-nombre="C++" markdown="1">

{% raw %}
```cpp
#include <iostream>
#include <vector>

const int INF = 1000000000;

// W es la matriz de adyacencias (0 = no hay arco). Calcula la distancia mínima
// desde origen a cada nodo; padre[v] es el nodo anterior a v en su camino.
void dijkstra(std::vector<std::vector<int>>& W, int origen, std::vector<int>& dist, std::vector<int>& padre) {
    int n = W.size();
    std::vector<bool> visitado(n, false);
    dist.assign(n, INF);
    padre.assign(n, -1);
    dist[origen] = 0;

    for (int paso = 0; paso < n; paso++) {
        // Nodo no visitado con el camino acumulado más corto
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        if (dist[u] == INF) {
            break; // los que faltan no se pueden alcanzar
        }
        visitado[u] = true;

        // ¿Pasar por u mejora el camino a sus vecinos?
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && W[u][v] > 0 && dist[u] + W[u][v] < dist[v]) {
                dist[v] = dist[u] + W[u][v];
                padre[v] = u;
            }
        }
    }
}

void mostrarCamino(std::vector<int>& padre, int v) {
    if (padre[v] != -1) {
        mostrarCamino(padre, padre[v]);
        std::cout << " -> ";
    }
    std::cout << v;
}

int main() {
    std::vector<std::vector<int>> W = {
        {0, 4, 1, 0, 0},
        {4, 0, 2, 5, 0},
        {1, 2, 0, 8, 10},
        {0, 5, 8, 0, 2},
        {0, 0, 10, 2, 0}
    };
    std::vector<int> dist, padre;
    dijkstra(W, 0, dist, padre);
    for (int v = 0; v < W.size(); v++) {
        std::cout << "Hasta " << v << " = " << dist[v] << "   ";
        mostrarCamino(padre, v);
        std::cout << std::endl;
    }
    return 0;
}
```
{% endraw %}

</div>
<div class="pestana" data-nombre="Python" markdown="1">

{% raw %}
```python
INF = float("inf")


def dijkstra(W, origen):
    n = len(W)
    visitado = [False] * n
    dist = [INF] * n
    padre = [-1] * n
    dist[origen] = 0
    for _ in range(n):
        u = min((v for v in range(n) if not visitado[v]), key=lambda v: dist[v])
        if dist[u] == INF:
            break  # los que faltan no se pueden alcanzar
        visitado[u] = True
        for v in range(n):
            if not visitado[v] and W[u][v] > 0 and dist[u] + W[u][v] < dist[v]:
                dist[v] = dist[u] + W[u][v]
                padre[v] = u
    return dist, padre


def camino(padre, v):
    ruta = []
    while v != -1:
        ruta.append(v)
        v = padre[v]
    return ruta[::-1]


W = [
    [0, 4, 1, 0, 0],
    [4, 0, 2, 5, 0],
    [1, 2, 0, 8, 10],
    [0, 5, 8, 0, 2],
    [0, 0, 10, 2, 0],
]
dist, padre = dijkstra(W, 0)
for v in range(len(W)):
    print(f"Hasta {v} = {dist[v]}  ", " -> ".join(map(str, camino(padre, v))))
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
Hasta 0 = 0   0
Hasta 1 = 3   0 -> 2 -> 1
Hasta 2 = 1   0 -> 2
Hasta 3 = 8   0 -> 2 -> 1 -> 3
Hasta 4 = 10   0 -> 2 -> 1 -> 3 -> 4
```

## Ligas recomendadas

- [Dijkstra’s Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/dijkstras-shortest-path-algorithm-greedy-algo-7/): explicación e implementación con heap.
- [Printing Paths in Dijkstra's Shortest Path Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/printing-paths-dijkstras-shortest-path-algorithm/): reconstruir rutas con el arreglo de padres.
- [Shortest Path Algorithm in Computer Network (GeeksforGeeks)](https://www.geeksforgeeks.org/computer-networks/shortest-path-algorithm-in-computer-network/): su uso en ruteo de redes.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Es el que mejor entiendo de esta parte, porque ya lo conocía de redes. Lo que más me ayudó fue verlo como Prim con memoria, es la misma estrategia, pero elige el camino acumulado más corto en lugar del arco más barato. 

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Sí. Me interesa en particular porque protocolos de ruteo como OSPF lo usan para conectar routers y switches. 

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Guardar el padre de cada nodo para reconstruir las rutas y, en grafos grandes, implementarlo con un heap.

</div>
