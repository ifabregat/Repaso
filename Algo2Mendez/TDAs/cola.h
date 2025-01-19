#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include <stdlib.h>

#include "lista.h"

typedef struct cola {
	lista_t *lista;
} cola_t;

cola_t *cola_crear();
void cola_destruir(cola_t *cola);
void cola_destruir_todo(cola_t *cola, void (*destructor)(void *));
size_t cola_cantidad(cola_t *cola);
void *cola_frente(cola_t *cola);
bool cola_encolar(cola_t *cola, void *elemento);
void *cola_desencolar(cola_t *cola);
bool cola_vacia(cola_t *cola);

#endif /*COLA_H*/