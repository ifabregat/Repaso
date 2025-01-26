#include "abb.h"

abb_t *abb_crear(int (*cmp)(void *, void *))
{
	if (!cmp)
		return NULL;

	abb_t *abb = calloc(1, sizeof(abb_t));
	if (!abb)
		return NULL;

	abb->cmp = cmp;

	return abb;
}

void nodo_destruir(nodoA_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;

	nodo_destruir(nodo->izq, destructor);
	nodo_destruir(nodo->der, destructor);

	if (destructor)
		destructor(nodo->dato);

	free(nodo);
}

void abb_destruir(abb_t *abb)
{
	abb_destruir_todo(abb, NULL);
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (!abb)
		return;

	nodo_destruir(abb->raiz, destructor);

	free(abb);
}

nodoA_t *nodo_crear(void *elemento)
{
	nodoA_t *nodo = calloc(1, sizeof(nodoA_t));
	if (!nodo)
		return NULL;

	nodo->dato = elemento;

	return nodo;
}

nodoA_t *nodo_insertar(nodoA_t *nodo, void *elemento,
		       int (*cmp)(void *, void *), bool *insertado)
{
	if (!nodo) {
		*insertado = true;

		return nodo_crear(elemento);
	}

	int comparacion = cmp(elemento, nodo->dato);

	if (comparacion > 0)
		nodo->der = nodo_insertar(nodo->der, elemento, cmp, insertado);
	else
		nodo->izq = nodo_insertar(nodo->izq, elemento, cmp, insertado);

	return nodo;
}

bool abb_insertar(abb_t *abb, void *elemento)
{
	if (!abb)
		return false;

	bool insertado = false;

	abb->raiz = nodo_insertar(abb->raiz, elemento, abb->cmp, &insertado);

	if (insertado)
		abb->cantidad++;

	return insertado;
}

nodoA_t *nodo_minimo(nodoA_t *nodo)
{
	while (nodo && nodo->izq)
		nodo = nodo->izq;

	return nodo;
}

nodoA_t *nodo_quitar(nodoA_t *nodo, void *elemento, int (*cmp)(void *, void *),
		     void **eliminado)
{
	if (!nodo)
		return NULL;

	int comparacion = cmp(elemento, nodo->dato);

	if (comparacion < 0)
		nodo->izq = nodo_quitar(nodo->izq, elemento, cmp, eliminado);
	else if (comparacion > 0)
		nodo->der = nodo_quitar(nodo->der, elemento, cmp, eliminado);
	else {
		*eliminado = nodo->dato;

		if (!nodo->izq && !nodo->der) {
			free(nodo);
			return NULL;
		}

		if (!nodo->izq) {
			nodoA_t *temp = nodo->der;
			free(nodo);
			return temp;
		}

		if (!nodo->der) {
			nodoA_t *temp = nodo->izq;
			free(nodo);
			return temp;
		}

		nodoA_t *hijo = nodo_minimo(nodo->der);
		nodo->dato = hijo->dato;
		nodo->der =
			nodo_quitar(nodo->der, hijo->dato, cmp, &hijo->dato);
	}

	return nodo;
}

bool abb_quitar(abb_t *abb, void *elemento, void **eliminado)
{
	if (!abb || !abb->raiz)
		return false;

	*eliminado = NULL;
	abb->raiz = nodo_quitar(abb->raiz, elemento, abb->cmp, eliminado);

	if (*eliminado) {
		abb->cantidad--;
		return true;
	}

	return false;
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (!abb)
		return NULL;

	nodoA_t *nodo = abb->raiz;

	while (nodo) {
		int comparacion = abb->cmp(nodo->dato, elemento);

		if (comparacion > 0)
			nodo = nodo->izq;
		else if (comparacion < 0)
			nodo = nodo->der;
		else
			return nodo->dato;
	}

	return NULL;
}

size_t abb_cantidad(abb_t *abb)
{
	if (!abb)
		return 0;

	return abb->cantidad;
}

size_t inorden_r(nodoA_t *nodo, bool (*f)(void *, void *), void *ctx,
		 size_t *contador, bool *continuar)
{
	if (!nodo || !(*continuar))
		return *contador;

	inorden_r(nodo->izq, f, ctx, contador, continuar);

	if (!(*continuar))
		return *contador;

	if (!f(nodo->dato, ctx)) {
		*continuar = false;
		return *contador;
	}

	(*contador)++;

	inorden_r(nodo->der, f, ctx, contador, continuar);

	return *contador;
}

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz || !f)
		return 0;

	size_t contador = 0;
	bool continuar = true;

	inorden_r(abb->raiz, f, ctx, &contador, &continuar);
	return contador;
}

size_t preorden_r(nodoA_t *nodo, bool (*f)(void *, void *), void *ctx,
		  size_t *contador, bool *continuar)
{
	if (!nodo || !(*continuar))
		return *contador;

	(*contador)++;

	if (!f(nodo->dato, ctx)) {
		*continuar = false;
		return *contador;
	}

	preorden_r(nodo->izq, f, ctx, contador, continuar);
	preorden_r(nodo->der, f, ctx, contador, continuar);

	return *contador;
}

size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz || !f)
		return 0;

	size_t contador = 0;
	bool continuar = true;

	return preorden_r(abb->raiz, f, ctx, &contador, &continuar);
}

size_t postorden_r(nodoA_t *nodo, bool (*f)(void *, void *), void *ctx,
		   size_t *contador, bool *continuar)
{
	if (!nodo || !(*continuar))
		return *contador;

	postorden_r(nodo->izq, f, ctx, contador, continuar);
	postorden_r(nodo->der, f, ctx, contador, continuar);

	if (!(*continuar))
		return *contador;

	(*contador)++;

	if (!f(nodo->dato, ctx))
		*continuar = false;

	return *contador;
}

size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz || !f)
		return 0;

	size_t contador = 0;
	bool continuar = true;

	return postorden_r(abb->raiz, f, ctx, &contador, &continuar);
}