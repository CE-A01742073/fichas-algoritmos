---
nombre: "Problema del viajero con programación dinámica"
orden: 4
nombre_corto: "Problema del viajero"
creador: "Michael Held y Richard Karp (y, por separado, Richard Bellman)"
fecha: "1962"
escuela: "Programación dinámica"
tiempo: "O(n² · 2ⁿ)"
espacio: "O(n · 2ⁿ)"
---

## Para qué sirve

Encuentra la ruta más barata que pasa una sola vez por cada punto y regresa al origen (el ciclo hamiltoniano óptimo). Aparece en logística y rutas de reparto, en el orden de perforación de circuitos impresos, en la secuenciación de genomas y en la planeación de observaciones de telescopios. Con programación dinámica da la respuesta exacta para casos de hasta unas 20 a 25 ciudades.

## Restricciones y limitaciones

- Es NP-Hard: no se conoce solución en tiempo polinomial, y esta sigue siendo exponencial.
- La memoria O(n · 2ⁿ) se agota antes que el tiempo; con 30 ciudades ya son miles de millones de casillas.
- Para casos grandes se usan heurísticas o aproximaciones (vecino más cercano, 2-opt, Christofides) que no garantizan el óptimo.

## Cómo funciona

D[vi, A] es el costo mínimo de ir de vi a v1 pasando una vez por todos los vértices del conjunto A. Con el conjunto vacío solo queda el arco directo: D[vi, ∅] = W[i,1]. Para los demás se prueba cada vértice vj de A como siguiente paso:

D[vi, A] = mín vj∈A (W[i,j] + D[vj, A − {vj}])
{: .formula}

Se resuelven primero los conjuntos de 1 vértice, luego los de 2, y así hasta n − 2. La respuesta es D[v1, V − {v1}]. Comparado con la fuerza bruta en O(n!), para 20 ciudades baja de unos 3,857 años a unos 45 segundos.

## Paradigma conveniente

Imperativo con máscaras de bits: cada subconjunto se guarda como un entero cuyos bits marcan qué vértices contiene, y la tabla es una matriz de n × 2ⁿ.

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
for i = 2 to n
    D[vi, ∅] = W[i,1]
for k = 1 to n-2
    for cada subconjunto A de {v2, ..., vn} con k vértices
        for cada i ≠ 1 con vi fuera de A
            D[vi, A] = mínimo de vj en A ( W[i,j] + D[vj, A − {vj}] )
D[v1, V − {v1}] = mínimo de j = 2..n ( W[1,j] + D[vj, V − {v1, vj}] )
return D[v1, V − {v1}]
```
{% endraw %}

</div>
<div class="pestana" data-nombre="C++" markdown="1">

{% raw %}
```cpp
#include <iostream>
#include <vector>

const int INF = 1000000000;

// W es la matriz de adyacencias (INF sin arco). El recorrido empieza y termina en el vértice 0.
// D[i][A] = costo mínimo de ir de i a 0 pasando una vez por los vértices del conjunto A.
// Cada conjunto A es un número: el bit j encendido significa que el vértice j está en A.
int viajero(std::vector<std::vector<int>>& W, std::vector<int>& ruta) {
    int n = W.size();
    int total = 1 << n;
    std::vector<std::vector<int>> D(n, std::vector<int>(total, INF));
    std::vector<std::vector<int>> siguiente(n, std::vector<int>(total, -1));

    for (int i = 1; i < n; i++) {
        D[i][0] = W[i][0];
    }
    // Los conjuntos se recorren de menor a mayor; un subconjunto siempre es un número menor.
    for (int A = 1; A < total; A++) {
        if (A & 1) {
            continue; // el vértice 0 nunca está dentro de A
        }
        for (int i = 1; i < n; i++) {
            if (A & (1 << i)) {
                continue; // i no puede estar en su propio conjunto
            }
            for (int j = 1; j < n; j++) {
                if ((A & (1 << j)) && W[i][j] < INF && D[j][A ^ (1 << j)] < INF) {
                    int costo = W[i][j] + D[j][A ^ (1 << j)];
                    if (costo < D[i][A]) {
                        D[i][A] = costo;
                        siguiente[i][A] = j;
                    }
                }
            }
        }
    }

    // Respuesta: salir de 0 hacia algún j y regresar pasando por todos los demás.
    int todos = (total - 1) ^ 1;
    int mejor = INF;
    int primero = -1;
    for (int j = 1; j < n; j++) {
        int resto = todos ^ (1 << j);
        if (W[0][j] < INF && D[j][resto] < INF && W[0][j] + D[j][resto] < mejor) {
            mejor = W[0][j] + D[j][resto];
            primero = j;
        }
    }

    ruta.clear();
    if (primero == -1) {
        return INF;
    }
    ruta.push_back(0);
    int actual = primero;
    int A = todos ^ (1 << primero);
    while (actual != -1) {
        ruta.push_back(actual);
        int sig = siguiente[actual][A];
        if (sig != -1) {
            A = A ^ (1 << sig);
        }
        actual = sig;
    }
    ruta.push_back(0);
    return mejor;
}

int main() {
    // Ejemplo de clase (v1..v4 se numeran 0..3)
    std::vector<std::vector<int>> W = {
        {0,   2, 9,   INF},
        {1,   0, 6,   4},
        {INF, 7, 0,   8},
        {6,   3, INF, 0}
    };
    std::vector<int> ruta;
    int costo = viajero(W, ruta);
    std::cout << "Costo minimo: " << costo << std::endl;
    std::cout << "Ruta: ";
    for (int v : ruta) {
        std::cout << "v" << v + 1 << " ";
    }
    std::cout << std::endl;
    return 0;
}
```
{% endraw %}

</div>
<div class="pestana" data-nombre="Python" markdown="1">

{% raw %}
```python
INF = float("inf")


def viajero(W):
    n = len(W)
    total = 1 << n
    D = [[INF] * total for _ in range(n)]
    siguiente = [[-1] * total for _ in range(n)]

    for i in range(1, n):
        D[i][0] = W[i][0]
    for A in range(1, total):
        if A & 1:
            continue
        for i in range(1, n):
            if A & (1 << i):
                continue
            for j in range(1, n):
                if A & (1 << j):
                    costo = W[i][j] + D[j][A ^ (1 << j)]
                    if costo < D[i][A]:
                        D[i][A] = costo
                        siguiente[i][A] = j

    todos = (total - 1) ^ 1
    mejor, primero = INF, -1
    for j in range(1, n):
        costo = W[0][j] + D[j][todos ^ (1 << j)]
        if costo < mejor:
            mejor, primero = costo, j
    if primero == -1:
        return INF, []

    ruta = [0]
    actual, A = primero, todos ^ (1 << primero)
    while actual != -1:
        ruta.append(actual)
        sig = siguiente[actual][A]
        if sig != -1:
            A ^= 1 << sig
        actual = sig
    ruta.append(0)
    return mejor, ruta


# Ejemplo de clase (v1..v4 se numeran 0..3)
W = [
    [0, 2, 9, INF],
    [1, 0, 6, 4],
    [INF, 7, 0, 8],
    [6, 3, INF, 0],
]
costo, ruta = viajero(W)
print("Costo minimo:", costo)
print("Ruta:", " ".join(f"v{v + 1}" for v in ruta))
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
Costo minimo: 21
Ruta: v1 v3 v4 v2 v1 
```

## Ligas recomendadas

- [Travelling Salesman Problem using Dynamic Programming (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/travelling-salesman-problem-using-dynamic-programming/): la recurrencia sobre subconjuntos.
- [Bitmasking and Dynamic Programming: TSP (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/bitmasking-dynamic-programming-set-2-tsp/): cómo representar los subconjuntos con máscaras de bits.
- [Traveling Salesman Problem using Branch And Bound (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/traveling-salesman-problem-using-branch-and-bound-2/): otra técnica exacta para comparar.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Lo había escuchado muchas veces, pero nunca lo había visto resuelto con una metodología específica. Entiendo la idea general y ya sé qué significa NP-Hard. Lo que me cuesta es la notación D[vi, A], porque ahora el subproblema es un subconjunto y no un intervalo.

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Sí, para casos chicos donde se necesita la ruta exacta, para más, sigue siendo exponencial. 

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Representar los subconjuntos en código, que supongo se hace con máscaras de bits, algo que casi no he usado. También me di cuenta de que mi primera idea era resolverlo con un algoritmo greedy, y al investigar vi que no asegura el óptimo.

</div>
