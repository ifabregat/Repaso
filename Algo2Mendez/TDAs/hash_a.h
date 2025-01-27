#ifndef HASH_A_H
#define HASH_A_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct nodoHA {
	char *clave;
	void *dato;
	struct nodoHA *siguiente;
} nodoHA_t;

typedef struct hash {
	nodoHA_t **tabla;
	size_t capacidad;
	size_t cantidad;
} hash_t;

hash_t *hash_crear(size_t);
size_t hash_cantidad(const hash_t *hash);
bool hash_insertar(hash_t *hash, const char *clave, void *dato,
		   void **encontrado);
void *hash_buscar(const hash_t *hash, const char *clave);
bool hash_contiene(const hash_t *hash, const char *clave);
void *hash_borrar(hash_t *hash, const char *clave);
size_t hash_iterar(const hash_t *hash, bool (*f)(const char *, void *, void *),
		   void *ctx);
void hash_destruir(hash_t *hash, void (*destructor)(void *));

#endif /*HASHA_H*/