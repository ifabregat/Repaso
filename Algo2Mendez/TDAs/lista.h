#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct nodoL {
	void *dato;
	struct nodoL *siguiente;
} nodoL_t;

typedef struct lista {
	nodoL_t *primer;
	nodoL_t *ultimo;
	size_t cantidad;
} lista_t;

lista_t *lista_crear();
void lista_destruir(lista_t *lista);
void lista_destruir_todo(lista_t *lista, void (*destructor)(void *));
size_t lista_cantidad(lista_t *lista);
bool lista_agregar(lista_t *lista, size_t posicion, void *elemento);
bool lista_agregar_final(lista_t *lista, void *elemento);
bool lista_quitar(lista_t *lista, size_t posicion, void **eliminado);
void *lista_buscar(lista_t *lista, void *buscado, int (*cmp)(void *, void *));
bool lista_obtener(lista_t *lista, size_t posicion, void **obtenido);
bool lista_esta_vacia(lista_t *lista);

typedef struct iterador {
	nodoL_t *elementoActual;
} iterador_t;

iterador_t *iterador_crear(lista_t *lista);
void iterador_destruir(iterador_t *iterador);
bool iterador_hay_siguiente(iterador_t *iterador);
void iterador_siguiente(iterador_t *iterador);
void *iterador_elemento_actual(iterador_t *iterador);

#endif /* LISTA_H */