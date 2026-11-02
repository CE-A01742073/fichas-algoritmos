#include <iostream>
#include <vector>
#include <algorithm>

struct Arco {
    int u, v, peso;
};

bool menorPeso(const Arco& a, const Arco& b) {
    return a.peso < b.peso;
}

// Union-find: cada nodo apunta a su padre; la raíz representa al conjunto.
int buscar(std::vector<int>& padre, int x) {
    if (padre[x] != x) {
        padre[x] = buscar(padre, padre[x]); // compresión de caminos
    }
    return padre[x];
}

// Regresa el costo del árbol de extensión mínima y deja sus arcos en arbol.
int kruskal(int n, std::vector<Arco> arcos, std::vector<Arco>& arbol) {
    std::sort(arcos.begin(), arcos.end(), menorPeso);
    std::vector<int> padre(n);
    for (int i = 0; i < n; i++) {
        padre[i] = i;
    }
    arbol.clear();
    int total = 0;
    for (int i = 0; i < arcos.size() && arbol.size() < n - 1; i++) {
        int a = buscar(padre, arcos[i].u);
        int b = buscar(padre, arcos[i].v);
        if (a != b) { // están en conjuntos distintos: no forma ciclo
            padre[a] = b;
            arbol.push_back(arcos[i]);
            total += arcos[i].peso;
        }
    }
    if (arbol.size() < n - 1) {
        return -1; // grafo desconectado
    }
    return total;
}

int main() {
    int n = 5;
    std::vector<Arco> arcos = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8},
        {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
    };
    std::vector<Arco> arbol;
    int total = kruskal(n, arcos, arbol);
    for (int i = 0; i < arbol.size(); i++) {
        std::cout << arbol[i].u << " - " << arbol[i].v << " : " << arbol[i].peso << std::endl;
    }
    std::cout << "Costo total: " << total << std::endl;
    return 0;
}
