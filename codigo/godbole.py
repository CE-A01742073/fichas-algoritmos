def godbole(d):
    n = len(d) - 1
    D = [[0] * (n + 1) for _ in range(n + 1)]
    K = [[0] * (n + 1) for _ in range(n + 1)]
    for diag in range(1, n):
        for i in range(1, n - diag + 1):
            j = i + diag
            D[i][j] = None
            for k in range(i, j):
                costo = D[i][k] + D[k + 1][j] + d[i - 1] * d[k] * d[j]
                if D[i][j] is None or costo < D[i][j]:
                    D[i][j] = costo
                    K[i][j] = k
    return D[1][n], K


def parentesis(K, i, j):
    if i == j:
        return f"M{i}"
    k = K[i][j]
    return f"({parentesis(K, i, k)} x {parentesis(K, k + 1, j)})"


# Ejercicio de clase: 8x5, 5x9, 9x3, 3x15, 15x4
d = [8, 5, 9, 3, 15, 4]
minimo, K = godbole(d)
print("Multiplicaciones minimas:", minimo)
print("Orden:", parentesis(K, 1, len(d) - 1))
