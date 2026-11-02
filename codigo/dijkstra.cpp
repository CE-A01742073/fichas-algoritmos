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
