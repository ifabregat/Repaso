#!/bin/usr/env python3

import heapq

grafo = {
    "A": {"B": 2, "C": 5, "D": 5},
    "B": {"A": 2 ,"C": 2, "D": 7,},
    "C": {"A": 5, "B": 2, "D": 4},
    "D": {"B": 7, "C": 4, "A": 5},
}

def prim(grafo, vertice):
    arbol = []
    visitados = set([vertice])
    min_heap = []

    for vecino, peso in grafo[vertice].items():
        heapq.heappush(min_heap, (peso, vertice, vecino))

    while min_heap:
        peso, origen, destino = heapq.heappop(min_heap)

        if destino not in visitados:
            visitados.add(destino)
            arbol.append((origen, destino, peso))

            for vecino, peso in grafo[destino].items():
                if vecino not in visitados:
                    heapq.heappush(min_heap, (peso, destino, vecino))

    return arbol

print(prim(grafo, "A"))