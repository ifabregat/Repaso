#!/usr/bin/env python3

import heapq

grafo = {
    "A": {"B": 2, "C": 5, "D": 5},
    "B": {"A": 2 ,"C": 2, "D": 7,},
    "C": {"A": 5, "B": 2, "D": 4},
    "D": {"B": 7, "C": 4, "A": 5},
}

class UnionFind:
    """Estructura para manejar conjuntos disjuntos (Union-Find con compresión de camino)."""

    def __init__(self, nodos):
        self.padre = {nodo: nodo for nodo in nodos}
        self.rango = {nodo: 0 for nodo in nodos}

    def encontrar(self, nodo):
        """Encuentra la raíz del conjunto al que pertenece un nodo, con compresión de camino."""
        if self.padre[nodo] != nodo:
            self.padre[nodo] = self.encontrar(self.padre[nodo])
        return self.padre[nodo]

    def unir(self, nodo1, nodo2):
        """Une dos conjuntos por rango."""
        raiz1 = self.encontrar(nodo1)
        raiz2 = self.encontrar(nodo2)

        if raiz1 != raiz2:
            if self.rango[raiz1] > self.rango[raiz2]:
                self.padre[raiz2] = raiz1
            elif self.rango[raiz1] < self.rango[raiz2]:
                self.padre[raiz1] = raiz2
            else:
                self.padre[raiz2] = raiz1
                self.rango[raiz1] += 1  

def kruskal(grafo):
    """
    Implementa el algoritmo de Kruskal para encontrar el Árbol de Expansión Mínima (MST).
    
    :param grafo: Diccionario de adyacencia { nodo: { vecino: peso, ... } }
    :return: Lista de aristas del MST
    """
    arbol = []
    aristas = []
    
    # Construir la lista de aristas
    for origen in grafo:
        for destino, peso in grafo[origen].items():
            if (peso, destino, origen) not in aristas:  # Evitar duplicados
                aristas.append((peso, origen, destino))

    # Ordenar las aristas por peso
    heapq.heapify(aristas)  # Convertimos la lista en un heap para extraer mínimos fácilmente

    # Inicializar estructura Union-Find
    conjuntos = UnionFind(grafo.keys())

    while aristas:
        peso, origen, destino = heapq.heappop(aristas)

        if conjuntos.encontrar(origen) != conjuntos.encontrar(destino):  # Si no forma ciclo
            conjuntos.unir(origen, destino)
            arbol.append((origen, destino, peso))

    return arbol

print(kruskal(grafo))