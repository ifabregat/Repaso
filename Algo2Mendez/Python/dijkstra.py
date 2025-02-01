#!/vin/user/venv python3

import heapq

grafo = {
    "A": { "C": 4, "D": 3 },
    "B": { "D": 5, "E": 7, "H": 2 },
    "C": { "A": 4, "E": 1, "F": 2 },
    "D": { "H": 4, "G": 5 },
    "E": { "H": 1, "B": 7 },
    "F": { "C": 2, "G": 8, "I": 5 },
    "G": { "I": 2, "D": 5, "F": 8 },
    "H": { "B": 2, "E": 1, "D": 4 },
    "I": { "F": 5, "G": 2 },
}

def dijkstra(grafo, vertice):
    # Inicializamos las distancias a infinito para todos los nodos
    distancias = {vertice: float('infinity') for vertice in grafo}
    distancias[vertice] = 0  # La distancia al nodo de inicio es 0

    # Cola de prioridad con tupla (distancia, nodo)
    queue = [(0, vertice)]

    # Lista de nodos visitados
    visitados = []

    # Diccionario de predecesores para cada nodo
    predecesores = {vertice: None for vertice in grafo}

    while queue:
        distancia_visitado, vertice_visitado = heapq.heappop(queue)

        # Si la distancia actual es mayor que la guardada, la ignoramos
        if distancia_visitado > distancias[vertice_visitado]:
            continue

        # Marcamos el nodo como visitado y lo agregamos a la lista
        visitados.append(vertice_visitado)

        # Relajamos las aristas (actualizamos distancias a los vecinos)
        for neighbor, weight in grafo[vertice_visitado].items():
            distance = distancia_visitado + weight
            # Si encontramos una mejor distancia, la actualizamos
            if distance < distancias[neighbor]:
                distancias[neighbor] = distance
                predecesores[neighbor] = vertice_visitado  # Guardamos el nodo predecesor
                heapq.heappush(queue, (distance, neighbor))

    return distancias, predecesores, visitados

def obtener_camino(predecesores, inicio, fin):
    camino = []
    nodo_actual = fin

    while nodo_actual is not None:
        camino.append(nodo_actual)
        nodo_actual = predecesores[nodo_actual]

    return camino[::-1]  # Invertimos el camino para que vaya desde el inicio hasta el fin

# Ejecutar el algoritmo Dijkstra desde el vértice 'C'
distancias, predecesores, visitados = dijkstra(grafo, "C")

# Mostrar las distancias desde 'C'
print(f"Distancias desde 'C': {distancias}")

# Mostrar el último nodo visitado para cada nodo
print("\nÚltimo nodo visitado para cada nodo:")
for nodo in grafo:
    print(f"{nodo}: {predecesores[nodo]}")

# Mostrar los nodos visitados en orden
print(f"\nNodos visitados en orden: {visitados}")