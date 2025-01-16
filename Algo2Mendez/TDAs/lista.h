#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

typedef struct nodo nodo_t;
typedef struct lista lista_t;

lista_t *lista_crear();
bool lista_agregar(lista_t *lista, size_t posicion, void *elemento);

#endif LISTA_H