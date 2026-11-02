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
