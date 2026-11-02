INF = float("inf")


def dijkstra(W, origen):
    n = len(W)
    visitado = [False] * n
    dist = [INF] * n
    padre = [-1] * n
    dist[origen] = 0
    for _ in range(n):
        u = min((v for v in range(n) if not visitado[v]), key=lambda v: dist[v])
        if dist[u] == INF:
            break  # los que faltan no se pueden alcanzar
        visitado[u] = True
        for v in range(n):
            if not visitado[v] and W[u][v] > 0 and dist[u] + W[u][v] < dist[v]:
                dist[v] = dist[u] + W[u][v]
                padre[v] = u
    return dist, padre


def camino(padre, v):
    ruta = []
    while v != -1:
        ruta.append(v)
        v = padre[v]
    return ruta[::-1]


W = [
    [0, 4, 1, 0, 0],
    [4, 0, 2, 5, 0],
    [1, 2, 0, 8, 10],
    [0, 5, 8, 0, 2],
    [0, 0, 10, 2, 0],
]
dist, padre = dijkstra(W, 0)
for v in range(len(W)):
    print(f"Hasta {v} = {dist[v]}  ", " -> ".join(map(str, camino(padre, v))))
