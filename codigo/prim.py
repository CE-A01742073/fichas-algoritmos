INF = float("inf")


def prim(W):
    n = len(W)
    en_arbol = [False] * n
    costo = [INF] * n
    padre = [-1] * n
    costo[0] = 0
    total = 0
    for _ in range(n):
        u = min((v for v in range(n) if not en_arbol[v]), key=lambda v: costo[v])
        if costo[u] == INF:
            return None, padre  # grafo desconectado
        en_arbol[u] = True
        total += costo[u]
        for v in range(n):
            if not en_arbol[v] and 0 < W[u][v] < costo[v]:
                costo[v] = W[u][v]
                padre[v] = u
    return total, padre


W = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0],
]
total, padre = prim(W)
for v in range(1, len(W)):
    print(f"{padre[v]} - {v} : {W[padre[v]][v]}")
print("Costo total:", total)
