#include "heap.h"

heap_t *heap_crear()
{
	heap_t *heap = calloc(1, sizeof(heap_t));
	if (!heap)
		return NULL;

	heap->datos = calloc(1, 10 * sizeof(int));
	if (!heap->datos) {
		free(heap);
		return NULL;
	}

	heap->capacidad = 10;

	return heap;
}

void heap_destruir(heap_t *heap)
{
	free(heap->datos);
	free(heap);
}

void swap(int *vector, int a, int b)
{
	int temp = vector[a];
	vector[a] = vector[b];
	vector[b] = temp;
}

void sift_up(heap_t *heap, int pos_actual)
{
	if (pos_actual == 0)
		return;

	int pos_padre = (pos_actual - 1) / 2;
	int padre = heap->datos[pos_padre];
	int hijo = heap->datos[pos_actual];

	if (hijo > padre) {
		swap(heap->datos, pos_actual, pos_padre);
		sift_up(heap, pos_padre);
	}
}

bool heap_insertar(heap_t *heap, int elemento)
{
	if (heap->cantidad == heap->capacidad)
		return false;

	heap->datos[heap->cantidad] = elemento;
	sift_up(heap, heap->cantidad);
	heap->cantidad++;

	return true;
}

void sift_down(heap_t *heap, int pos_actual) {
    int pos_izq = (pos_actual * 2) + 1;
    int pos_der = (pos_actual * 2) + 2;

    if (pos_actual >= heap->cantidad)
        return;

    int pos_mayor = pos_actual;

    if (pos_izq < heap->cantidad && heap->datos[pos_izq] > heap->datos[pos_mayor])
        pos_mayor = pos_izq;

    if (pos_der < heap->cantidad && heap->datos[pos_der] > heap->datos[pos_mayor])
        pos_mayor = pos_der;

    if (pos_mayor != pos_actual) {
        swap(heap->datos, pos_actual, pos_mayor);
        sift_down(heap, pos_mayor);
    }
}

int heap_eliminar(heap_t *heap)
{
    if (heap->cantidad == 0)
        return -1;

    int eliminado = heap->datos[0];
    heap->cantidad--;
    heap->datos[0] = heap->datos[heap->cantidad];
    sift_down(heap, 0);

    return eliminado;
}

void heapify(heap_t *heap) {
/**
 * for (int i = 0; i < heap->cantidad; i++)
 *      sift_up(heap, i)
 */

    for (int i = (heap->cantidad -2) / 2; i > 0; i--)
        sift_down(heap, i);

    sift_down(heap, 0);
}

void heap_sort_r(heap_t *heap) {
    if (heap->cantidad == 1)
        return;

    swap(heap->datos, 0, heap->cantidad - 1);
    heap->cantidad--;
    sift_down(heap, 0);
    heap_sort_r(heap);
}

void heap_sort(heap_t *heap) {
    heapify(heap);

    heap_sort_r(heap);
}