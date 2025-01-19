#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct nodoA {
	void *dato;
	struct nodoA *izq;
	struct nodoA *der;
} nodoA_t;

typedef struct abb {
	nodoA_t *raiz;
	size_t cantidad;
	int (*cmp)(void *, void *);
} abb_t;

abb_t *abb_crear(int (*cmp)(void *, void *));
void abb_destruir(abb_t *abb);
void abb_destruir_todo(abb_t *abb, void (*destructor)(void *));
bool abb_insertar(abb_t *abb, void *elemento);
bool abb_quitar(abb_t *abb, void *elemento, void **eliminado);
void *abb_obtener(abb_t *abb, void *elemento);
size_t abb_cantidad(abb_t *abb);

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx);
size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx);
size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx);

#endif /*ABB_H*/