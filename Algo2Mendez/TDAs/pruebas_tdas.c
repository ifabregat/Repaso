#include "pa2m.h"

#include "lista.h"
#include "cola.h"

#include <string.h>

void pruebasLista()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "La lista creada tiene 0 elementos");
	int numero = 5;
	pa2m_afirmar(lista_agregar(lista, 0, &numero),
		     "Se pudo agregar un elemento a la lista");
	pa2m_afirmar(lista_cantidad(lista) == 1, "La lista tiene 1 elemento");
	char *cadena = "hola";
	pa2m_afirmar(lista_agregar(lista, 0, cadena),
		     "Se pudo agregar un elemento a la lista en la posicion 0");
	void *elemento = NULL;
	lista_obtener(lista, 0, &elemento);
	pa2m_afirmar(strcmp((char *)elemento, "hola") == 0,
		     "El elemento obtenido es el correcto");
	lista_destruir(lista);
}

void pruebasListaNulos()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_cantidad(NULL) == 0,
		     "La cantidad de una lista nula es 0");
	pa2m_afirmar(!lista_agregar(NULL, 0, NULL),
		     "No se puede agregar un elemento a una lista nula");
	pa2m_afirmar(lista_agregar(lista, 0, NULL),
		     "Si puede agregar un elemento nulo a una lista");
	pa2m_afirmar(
		!lista_agregar(lista, 3, NULL),
		"No se puede agregar un elemento a una lista en una posicion "
		"invalida");
	pa2m_afirmar(!lista_obtener(NULL, 0, NULL),
		     "No se puede obtener un elemento de una lista nula");
	pa2m_afirmar(
		!lista_obtener(lista, 9, NULL),
		"No se puede obtener un elemento de una lista en una posicion "
		"invalida");
	lista_destruir(lista);
}

void pruebasIteradorLista()
{
	lista_t *lista = lista_crear();
	int numero = 5;
	lista_agregar(lista, 0, &numero);
	char *cadena = "hola";
	lista_agregar(lista, 1, cadena);
	char *cadena2 = "chau";
	lista_agregar(lista, 1, cadena2);
	int numero2 = 10;
	lista_agregar_final(lista, &numero2);
	iterador_t *iterador = iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Se pudo crear un iterador para la lista");
	void *elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(*(int *)elemento == 5, "El elemento actual es el correcto");
	iterador_siguiente(iterador);
	elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(strcmp((char *)elemento, "chau") == 0, "El elemento actual es el correcto");
	iterador_siguiente(iterador);
	elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(strcmp((char *)elemento, "hola") == 0,
		     "El elemento actual es el correcto");
	iterador_siguiente(iterador);
	elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(*(int *)elemento == 10, "El elemento actual es el correcto");
	iterador_destruir(iterador);
	lista_destruir(lista);
}

void pruebasCola()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "La lista creada tiene 0 elementos");
	int numero = 5;
	pa2m_afirmar(cola_encolar(cola, &numero),
		     "Se pudo agregar un elemento a la cola");
	int numero2 = 10;
	pa2m_afirmar(cola_encolar(cola, &numero2), "Se pudo agregar un elemento a la cola");
	void *elemento = cola_frente(cola);
	pa2m_afirmar(*(int *)elemento == 5, "El elemento del frente es el correcto");
	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(int *)elemento == 5, "El elemento desencolado es el correcto");
	elemento = cola_frente(cola);
	pa2m_afirmar(*(int *)elemento == 10, "El nuevo frente es el correcto");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas lista");
	pruebasLista();
	printf("\n");
	pruebasListaNulos();
	printf("\n");
	pruebasIteradorLista();
	pa2m_nuevo_grupo("Pruebas cola");
	pruebasCola();

	return pa2m_mostrar_reporte();
}