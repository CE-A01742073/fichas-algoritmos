def buscar(padre, x):
    if padre[x] != x:
        padre[x] = buscar(padre, padre[x])  # compresión de caminos
    return padre[x]


def kruskal(n, arcos):
    padre = list(range(n))
    arbol = []
    total = 0
    for u, v, peso in sorted(arcos, key=lambda a: a[2]):
        a, b = buscar(padre, u), buscar(padre, v)
        if a != b:  # conjuntos distintos: no forma ciclo
            padre[a] = b
            arbol.append((u, v, peso))
            total += peso
            if len(arbol) == n - 1:
                break
    if len(arbol) < n - 1:
        return None, arbol  # grafo desconectado
    return total, arbol


arcos = [(0, 1, 2), (0, 3, 6), (1, 2, 3), (1, 3, 8), (1, 4, 5), (2, 4, 7), (3, 4, 9)]
total, arbol = kruskal(5, arcos)
for u, v, peso in arbol:
    print(f"{u} - {v} : {peso}")
print("Costo total:", total)
