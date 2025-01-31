#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct heap {
	int *datos;
	int cantidad;
	int capacidad;
} heap_t;

heap_t *heap_crear();
void heap_destruir(heap_t *heap);
bool heap_insertar(heap_t *heap, int elemento);
int heap_eliminar(heap_t *heap);
void heapify(heap_t *heap);
void heap_sort(heap_t *heap);

#endif /* HEAP_H */