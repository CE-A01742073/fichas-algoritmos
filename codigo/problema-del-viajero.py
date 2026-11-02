INF = float("inf")


def viajero(W):
    n = len(W)
    total = 1 << n
    D = [[INF] * total for _ in range(n)]
    siguiente = [[-1] * total for _ in range(n)]

    for i in range(1, n):
        D[i][0] = W[i][0]
    for A in range(1, total):
        if A & 1:
            continue
        for i in range(1, n):
            if A & (1 << i):
                continue
            for j in range(1, n):
                if A & (1 << j):
                    costo = W[i][j] + D[j][A ^ (1 << j)]
                    if costo < D[i][A]:
                        D[i][A] = costo
                        siguiente[i][A] = j

    todos = (total - 1) ^ 1
    mejor, primero = INF, -1
    for j in range(1, n):
        costo = W[0][j] + D[j][todos ^ (1 << j)]
        if costo < mejor:
            mejor, primero = costo, j
    if primero == -1:
        return INF, []

    ruta = [0]
    actual, A = primero, todos ^ (1 << primero)
    while actual != -1:
        ruta.append(actual)
        sig = siguiente[actual][A]
        if sig != -1:
            A ^= 1 << sig
        actual = sig
    ruta.append(0)
    return mejor, ruta


# Ejemplo de clase (v1..v4 se numeran 0..3)
W = [
    [0, 2, 9, INF],
    [1, 0, 6, 4],
    [INF, 7, 0, 8],
    [6, 3, INF, 0],
]
costo, ruta = viajero(W)
print("Costo minimo:", costo)
print("Ruta:", " ".join(f"v{v + 1}" for v in ruta))
