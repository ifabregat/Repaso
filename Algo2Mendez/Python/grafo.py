#!/bin/usr/env python3

from collections import deque

grafo = {
    "A": ["B", "C"],
    "B": ["A", "D", "E"],
    "C": ["A", "F"],
    "D": ["B"],
    "E": ["B"],
    "F": []
}

def dfs(grafo, nodo, visitados):
    visitados.append(nodo)

    for vertice in grafo[nodo]:
        if vertice not in visitados:
            dfs(grafo, vertice, visitados)

    return visitados 

def bfs(grafo, vertice):
    visitados = []
    cola = deque([vertice])

    while len(cola) > 0:
        vertice = cola.popleft()
        visitados.append(vertice)

        for vecino in grafo[vertice]:
            if vecino not in visitados:
                cola.append(vecino)

    return visitados

def es_conexo(grafo):
    return len(dfs(grafo, "A", [])) == len(grafo)

visitados = []

print("DFS desde A: ", dfs(grafo, "B", visitados))
print("BFS desde A: ", bfs(grafo, "B"))
print("El grafo es conexo: ", es_conexo(grafo))