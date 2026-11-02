def abb_optimo(p):
    # p[1..n] son las probabilidades; p[0] no se usa
    n = len(p) - 1
    A = [[0.0] * (n + 1) for _ in range(n + 2)]
    R = [[0] * (n + 1) for _ in range(n + 2)]
    for i in range(1, n + 1):
        A[i][i] = p[i]
        R[i][i] = i
    for diag in range(1, n):
        for i in range(1, n - diag + 1):
            j = i + diag
            suma = sum(p[i:j + 1])
            A[i][j] = None
            for k in range(i, j + 1):
                costo = A[i][k - 1] + A[k + 1][j] + suma
                if A[i][j] is None or costo < A[i][j]:
                    A[i][j] = costo
                    R[i][j] = k
    return A[1][n], R


def mostrar(R, llaves, i, j, nivel=0):
    if i > j:
        return
    k = R[i][j]
    print("    " * nivel + llaves[k])
    mostrar(R, llaves, i, k - 1, nivel + 1)
    mostrar(R, llaves, k + 1, j, nivel + 1)


# Ejercicio de clase, con las llaves en orden alfabético
llaves = ["", "a", "con", "de", "el", "y"]
p = [0, 0.25, 0.17, 0.25, 0.20, 0.13]
promedio, R = abb_optimo(p)
print("Promedio de comparaciones:", round(promedio, 2))
mostrar(R, llaves, 1, len(p) - 1)
