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
