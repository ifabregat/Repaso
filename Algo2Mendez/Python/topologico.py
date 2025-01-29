#!/bin/usr/env python3

from collections import deque

grafo = {
    "CBC": ["AM2", "FUN", "F1"],
    "AM2": ["AM3"],
    "FUN": ["ALGO2"],
    "F1": ["TDA"],
    "AM3": ["ALGO3"],
    "ALGO2": ["ALGO3", "TDA"],
    "ALGO3": ["M2"],
    "TDA": ["M2"],
    "M2": ["FIN"],
    "FIN": []
}

# Lucas Pandolfo - 2024

def proximo_topo(incidencias, visitados):
    proximo = None
    for incidencia, peso in incidencias.items():
        if peso == 0 and incidencia not in visitados:
            proximo = incidencia
            break
    return proximo

def topologico_pandolfo(grafo):
    incidencias = { k:0 for k,v in grafo.items() }
    recorrido = []
    visitados = set()

    for nodo, vecinos in grafo.items():
        for vecino in vecinos:
            incidencias[vecino] += 1

    proximo = proximo_topo(incidencias, visitados)

    while proximo is not None:
        recorrido.append(proximo)
        visitados.add(proximo)
        for vecino in grafo[proximo]:
            incidencias[vecino] -= 1
        proximo = proximo_topo(incidencias, visitados)

    return recorrido

# Martin Buchwald - 2020

def grados_entrada(grafo):
    incidencias = { k:0 for k,v in grafo.items() }
    for vertices, vecinos in grafo.items():
        for vecino in vecinos:
            incidencias[vecino] += 1
    return incidencias

def topologico_buchwald(grafo):
    incidencias = grados_entrada(grafo)
    cola = deque()

    for vertice in grafo:
        if incidencias[vertice] == 0:
            cola.append(vertice)
    
    recorrido = []
    while cola:
        vertice = cola.popleft()
        recorrido.append(vertice)
        for vecino in grafo[vertice]:
            incidencias[vecino] -= 1
            if incidencias[vecino] == 0:
                cola.append(vecino)

    return recorrido

def dfs_buchwald(grafo, vertice, visitados, recorrido):
    visitados.add(vertice)
    for vecino in grafo[vertice]:
        if vecino not in visitados:
            dfs_buchwald(grafo, vecino, visitados, recorrido)
    recorrido.appendleft(vertice)

def topologico_buchwald_r(grafo):
    visitados = set()
    recorrido = deque()

    for vertice in grafo:
        if vertice not in visitados:
            dfs_buchwald(grafo, vertice, visitados, recorrido)

    return list(recorrido)

print(topologico_pandolfo(grafo))
print(topologico_buchwald(grafo))
print(topologico_buchwald_r(grafo))