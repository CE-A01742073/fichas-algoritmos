---
nombre: "Algoritmo de Floyd"
orden: 1
nombre_corto: "Floyd"
creador: "Robert W. Floyd (con antecedentes de Bernard Roy y Stephen Warshall)"
fecha: "1962"
escuela: "Programación dinámica"
tiempo: "O(n³)"
espacio: "O(n²)"
---

## Para qué sirve

Calcula el camino más corto entre todos los pares de nodos de un grafo ponderado de una sola vez. Conviene cuando hay muchas consultas sobre el mismo grafo: rutas y tarifas entre ciudades, tablas de distancias entre sucursales, latencias entre los nodos de una red o el cierre transitivo de una relación (versión de Warshall, para saber quién alcanza a quién).

## Restricciones y limitaciones

- O(n³) lo vuelve impráctico con miles de nodos.
- Usa una matriz de n × n aunque el grafo tenga pocos arcos.
- Acepta pesos negativos, pero no ciclos negativos; si al final algún D[i,i] < 0, hay uno.
- Si solo necesitas rutas desde un origen, Dijkstra es más barato.

## Cómo funciona

Parte de la matriz de adyacencias, con 0 en la diagonal e ∞ donde no hay arco. En la iteración k permite pasar por el nodo k como escala y, para cada par (i, j), se queda con el menor entre el camino que ya tenía y el que pasa por k:

Dk[i,j] = mín(Dk-1[i,j], Dk-1[i,k] + Dk-1[k,j])
{: .formula}

El renglón y la columna k no cambian en la iteración k, por eso basta una sola matriz. Para recuperar la ruta se guarda en una matriz P el nodo intermedio y se reconstruye de forma recursiva.

## Paradigma conveniente

Imperativo con matrices: tres ciclos anidados sobre un arreglo bidimensional, sin recursión. Solo la reconstrucción del camino es más natural en forma recursiva.

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
D = matriz de adyacencias
P = matriz de ceros
for k = 1 to n
    for i = 1 to n
        for j = 1 to n
            if D[i,k] + D[k,j] < D[i,j]
                D[i,j] = D[i,k] + D[k,j]
                P[i,j] = k

camino(i, j)
    if P[i,j] != 0
        camino(i, P[i,j])
        escribir(P[i,j])
        camino(P[i,j], j)
```
{% endraw %}

</div>
<div class="pestana" data-nombre="C++" markdown="1">

{% raw %}
```cpp
#include <iostream>
#include <vector>

const int INF = 1000000000;

// D empieza como la matriz de adyacencias (0 en la diagonal, INF sin arco).
// Al terminar, D[i][j] es el costo mínimo de i a j y P[i][j] el nodo intermedio (-1 = arco directo).
void floyd(std::vector<std::vector<int>>& D, std::vector<std::vector<int>>& P) {
    int n = D.size();
    P.assign(n, std::vector<int>(n, -1));
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (D[i][k] < INF && D[k][j] < INF && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }
}

void camino(std::vector<std::vector<int>>& P, int i, int j) {
    int k = P[i][j];
    if (k != -1) {
        camino(P, i, k);
        std::cout << k << " ";
        camino(P, k, j);
    }
}

int main() {
    std::vector<std::vector<int>> D = {
        {0,   3,   INF, 7},
        {8,   0,   2,   INF},
        {5,   INF, 0,   1},
        {2,   INF, INF, 0}
    };
    std::vector<std::vector<int>> P;
    floyd(D, P);

    for (int i = 0; i < D.size(); i++) {
        for (int j = 0; j < D.size(); j++) {
            std::cout << D[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "Camino de 1 a 0: 1 ";
    camino(P, 1, 0);
    std::cout << "0" << std::endl;
    return 0;
}
```
{% endraw %}

</div>
<div class="pestana" data-nombre="Python" markdown="1">

{% raw %}
```python
INF = float("inf")


def floyd(D):
    n = len(D)
    D = [fila[:] for fila in D]
    P = [[-1] * n for _ in range(n)]
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if D[i][k] + D[k][j] < D[i][j]:
                    D[i][j] = D[i][k] + D[k][j]
                    P[i][j] = k
    return D, P


def camino(P, i, j):
    k = P[i][j]
    if k == -1:
        return []
    return camino(P, i, k) + [k] + camino(P, k, j)


D = [
    [0, 3, INF, 7],
    [8, 0, 2, INF],
    [5, INF, 0, 1],
    [2, INF, INF, 0],
]
D, P = floyd(D)
for fila in D:
    print(fila)
print("Camino de 1 a 0:", [1] + camino(P, 1, 0) + [0])
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
0   3   5   6   
5   0   2   3   
3   6   0   1   
2   5   7   0   
Camino de 1 a 0: 1 2 3 0
```

## Ligas recomendadas

- [Floyd Warshall Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/floyd-warshall-algorithm-dp-16/): explicación, ejemplo paso a paso e implementación.
- [Detecting negative cycle using Floyd Warshall (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/detecting-negative-cycle-using-floyd-warshall/): cómo detectar ciclos negativos con la diagonal.
- [Comparison of Dijkstra’s and Floyd–Warshall algorithms (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/comparison-dijkstras-floyd-warshall-algorithms/): cuándo usar cada uno.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Lo entiendo conceptualmente, pero no al 100. La recurrencia me hizo sentido cuando entendí que el tamaño del problema son los nodos que se permiten como escala, no los nodos del grafo. Lo que todavía me cuesta entender es por qué basta una sola matriz y la complejidad espacial es O(n²) y no O(n³)

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Sí. Lo apliqué en la Misión #6 para encontrar la ruta más barata entre las ciudades de una aerolínea, y ahí vi que conviene cuando hay muchas consultas sobre el mismo grafo, se calcula todo una vez al cargar el archivo y cada consulta se responde al instante. También lo veo útil en redes de computadoras, para saber qué nodos quedan incomunicados si uno falla.

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Los tres ciclos son sencillos pero se me dificulta reconstruir la ruta con la matriz P de forma recursiva y no solo dar el costo. En la Misión #6 también me costó más la documentación que el algoritmo, y por eso perdí adalgos.

</div>
