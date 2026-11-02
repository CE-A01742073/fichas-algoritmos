INF = float("inf")


def floyd(D):
    n = len(D)
    D = [fila[:] for fila in D]
    P = [[-1] * n for _ in range(n)]
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if D[i][k] + D[k][j] < D[i][j]:
                    D[i][j] = D[i][k] + D[k][j]
                    P[i][j] = k
    return D, P


def camino(P, i, j):
    k = P[i][j]
    if k == -1:
        return []
    return camino(P, i, k) + [k] + camino(P, k, j)


D = [
    [0, 3, INF, 7],
    [8, 0, 2, INF],
    [5, INF, 0, 1],
    [2, INF, INF, 0],
]
D, P = floyd(D)
for fila in D:
    print(fila)
print("Camino de 1 a 0:", [1] + camino(P, 1, 0) + [0])
