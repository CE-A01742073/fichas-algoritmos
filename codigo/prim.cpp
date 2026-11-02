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
