from collections import deque


def pivote(vector, inicio, fin):
    pivote = vector[fin - 1]
    i = inicio
    for j in range(inicio, fin):
        if vector[j] < pivote:
            vector[i], vector[j] = vector[j], vector[i]
            i += 1

    vector[i], vector[fin - 1] = vector[fin - 1], vector[i]
    return i

def quicksort(vector, inicio, fin):
    if inicio < fin:
        piv = pivote(vector, inicio, fin)
        quicksort(vector, inicio, piv)
        quicksort(vector, piv + 1, fin)

def merge(vector, inicio, mitad, fin):
    izq = deque(vector[inicio:mitad + 1])
    der = deque(vector[mitad + 1:fin + 1])
    i = inicio
    while izq and der:
        if izq[0] < der[0]:
            vector[i] = izq.popleft()
        else:
            vector[i] = der.popleft()
        i += 1
    while izq:
        vector[i] = izq.popleft()
        i += 1
    while der:
        vector[i] = der.popleft()
        i += 1

def mergesort(vector, inicio, fin):
    if inicio < fin:
        mitad = (inicio + fin) // 2
        mergesort(vector, inicio, mitad)
        mergesort(vector, mitad + 1, fin)
        merge(vector, inicio, mitad, fin)

vector = [3, 6, 8, 10, 1, 2, 1, 4, 5, 7, 9]
quicksort(vector, 0, len(vector))
print(f'{vector}\n')
vector = [3, 6, 8, 10, 1, 2, 1, 4, 5, 7, 9]
mergesort(vector, 0, len(vector) - 1)
print(vector)

grafo = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

def dfs(grafo, vertice, visitados):
    visitados.append(vertice)
    for vecino in grafo[vertice]:
        if vecino not in visitados:
            dfs(grafo, vecino, visitados)
    
def bfs(grafo, vertice, visitados):
    cola = deque([vertice])

    while len(cola) > 0:
        vertice = cola.popleft()
        visitados.append(vertice)
        for vecino in grafo[vertice]:
            if vecino not in visitados and vecino not in cola:
                cola.append(vecino)

    

visitados = []
dfs(grafo, 'A', visitados)
print(visitados)
visitados = []
bfs(grafo, 'A', visitados)
print(visitados)

def dfs(grafo, vertice, visitados, recorrido):
    visitados.add(vertice)
    for vecino in grafo[vertice]:
        if vecino not in visitados:
            dfs(grafo, vecino, visitados, recorrido)
    recorrido.appendleft(vertice)

def topologico(grafo):
    visitados = set()
    recorrido = deque()
    for vertice in grafo:
        dfs(grafo, vertice, visitados, recorrido)

    return list(recorrido)

print(topologico(grafo))

def dfs(grafo, vertice, visitados=None, padre=None):
    visitados.add(vertice)
    for vecino in grafo[vertice]:
        if vecino not in visitados:
            if dfs(grafo, vecino, visitados, vertice):
                return True
        elif vecino != padre:
            return True
    return False

def es_arbol(grafo):
    visitados = set()

    if dfs(grafo, "A", visitados, None):
        return False
    
    if len(visitados) != len(grafo):
        return False
    
    return True

if es_arbol(grafo):
    print("Es un árbol")
else:
    print("No es un árbol")