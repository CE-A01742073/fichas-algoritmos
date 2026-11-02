---
nombre: "Código de Huffman"
orden: 8
nombre_corto: "Huffman"
creador: "David A. Huffman"
fecha: "1952"
escuela: "Algoritmos voraces"
tiempo: "O(n log n), con n = número de símbolos distintos"
espacio: "O(n)"
---

## Para qué sirve

Comprime información sin perder datos, dando códigos binarios más cortos a los símbolos más frecuentes. Está dentro de formatos que se usan todos los días: DEFLATE (ZIP, gzip y PNG), JPEG y MP3 lo usan como último paso de compresión. En el ejemplo de clase, 10,000 caracteres pasan de 8,000 bits a 3,130, una compresión de 60.9%.

## Restricciones y limitaciones

- Necesita conocer las frecuencias: o se lee el archivo dos veces o se usa una tabla fija.
- El árbol o la tabla de códigos tiene que viajar con los datos para poder descomprimir.
- Cada símbolo ocupa un número entero de bits; la codificación aritmética comprime más cuando un símbolo domina.
- Si todos los símbolos tienen frecuencias parecidas, casi no comprime.

## Cómo funciona

Cada símbolo empieza como una hoja con su frecuencia. En cada paso toma los dos nodos de menor frecuencia y los une en un nodo padre cuya frecuencia es la suma de ambos. Repite hasta que queda un solo nodo, la raíz. Después asigna 0 a cada rama izquierda y 1 a cada derecha; el camino de la raíz a cada hoja es el código del símbolo.

El resultado es un código de prefijo: ningún código es el inicio de otro, así que se decodifica sin separadores.

## Paradigma conveniente

Imperativo con una cola de prioridad (heap) de nodos para construir el árbol, y recursivo para recorrerlo y asignar los códigos.

## Implementación

<div class="codigo" markdown="1">
<div class="pestana" data-nombre="Pseudocódigo" markdown="1">

{% raw %}
```text
cola = cola de prioridad con una hoja por símbolo
mientras la cola tenga más de un nodo
    a = sacar el nodo de menor frecuencia
    b = sacar el nodo de menor frecuencia
    padre = nuevo nodo con frecuencia a + b
    padre.izq = a
    padre.der = b
    meter padre en la cola
raiz = el nodo que queda

asignar(nodo, codigo)
    if nodo es hoja
        codigo[nodo] = codigo
    else
        asignar(nodo.izq, codigo + "0")
        asignar(nodo.der, codigo + "1")
```
{% endraw %}

</div>
<div class="pestana" data-nombre="C++" markdown="1">

{% raw %}
```cpp
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
```
{% endraw %}

</div>
<div class="pestana" data-nombre="Python" markdown="1">

{% raw %}
```python
import heapq


def huffman(frecuencias):
    # Cada elemento del heap: (frecuencia, desempate, nodo)
    # Una hoja es un símbolo; un nodo interno es una pareja (izquierdo, derecho).
    heap = [(f, i, s) for i, (s, f) in enumerate(frecuencias.items())]
    heapq.heapify(heap)
    contador = len(heap)
    while len(heap) > 1:
        fa, _, a = heapq.heappop(heap)
        fb, _, b = heapq.heappop(heap)
        heapq.heappush(heap, (fa + fb, contador, (a, b)))
        contador += 1
    raiz = heap[0][2]

    codigos = {}

    def asignar(nodo, codigo):
        if isinstance(nodo, tuple):
            asignar(nodo[0], codigo + "0")
            asignar(nodo[1], codigo + "1")
        else:
            codigos[nodo] = codigo or "0"

    asignar(raiz, "")
    return codigos


frecuencias = {"A": 45, "B": 13, "C": 12, "D": 16, "E": 9, "F": 5}
for simbolo, codigo in sorted(huffman(frecuencias).items()):
    print(f"{simbolo}: {codigo}")
```
{% endraw %}

</div>
</div>

<p class="salida-titulo">Salida del ejemplo en C++</p>

```text
A: 0
C: 100
B: 101
F: 1100
E: 1101
D: 111
```

## Ligas recomendadas

- [Huffman Coding Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/huffman-coding-greedy-algo-3/): construcción del árbol paso a paso.
- [Text File Compression And Decompression Using Huffman Coding (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/text-file-compression-and-decompression-using-huffman-coding/): comprimir y descomprimir un archivo real.
- [Practice Questions on Huffman Encoding (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/practice-questions-on-huffman-encoding/): ejercicios para practicar el árbol a mano.

## Reflexiones personales

<div class="reflexiones" markdown="1">

### ¿Qué tan fácil o difícil fue entender este algoritmo? ¿Ya lo comprendes por completo?

Es el que menos entendí en clase, entiendo que los símbolos más frecuentes llevan códigos más cortos, pero se me dificulta armar el árbol

### ¿Tienes claridad de cuándo convendría usarlo al construir una aplicación de software?

Más o menos. Sé que está dentro de formatos como ZIP, PNG o JPEG, pero lo veo más como algo que ya viene en librerías que como algo que yo programaría desde cero

### ¿Qué es lo más retador para implementarlo con tus habilidades de programación?

Construir el árbol con una cola de prioridad y recorrerlo de forma recursiva para asignar los códigos. Además, para descomprimir hay que guardar el árbol junto con los datos.

</div>
