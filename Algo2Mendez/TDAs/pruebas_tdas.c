#include "pa2m.h"

#include "lista.h"
#include "cola.h"
#include "pila.h"
#include "abb.h"
#include "hash_a.h"
#include "hash_c.h"

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
	pa2m_afirmar(iterador != NULL,
		     "Se pudo crear un iterador para la lista");
	void *elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(*(int *)elemento == 5,
		     "El elemento actual es el correcto");
	iterador_siguiente(iterador);
	elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(strcmp((char *)elemento, "chau") == 0,
		     "El elemento actual es el correcto");
	iterador_siguiente(iterador);
	elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(strcmp((char *)elemento, "hola") == 0,
		     "El elemento actual es el correcto");
	iterador_siguiente(iterador);
	elemento = iterador_elemento_actual(iterador);
	pa2m_afirmar(*(int *)elemento == 10,
		     "El elemento actual es el correcto");
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
	pa2m_afirmar(cola_encolar(cola, &numero2),
		     "Se pudo agregar un elemento a la cola");
	void *elemento = cola_frente(cola);
	pa2m_afirmar(*(int *)elemento == 5,
		     "El elemento del frente es el correcto");
	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(int *)elemento == 5,
		     "El elemento desencolado es el correcto");
	elemento = cola_frente(cola);
	pa2m_afirmar(*(int *)elemento == 10, "El nuevo frente es el correcto");
	cola_destruir(cola);
}

void pruebasPila()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "La lista creada tiene 0 elementos");
	int numero = 5;
	pa2m_afirmar(pila_apilar(pila, &numero),
		     "Se pudo agregar un elemento a la pila");
	int numero2 = 10;
	pa2m_afirmar(pila_apilar(pila, &numero2),
		     "Se pudo agregar un elemento a la pila");
	void *elemento = pila_tope(pila);
	pa2m_afirmar(*(int *)elemento == 10,
		     "El elemento del tope es el correcto");
	elemento = pila_despilar(pila);
	pa2m_afirmar(*(int *)elemento == 10,
		     "El elemento desapilado es el correcto");
	elemento = pila_tope(pila);
	pa2m_afirmar(*(int *)elemento == 5, "El nuevo tope es el correcto");
	pila_destruir(pila);
}

int cmp(void *e1, void *e2)
{
	return *(int *)e1 - *(int *)e2;
}

void pruebasABB()
{
	abb_t *abb = abb_crear(cmp);
	pa2m_afirmar(abb != NULL, "Puedo crear un ABB");
	int numero = 10;
	pa2m_afirmar(abb_insertar(abb, &numero), "Puedo insertar un numero");
	int numero2 = 5;
	pa2m_afirmar(abb_insertar(abb, &numero2), "Puedo insertar otro numero");
	int numero3 = 15;
	pa2m_afirmar(abb_insertar(abb, &numero3), "Puedo insertar otro numero");
	void *eliminado = NULL;
	pa2m_afirmar(abb_quitar(abb, &numero2, &eliminado),
		     "Puedo quitar un elemento del abb");
	pa2m_afirmar(cmp(eliminado, &numero2) == 0,
		     "El numero eliminado es el correcto");
	abb_destruir(abb);
}

bool imprimir_elemento(void *elemento, void *ctx)
{
	printf("%i ", *(int *)elemento);
	return true;
}

void pruebasIteradorABB()
{
	abb_t *abb = abb_crear(cmp);
	int elemento1 = 50;
	abb_insertar(abb, &elemento1);
	int elemento2 = 54;
	abb_insertar(abb, &elemento2);
	int elemento3 = 20;
	abb_insertar(abb, &elemento3);
	int elemento4 = 10;
	abb_insertar(abb, &elemento4);
	int elemento5 = 30;
	abb_insertar(abb, &elemento5);
	int elemento6 = 15;
	abb_insertar(abb, &elemento6);
	int elemento7 = 60;
	abb_insertar(abb, &elemento7);
	size_t cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en inorden el ABB");
	cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en preorden el ABB");
	cantidad = abb_iterar_postorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en postorden el ABB");
	abb_destruir(abb);
}

void pruebasHashAbierto()
{
	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash abierto");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash tiene 0 elementos");
	int numero = 10;
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, "diez", &numero, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(encontrado == NULL, "No se encontro un elemento previo");
	int numero2 = 15;
	pa2m_afirmar(hash_insertar(hash, "quince", &numero2, &encontrado),
		     "Puedo insertar otro elemento en el hash");
	numero = 20;
	pa2m_afirmar(encontrado == NULL, "No se encontro un elemento previo");
	pa2m_afirmar(hash_insertar(hash, "diez", &numero, &encontrado),
		     "Puedo insertar un elemento con clave repetida");
	pa2m_afirmar(encontrado == &numero, "Se encontro el elemento previo");
	pa2m_afirmar(hash_cantidad(hash) == 2, "El hash tiene 1 elemento");
	pa2m_afirmar(hash_contiene(hash, "diez"),
		     "El hash contiene la clave 'diez'");
	pa2m_afirmar(*(int *)hash_buscar(hash, "diez") == 20,
		     "El elemento encontrado es el correcto");
	int numero3 = 25;
	pa2m_afirmar(hash_insertar(hash, "veinticinco", &numero3, NULL),
		     "Puedo insertar otro elemento en el hash");
	int numero4 = 30;
	pa2m_afirmar(hash_insertar(hash, "treinta", &numero4, NULL),
		     "Puedo insertar otro elemento en el hash");
	int numero5 = 35;
	pa2m_afirmar(hash_insertar(hash, "treinta", &numero5, &encontrado),
		     "Puedo insertar un elemento con clave repetida");
	pa2m_afirmar(encontrado == &numero4, "Se encontro el elemento previo");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash tiene 4 elementos");
	int *elemento = hash_borrar(hash, "diez");
	pa2m_afirmar(*elemento == 20, "El elemento eliminado es el correcto");
	hash_destruir(hash, NULL);
}

bool imprimir_elemento_hash(const char *clave, void *elemento, void *ctx)
{
	printf("%s: %i 		", clave, *(int *)elemento);
	return true;
}

void pruebasIteradorHashAbierto()
{
	hash_t *hash = hash_crear(10);
	int numero = 10;
	hash_insertar(hash, "diez", &numero, NULL);
	int numero2 = 15;
	hash_insertar(hash, "quince", &numero2, NULL);
	int numero3 = 20;
	hash_insertar(hash, "veinte", &numero3, NULL);
	int numero4 = 25;
	hash_insertar(hash, "veinticinco", &numero4, NULL);
	int numero5 = 30;
	hash_insertar(hash, "treinta", &numero5, NULL);
	size_t cantidad = hash_iterar(hash, imprimir_elemento_hash, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 5, "Se puede iterar el hash abierto");
	int *elemento = hash_borrar(hash, "veinte");
	pa2m_afirmar(*elemento == 20, "El elemento eliminado es el correcto");
	cantidad = hash_iterar(hash, imprimir_elemento_hash, NULL);
	hash_destruir(hash, NULL);
}

void pruebasHashCerrado()
{
	hash_c_t *hash = hashC_crear(10);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash cerrado");
	pa2m_afirmar(hashC_cantidad(hash) == 0, "El hash tiene 0 elementos");
	int numero = 10;
	void *encontrado = NULL;
	pa2m_afirmar(hashC_insertar(hash, "diez", &numero, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(encontrado == NULL, "No se encontro un elemento previo");
	int numero2 = 15;
	pa2m_afirmar(hashC_insertar(hash, "quince", &numero2, &encontrado),
		     "Puedo insertar otro elemento en el hash");
	numero = 20;
	pa2m_afirmar(encontrado == NULL, "No se encontro un elemento previo");
	pa2m_afirmar(hashC_insertar(hash, "diez", &numero, &encontrado),
		     "Puedo insertar un elemento con clave repetida");
	pa2m_afirmar(encontrado == &numero, "Se encontro el elemento previo");
	pa2m_afirmar(hashC_cantidad(hash) == 2, "El hash tiene 1 elemento");
	pa2m_afirmar(hashC_contiene(hash, "diez"),
		     "El hash contiene la clave 'diez'");
	pa2m_afirmar(*(int *)hashC_buscar(hash, "diez") == 20,
		     "El elemento encontrado es el correcto");
	int numero3 = 25;
	pa2m_afirmar(hashC_insertar(hash, "veinticinco", &numero3, NULL),
		     "Puedo insertar otro elemento en el hash");
	int numero4 = 30;
	pa2m_afirmar(hashC_insertar(hash, "treinta", &numero4, NULL),
		     "Puedo insertar otro elemento en el hash");
	int numero5 = 35;
	pa2m_afirmar(hashC_insertar(hash, "treinta", &numero5, &encontrado),
		     "Puedo insertar un elemento con clave repetida");
	pa2m_afirmar(encontrado == &numero4, "Se encontro el elemento previo");
	pa2m_afirmar(hashC_cantidad(hash) == 4, "El hash tiene 4 elementos");
	int *elemento = hashC_borrar(hash, "diez");
	pa2m_afirmar(*elemento == 20, "El elemento eliminado es el correcto");
	hashC_destruir(hash, NULL);
}

void pruebasIteradorHashCerrado()
{
	hash_c_t *hash = hashC_crear(10);
	int numero = 10;
	hashC_insertar(hash, "diez", &numero, NULL);
	int numero2 = 15;
	hashC_insertar(hash, "quince", &numero2, NULL);
	int numero3 = 20;
	hashC_insertar(hash, "veinte", &numero3, NULL);
	int numero4 = 25;
	hashC_insertar(hash, "veinticinco", &numero4, NULL);
	int numero5 = 30;
	hashC_insertar(hash, "treinta", &numero5, NULL);
	size_t cantidad = hashC_iterar(hash, imprimir_elemento_hash, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 5, "Se puede iterar el hash cerrado");
	int *elemento = hashC_borrar(hash, "veinte");
	pa2m_afirmar(*elemento == 20, "El elemento eliminado es el correcto");
	cantidad = hashC_iterar(hash, imprimir_elemento_hash, NULL);
	hashC_destruir(hash, NULL);
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
	pa2m_nuevo_grupo("Pruebas pila");
	pruebasPila();
	pa2m_nuevo_grupo("Pruebas ABB");
	pruebasABB();
	printf("\n");
	pruebasIteradorABB();
	pa2m_nuevo_grupo("Pruebas hash abierto");
	pruebasHashAbierto();
	printf("\n");
	pruebasIteradorHashAbierto();
	pa2m_nuevo_grupo("Pruebas hash cerrado");
	pruebasHashCerrado();
	printf("\n");
	pruebasIteradorHashCerrado();

	return pa2m_mostrar_reporte();
}