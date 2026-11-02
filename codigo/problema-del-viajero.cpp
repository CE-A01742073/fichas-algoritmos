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
