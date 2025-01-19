#include "pila.h"

pila_t *pila_crear()
{
    return (pila_t *)lista_crear();
}

void pila_destruir(pila_t *pila)
{
    lista_destruir((lista_t *)pila);
}

void pila_destruir_todo(pila_t *pila, void (*destructor)(void *))
{
    lista_destruir_todo((lista_t *)pila, destructor);
}

size_t pila_cantidad(pila_t *pila)
{
    return lista_cantidad((lista_t *)pila);
}

void *pila_tope(pila_t *pila)
{
    void *elemento = NULL;

    if (!lista_obtener((lista_t *)pila, 0, &elemento))
        return NULL;

    return elemento;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
    return lista_agregar((lista_t *)pila, 0, elemento);
}

void *pila_despilar(pila_t *pila)
{
    void *elemento = NULL;

    if (!lista_quitar((lista_t *)pila, 0, &elemento))
        return NULL;

    return elemento;
}