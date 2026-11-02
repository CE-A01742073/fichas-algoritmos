#include <iostream>
#include <vector>
#include <string>

// p[1..n] son las probabilidades de las llaves ordenadas (p[0] no se usa).
// Regresa el promedio mínimo de comparaciones; R[i][j] guarda la raíz del tramo i..j.
double abbOptimo(std::vector<double>& p, std::vector<std::vector<int>>& R) {
    int n = p.size() - 1;
    std::vector<std::vector<double>> A(n + 2, std::vector<double>(n + 1, 0));
    R.assign(n + 2, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        A[i][i] = p[i];
        R[i][i] = i;
    }
    for (int diag = 1; diag <= n - 1; diag++) {
        for (int i = 1; i <= n - diag; i++) {
            int j = i + diag;
            double suma = 0;
            for (int t = i; t <= j; t++) {
                suma += p[t];
            }
            A[i][j] = -1;
            for (int k = i; k <= j; k++) {
                double costo = A[i][k - 1] + A[k + 1][j] + suma;
                if (A[i][j] < 0 || costo < A[i][j]) {
                    A[i][j] = costo;
                    R[i][j] = k;
                }
            }
        }
    }
    return A[1][n];
}

// Muestra el árbol en preorden: raíz, subárbol izquierdo, subárbol derecho.
void mostrar(std::vector<std::vector<int>>& R, std::vector<std::string>& llaves, int i, int j, int nivel) {
    if (i > j) {
        return;
    }
    int k = R[i][j];
    std::cout << std::string(nivel * 4, ' ') << llaves[k] << std::endl;
    mostrar(R, llaves, i, k - 1, nivel + 1);
    mostrar(R, llaves, k + 1, j, nivel + 1);
}

int main() {
    // Ejercicio de clase, con las llaves en orden alfabético
    std::vector<std::string> llaves = {"", "a", "con", "de", "el", "y"};
    std::vector<double> p = {0, 0.25, 0.17, 0.25, 0.20, 0.13};
    std::vector<std::vector<int>> R;
    double promedio = abbOptimo(p, R);
    std::cout << "Promedio de comparaciones: " << promedio << std::endl;
    mostrar(R, llaves, 1, p.size() - 1, 0);
    return 0;
}
