#ifndef HASH_C_H
#define HASH_C_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct hash_c {
	char **claves;
	void **datos;
	int *estado;
	size_t capacidad;
	size_t cantidad;
} hash_c_t;

hash_c_t *hashC_crear(size_t);
size_t hashC_cantidad(const hash_c_t *hash);
bool hashC_insertar(hash_c_t *hash, const char *clave, void *dato,
		    void **encontrado);
void *hashC_buscar(const hash_c_t *hash, const char *clave);
bool hashC_contiene(const hash_c_t *hash, const char *clave);
void *hashC_borrar(hash_c_t *hash, const char *clave);
size_t hashC_iterar(const hash_c_t *hash,
		    bool (*f)(const char *, void *, void *), void *ctx);
void hashC_destruir(hash_c_t *hash, void destructor(void *));

#endif /*HASH_C_H*/