// Punto 4:

// Escriba una función (en C) que reciba un vector (de tamaño arbitrario) de strings y devuelva el primer
// string repetido del vector. La función debe poder funcionar en tiempo lineal respecto de la cantidad de
// strings. Explique la solución y justifique por qué es lineal.

#include <stdio.h>
#include "./../TDAs/hash_a.h"
#include "./../TDAs/abb.h"

char *primer_repetido(char **vector, size_t tamanio) {
    hash_t *hash = hash_crear(3);
    if (!hash)
        return NULL;
    
    for (size_t i = 0; i < tamanio; i++) {
        void *encontrado = NULL;

        if (!hash_insertar(hash, vector[i], (void *)1, &encontrado)) {
            hash_destruir(hash, NULL);
            return NULL;
        }

        if (encontrado) {
            hash_destruir(hash, NULL);
            return vector[i];
        }
    }

    hash_destruir(hash, NULL);
    return NULL;
}

int main() {
    char *vector[] = {"hola", "mundo", "pepe", "chau"};
    size_t tamanio = sizeof(vector) / sizeof(char *);

    char *repetido = primer_repetido(vector, tamanio);

    if (repetido)
        printf("El primer string repetido es: %s\n", repetido);
    else
        printf("No hay strings repetidos\n");

    return 0;
}

/**
 * La función primer_repetido recibe un vector de strings y su tamaño. Crea un hash con capacidad 3 y recorre el vector
 * insertando cada string en el hash. Si el string ya se encuentra en el hash, lo devuelve. Si no hay strings repetidos,
 * devuelve NULL. La función funciona en tiempo lineal respecto de la cantidad de strings porque la función hash_insertar
 * tiene una complejidad de O(1) en el caso promedio y la función hash_crear tiene una complejidad de O(1). Por lo tanto,
 * la función primer_repetido tiene una complejidad de O(n) en el caso promedio.
 */

// Punto 5:

// Explique qué es un diccionario y cuáles son sus principales características. Haga una comparativa entre
// diccionarios implementados con tablas de hash y con árboles autobalanceados. Escriba dos fragmentos
// de código (en C) donde se evidencie la conveniencia de una implementación por sobre la otra.

/**
 * Diccionario es un tipo de dato el cual almacena pares clave-valor. Las principales características de un diccionario son:
 * - Los costos de inserción, eliminación y búsqueda son O(1) en el caso promedio. En el peor caso, los costos son O(n).
 * - No permite claves repetidas. De haber una clave repetida, se reemplaza el valor asociado a la clave.
 * 
 * Comparativa entre diccionarios implementados con tablas de hash y con árboles autobalanceados:
 * - Tablas de hash:
 *  - Ventajas:
 *   - Costo de inserción, eliminación y búsqueda O(1) en el caso promedio.
 *  - Implementación más sencilla.
 * - Desventajas:
 *  - Costo de inserción, eliminación y búsqueda O(n) en el peor caso.
 * - No se pueden recorrer los elementos en orden.
 * 
 * - Árboles autobalanceados:
 * - Ventajas:
 * - Costo de inserción, eliminación y búsqueda O(log n).
 * - Se pueden recorrer los elementos en orden.
 * - Desventajas:
 * - Implementación más compleja.
 * - Costo de inserción, eliminación y búsqueda O(log n) en el caso promedio.
 */

// Implementación de un diccionario con tablas de hash:

typedef struct {
    char *tabla[100];
} hashcerrado;

unsigned int func_hash(char *clave) {
    unsigned int hash = 0;
    for (size_t i = 0; clave[i]; i++)
        hash = 31 * hash + clave[i];
    return hash % 100;
}

void insertar_hash(hashcerrado *hash, const char *clave) {
    unsigned int pos = func_hash(clave);

    // Búsqueda de posición libre con prueba lineal circular
    while (hash->tabla[pos] != NULL) {
        if (++pos == 100) pos = 0;  // Vuelve al inicio si se pasa
    }

    hash->tabla[pos] = calloc(strlen(clave) + 1, sizeof(char));
    if (!hash->tabla[pos]) return;
    strcpy(hash->tabla[pos], clave);

    return;
}

// Implementación de un diccionario con árboles autobalanceados:

typedef struct {
    char *clave;
    struct avl *izq, *der;
} avl;

avl *insertar_avl(avl *raiz, const char *clave) {
    if (raiz == NULL) {  // Caso base: crear nuevo nodo
        avl *nuevo = malloc(sizeof(avl));
        if (!nuevo) return NULL;
        nuevo->clave = strdup(clave);
        nuevo->izq = nuevo->der = NULL;
        return nuevo;
    }

    if (strcmp(clave, raiz->clave) < 0)
        raiz->izq = insertar_avl(raiz->izq, clave);
    else
        raiz->der = insertar_avl(raiz->der, clave);

    return raiz;
}