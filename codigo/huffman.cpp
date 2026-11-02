#include <iostream>
#include <vector>
#include <queue>
#include <string>

struct Nodo {
    char simbolo;
    int frecuencia;
    Nodo* izq;
    Nodo* der;
};

Nodo* nuevoNodo(char s, int f, Nodo* izq, Nodo* der) {
    Nodo* nodo = new Nodo;
    nodo->simbolo = s;
    nodo->frecuencia = f;
    nodo->izq = izq;
    nodo->der = der;
    return nodo;
}

// Para que la cola de prioridad saque primero la menor frecuencia
struct Comparar {
    bool operator()(Nodo* a, Nodo* b) {
        return a->frecuencia > b->frecuencia;
    }
};

Nodo* construirArbol(std::vector<char>& simbolos, std::vector<int>& frecuencias) {
    std::priority_queue<Nodo*, std::vector<Nodo*>, Comparar> cola;
    for (int i = 0; i < simbolos.size(); i++) {
        cola.push(nuevoNodo(simbolos[i], frecuencias[i], nullptr, nullptr));
    }
    // Decisión voraz: unir siempre los dos nodos de menor frecuencia
    while (cola.size() > 1) {
        Nodo* a = cola.top();
        cola.pop();
        Nodo* b = cola.top();
        cola.pop();
        cola.push(nuevoNodo('\0', a->frecuencia + b->frecuencia, a, b));
    }
    return cola.top();
}

// Izquierda = 0, derecha = 1. Guarda el código de cada hoja.
void asignarCodigos(Nodo* nodo, std::string codigo, std::vector<char>& simbolos, std::vector<std::string>& codigos) {
    if (nodo->izq == nullptr && nodo->der == nullptr) {
        if (codigo == "") {
            codigo = "0"; // caso de un solo símbolo
        }
        simbolos.push_back(nodo->simbolo);
        codigos.push_back(codigo);
        return;
    }
    asignarCodigos(nodo->izq, codigo + "0", simbolos, codigos);
    asignarCodigos(nodo->der, codigo + "1", simbolos, codigos);
}

int main() {
    std::vector<char> simbolos = {'A', 'B', 'C', 'D', 'E', 'F'};
    std::vector<int> frecuencias = {45, 13, 12, 16, 9, 5};
    Nodo* raiz = construirArbol(simbolos, frecuencias);

    std::vector<char> hojas;
    std::vector<std::string> codigos;
    asignarCodigos(raiz, "", hojas, codigos);
    for (int i = 0; i < hojas.size(); i++) {
        std::cout << hojas[i] << ": " << codigos[i] << std::endl;
    }
    return 0;
}
