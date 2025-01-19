#ifndef PILA_H
#define PILA_H

#include <stdbool.h>
#include <stdlib.h>

#include "lista.h"

typedef struct pila {
	lista_t *lista;
} pila_t;

pila_t *pila_crear();
void pila_destruir(pila_t *pila);
void pila_destruir_todo(pila_t *pila, void (*destructor)(void *));
size_t pila_cantidad(pila_t *pila);
void *pila_tope(pila_t *pila);
bool pila_apilar(pila_t *pila, void *elemento);
void *pila_despilar(pila_t *pila);
bool pila_vacia(pila_t *pila);

#endif /*PILA_H*/