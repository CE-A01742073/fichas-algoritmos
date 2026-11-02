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
