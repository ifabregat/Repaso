class Nodo:
    def __init__(nodo, elemento): # Inicializar NODO
        nodo.elemento = elemento
        nodo.siguiente = None

class Lista:
    def __init__(self): # Inicializar LISTA
        self.primero = None
        self.cantidad = 0

    def insertar(self, elemento): # Insertar elemento en la LISTA
        self.cantidad = self.cantidad + 1
        if self.primero is None:
            self.primero = Nodo(elemento)
        else:
            actual = self.primero
            while actual.siguiente:
                actual = actual.siguiente
            actual.siguiente = Nodo(elemento)

    def obtener_nodo(self, posicion): # Obtener nodo en la posicion de la LISTA
        if self.primero is None:
            return
        actual = self.primero
        while actual and posicion > 0:
            actual = actual.siguiente
            posicion = posicion - 1
        if posicion == 0 and actual:
            return actual
        else:
            print("Posición no encontrada")
            return None

    def __getitem__(self, posicion): # Obtener elemento en la posicion
        nodo = self.obtener_nodo(posicion)
        if nodo:
            return nodo.elemento
        else:
            return None

    def __setitem__(self, posicion, elemento): # Cambiar elemento en la posicion
        nodo = self.obtener_nodo(posicion)
        if nodo:
            nodo.elemento = elemento
        else:
            print("Posición no encontrada")            

    def __str__(self): # Pasar LISTA a string
        string = "[ "
        actual = 0
        while actual < self.cantidad:
            string += str(self[actual]) + " "
            actual +=1
        string += "]"
        return string
    
    def __repr__(self): # Representacion de LISTA
        return str(self)

    def __iter__(self): # Iterador
        return next(self)

    def __next__(self): # Siguiente elemento
        actual = 0
        while actual < self.cantidad:
            yield self[actual]
            actual += 1

def generar_generador(n):
    actual = 0

    def g():
        nonlocal n
        nonlocal actual
        if actual<n:
            actual += 1
            return actual
        return None

    return g
