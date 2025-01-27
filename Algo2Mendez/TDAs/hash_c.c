#include "hash_c.h"

#define VACIO 0
#define OCUPADO 1
#define BORRADO 2

hash_c_t *hashC_crear(size_t capacidad)
{
	hash_c_t *hash = calloc(1, sizeof(hash_c_t));
	if (!hash)
		return NULL;

	if (capacidad < 3)
		capacidad = 3;

	hash->claves = calloc(capacidad, sizeof(char *));
	if (!hash->claves) {
		free(hash);
		return NULL;
	}

	hash->datos = calloc(capacidad, sizeof(void *));
	if (!hash->datos) {
		free(hash->claves);
		free(hash);
		return NULL;
	}

	hash->estado = calloc(capacidad, sizeof(int));
	if (!hash->estado) {
		free(hash->datos);
		free(hash->claves);
		free(hash);
		return NULL;
	}

	hash->capacidad = capacidad;
	hash->cantidad = 0;

	return hash;
}

size_t hashC_cantidad(const hash_c_t *hash)
{
	if (!hash)
		return 0;

	return hash->cantidad;
}

size_t probing_lineal(size_t pos, size_t capacidad)
{
	return (pos + 1) % capacidad;
}

size_t probing_cuadratico(size_t pos, size_t capacidad)
{
	return (pos + 1 + pos * pos) % capacidad;
}

size_t func_hashC(const char *clave, size_t capacidad)
{
	size_t hash = 0;
	for (size_t i = 0; clave[i]; i++) {
		hash = 31 * hash + (size_t)clave[i];
	}

	return hash % capacidad;
}

void rehashC(hash_c_t *hash)
{
	size_t nueva_capacidad = hash->capacidad * 2;
	char **nuevas_claves = calloc(nueva_capacidad, sizeof(char *));
	void **nuevos_datos = calloc(nueva_capacidad, sizeof(void *));
	int *nuevo_estado = calloc(nueva_capacidad, sizeof(int));

	if (!nuevas_claves || !nuevos_datos || !nuevo_estado) {
		free(nuevas_claves);
		free(nuevos_datos);
		free(nuevo_estado);
		return;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->estado[i] == OCUPADO) {
			size_t pos =
				func_hashC(hash->claves[i], nueva_capacidad);
			while (nuevo_estado[pos] == OCUPADO)
				pos = probing_lineal(pos, nueva_capacidad);

			nuevas_claves[pos] = hash->claves[i];
			nuevos_datos[pos] = hash->datos[i];
			nuevo_estado[pos] = OCUPADO;
		}
	}

	free(hash->claves);
	free(hash->datos);
	free(hash->estado);

	hash->claves = nuevas_claves;
	hash->datos = nuevos_datos;
	hash->estado = nuevo_estado;
	hash->capacidad = nueva_capacidad;
}

bool hashC_insertar(hash_c_t *hash, const char *clave, void *dato,
		    void **encontrado)
{
	if (!hash || !clave)
		return false;

	if (hash->cantidad / hash->capacidad >= 0.7)
		rehashC(hash);

    size_t pos = func_hashC(clave, hash->capacidad);
    while (hash->estado[pos] == OCUPADO) {
        if (strcmp(hash->claves[pos], clave) == 0) {
            if (encontrado)
                *encontrado = hash->datos[pos];
            hash->datos[pos] = dato;
            return true;
        }
        pos = probing_lineal(pos, hash->capacidad);
    }

    hash->claves[pos] = calloc(strlen(clave) + 1, sizeof(char));
    if (!hash->claves[pos])
        return false;
    
    strcpy(hash->claves[pos], clave);

    hash->datos[pos] = dato;
    hash->estado[pos] = OCUPADO;

    hash->cantidad++;

	return true;
}

void *hashC_buscar(const hash_c_t *hash, const char *clave)
{
    if (!hash || !clave)
        return NULL;

    size_t pos = func_hashC(clave, hash->capacidad);
    while (hash->estado[pos] != VACIO) {
        if (hash->estado[pos] == OCUPADO &&
            strcmp(hash->claves[pos], clave) == 0)
            return hash->datos[pos];

        pos = probing_lineal(pos, hash->capacidad);
    }

    return NULL;
}

bool hashC_contiene(const hash_c_t *hash, const char *clave)
{
    if (!hash || !clave)
        return false;

    size_t pos = func_hashC(clave, hash->capacidad);
    while (hash->estado[pos] != VACIO) {
        if (hash->estado[pos] == OCUPADO &&
            strcmp(hash->claves[pos], clave) == 0)
            return true;

        pos = probing_lineal(pos, hash->capacidad);
    }

    return false;
}

void *hashC_borrar(hash_c_t *hash, const char *clave)
{
    if (!hash || !clave)
        return NULL;

    size_t pos = func_hashC(clave, hash->capacidad);
    while (hash->estado[pos] != VACIO) {
        if (hash->estado[pos] == OCUPADO &&
            strcmp(hash->claves[pos], clave) == 0) {
            free(hash->claves[pos]);
            hash->estado[pos] = BORRADO;
            hash->cantidad--;
            return hash->datos[pos];
        }

        pos = probing_lineal(pos, hash->capacidad);
    }

    return NULL;
}

size_t hashC_iterar(const hash_c_t *hash,
            bool (*f)(const char *, void *, void *), void *ctx)
{
    if (!hash || !f)
        return 0;

    size_t cantidad = 0;
    for (size_t i = 0; i < hash->capacidad; i++) {
        if (hash->estado[i] == OCUPADO) {
            if (!f(hash->claves[i], hash->datos[i], ctx))
                break;
            cantidad++;
        }
    }

    return cantidad;
}

void hashC_destruir(hash_c_t *hash, void destructor(void *))
{
	if (!hash)
		return;

	if (destructor) {
		for (size_t i = 0; i < hash->capacidad; i++) {
			if (hash->estado[i] == OCUPADO)
				destructor(hash->datos[i]);
		}
	}

    for (size_t i = 0; i < hash->capacidad; i++) {
        if (hash->estado[i] == OCUPADO)
            free(hash->claves[i]);
    }

	free(hash->claves);
	free(hash->datos);
	free(hash->estado);
	free(hash);
}
