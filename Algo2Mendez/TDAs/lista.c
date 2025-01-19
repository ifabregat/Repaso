#include "lista.h"

lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	if (!lista)
		return NULL;

	return lista;
}

void destruir_nodo(nodoL_t *nodo, void (*destructor)(void *))
{
	while (nodo) {
		nodoL_t *siguiente = nodo->siguiente;

		if (destructor)
			destructor(nodo->dato);

		free(nodo);
		nodo = siguiente;
	}
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;

	destruir_nodo(lista->primer, NULL);
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (!lista)
		return;

	destruir_nodo(lista->primer, destructor);
	free(lista);
}

size_t lista_cantidad(lista_t *lista)
{
	if (!lista)
		return 0;

	return lista->cantidad;
}

nodoL_t *obtener_nodo(lista_t *lista, size_t posicion)
{
	if (!lista || posicion >= lista->cantidad)
		return NULL;

	nodoL_t *anterior = lista->primer;
	for (size_t i = 0; i < posicion; i++) {
		anterior = anterior->siguiente;
	}

	return anterior;
}

bool alInicio(lista_t *lista, nodoL_t *nodo)
{
	nodo->siguiente = lista->primer;
	lista->primer = nodo;

	if (!lista->ultimo)
		lista->ultimo = nodo;

	return true;
}

bool alFinal(lista_t *lista, nodoL_t *nodo)
{
	lista->ultimo->siguiente = nodo;
	lista->ultimo = nodo;

	return true;
}

bool otraPosicion(lista_t *lista, nodoL_t *nodo, size_t posicion)
{
	nodoL_t *anterior = obtener_nodo(lista, posicion - 1);
	if (!anterior)
		return false;

	nodo->siguiente = anterior->siguiente;
	anterior->siguiente = nodo;

	return true;
}

bool lista_agregar(lista_t *lista, size_t posicion, void *elemento)
{
	if (!lista || posicion > lista->cantidad)
		return false;

	nodoL_t *nodoInsertar = calloc(1, sizeof(nodoL_t));
	if (!nodoInsertar)
		return false;

	nodoInsertar->dato = elemento;

	if (posicion == 0) {
		if (!alInicio(lista, nodoInsertar)) {
			free(nodoInsertar);
			return false;
		}
	} else if (posicion == lista->cantidad) {
		if (!alFinal(lista, nodoInsertar)) {
			free(nodoInsertar);
			return false;
		}
	} else {
		if (!otraPosicion(lista, nodoInsertar, posicion)) {
			free(nodoInsertar);
			return false;
		}
	}

	lista->cantidad++;
	return true;
}

bool lista_agregar_final(lista_t *lista, void *elemento)
{
	return lista_agregar(lista, lista->cantidad, elemento);
}

bool lista_quitar(lista_t *lista, size_t posicion, void **eliminado)
{
	if (!lista || posicion >= lista->cantidad)
		return false;

	nodoL_t *nodoEliminar = NULL;

	if (posicion == 0) {
		nodoEliminar = lista->primer;
		lista->primer = lista->primer->siguiente;
	} else {
		nodoL_t *anterior = obtener_nodo(lista, posicion - 1);
		if (!anterior)
			return false;

		nodoEliminar = anterior->siguiente;
		anterior->siguiente = nodoEliminar->siguiente;
	}

	if (posicion == lista->cantidad - 1)
		lista->ultimo = obtener_nodo(lista, lista->cantidad - 2);

	if (eliminado)
		*eliminado = nodoEliminar->dato;

	free(nodoEliminar);
	lista->cantidad--;
	return true;
}

void *lista_buscar(lista_t *lista, void *buscado, int (*cmp)(void *, void *))
{
	if (!lista || !cmp)
		return NULL;

	nodoL_t *actual = lista->primer;
	while (actual) {
		if (cmp(actual->dato, buscado) == 0)
			return actual->dato;

		actual = actual->siguiente;
	}

	return NULL;
}

bool lista_obtener(lista_t *lista, size_t posicion, void **obtenido)
{
	if (!lista || posicion >= lista->cantidad)
		return false;

	nodoL_t *nodo = obtener_nodo(lista, posicion);
	if (!nodo)
		return false;

	if (obtenido)
		*obtenido = nodo->dato;

	return true;
}

bool lista_esta_vacia(lista_t *lista)
{
	return lista && lista->cantidad == 0;
}

iterador_t *iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	iterador_t *iterador = calloc(1, sizeof(iterador_t));
	if (!iterador)
		return NULL;

	iterador->elementoActual = lista->primer;
	return iterador;
}

void iterador_destruir(iterador_t *iterador)
{
	free(iterador);
}

bool iterador_hay_siguiente(iterador_t *iterador)
{
	return iterador && iterador->elementoActual;
}

void iterador_siguiente(iterador_t *iterador)
{
	if (!iterador || !iterador->elementoActual)
		return;

	iterador->elementoActual = iterador->elementoActual->siguiente;
}

void *iterador_elemento_actual(iterador_t *iterador)
{
	if (!iterador || !iterador->elementoActual)
		return NULL;

	return iterador->elementoActual->dato;
}
