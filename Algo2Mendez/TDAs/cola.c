#include "cola.h"

cola_t* cola_crear()
{
    return (cola_t *)lista_crear();
}

void cola_destruir(cola_t* cola)
{
    lista_destruir((lista_t *)cola);
}

void cola_destruir_todo(cola_t *cola, void (*destructor)(void *))
{
    lista_destruir_todo((lista_t *)cola, destructor);
}

size_t cola_cantidad(cola_t *cola)
{
    return lista_cantidad((lista_t *)cola);
}

void *cola_frente(cola_t* cola)
{
    void *elemento = NULL;

    if (!lista_obtener((lista_t *)cola, 0, &elemento))
        return NULL;
         
    return elemento;
}

bool cola_vacia(cola_t* cola)
{
    return lista_esta_vacia((lista_t *)cola);
}

bool cola_encolar(cola_t* cola, void* elemento)
{
    return lista_agregar_final((lista_t *)cola, elemento);
}

void  *cola_desencolar(cola_t* cola)
{
    void *elemento = NULL;

    if (!lista_quitar((lista_t *)cola, 0, &elemento))
        return NULL;

    return elemento;
}
