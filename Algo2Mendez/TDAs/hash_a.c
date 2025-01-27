#include "hash_a.h"

hash_t *hash_crear(size_t capacidad_inicial)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash)
		return NULL;

	if (capacidad_inicial < 3)
		capacidad_inicial = 3;

	hash->tabla = calloc(capacidad_inicial, sizeof(nodoHA_t *));
	if (!hash->tabla) {
		free(hash);
		return NULL;
	}

	hash->capacidad = capacidad_inicial;

	return hash;
}

size_t hash_cantidad(const hash_t *hash)
{
	if (!hash)
		return 0;

	return hash->cantidad;
}

size_t func_hash(const char *clave, size_t capacidad)
{
	size_t hash = 0;
	for (size_t i = 0; clave[i]; i++)
		hash = (hash * 31) + (size_t)clave[i];

	return hash % capacidad;
}

void rehash(hash_t *hash)
{
    size_t nueva_capacidad = hash->capacidad * 2;

    nodoHA_t **nueva_tabla = calloc(nueva_capacidad, sizeof(nodoHA_t *));
    if (!nueva_tabla)
        return;

    for (size_t i = 0; i < hash->capacidad; i++)
    {
        nodoHA_t *nodo = hash->tabla[i];
        while (nodo)
        {
            nodoHA_t *nodo_siguiente = nodo->siguiente;
            size_t indice = func_hash(nodo->clave, nueva_capacidad);
            nodo->siguiente = nueva_tabla[indice];
            nueva_tabla[indice] = nodo;
            nodo = nodo_siguiente;
        }
    }

    free(hash->tabla);
    hash->tabla = nueva_tabla;
    hash->capacidad = nueva_capacidad;
}

bool hash_insertar(hash_t *hash, const char *clave, void *dato,
		   void **encontrado)
{
	if (!hash || !clave)
		return false;

    if (hash->cantidad / hash->capacidad >= 0.75)
    {
        rehash(hash);
    }

	size_t indice = func_hash(clave, hash->capacidad);

	nodoHA_t *nodo = hash->tabla[indice];

	while (nodo) {
		if (strcmp(nodo->clave, clave) == 0) {
			if (encontrado)
				*encontrado = nodo->dato;

			nodo->dato = dato;
			return true;
		}

		nodo = nodo->siguiente;
	}

	if (encontrado)
		*encontrado = NULL;

	nodoHA_t *nuevo_nodo = calloc(1, sizeof(nodoHA_t));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->clave = calloc(strlen(clave) + 1, sizeof(char));
	if (!nuevo_nodo->clave) {
		free(nuevo_nodo);
		return false;
	}
	strcpy(nuevo_nodo->clave, clave);

	nuevo_nodo->dato = dato;
	nuevo_nodo->siguiente = hash->tabla[indice];
	hash->tabla[indice] = nuevo_nodo;

	hash->cantidad++;

	return true;
}

void *hash_buscar(const hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t indice = func_hash(clave, hash->capacidad);

	nodoHA_t *nodo = hash->tabla[indice];

	while (nodo) {
		if (strcmp(nodo->clave, clave) == 0)
			return nodo->dato;

		nodo = nodo->siguiente;
	}

	return NULL;
}

bool hash_contiene(const hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return false;

	return hash_buscar(hash, clave) != NULL;
}

void *hash_borrar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t indice = func_hash(clave, hash->capacidad);

	nodoHA_t *nodo = hash->tabla[indice];
	nodoHA_t *nodo_anterior = NULL;

	while (nodo) {
		if (strcmp(nodo->clave, clave) == 0) {
			if (nodo_anterior)
				nodo_anterior->siguiente = nodo->siguiente;
			else
				hash->tabla[indice] = nodo->siguiente;

			void *dato = nodo->dato;
			free(nodo->clave);
			free(nodo);

			hash->cantidad--;

			return dato;
		}

		nodo_anterior = nodo;
		nodo = nodo->siguiente;
	}

	return NULL;
}

size_t hash_iterar(const hash_t *hash, bool (*f)(const char *, void *, void *),
		   void *ctx)
{
	if (!hash || !f)
		return 0;

	size_t cantidad = 0;

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodoHA_t *nodo = hash->tabla[i];

		while (nodo) {
			if (!f(nodo->clave, nodo->dato, ctx))
				return cantidad;

			nodo = nodo->siguiente;
			cantidad++;
		}
	}

	return cantidad;
}

void hash_destruir(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodoHA_t *nodo = hash->tabla[i];

		while (nodo) {
			nodoHA_t *nodo_a_borrar = nodo;
			nodo = nodo->siguiente;

			if (destructor)
				destructor(nodo_a_borrar->dato);

			free(nodo_a_borrar->clave);
			free(nodo_a_borrar);
		}
	}

	free(hash->tabla);
	free(hash);
}