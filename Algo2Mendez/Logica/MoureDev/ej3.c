/*
 * EJERCICIO:
 * - Muestra ejemplos de creación de todas las estructuras soportadas por defecto en tu lenguaje.
 * - Utiliza operaciones de inserción, borrado, actualización y ordenación.
 *
 * DIFICULTAD EXTRA (opcional):
 * Crea una agenda de contactos por terminal.
 * - Debes implementar funcionalidades de búsqueda, inserción, actualización y eliminación de contactos.
 * - Cada contacto debe tener un nombre y un número de teléfono.
 * - El programa solicita en primer lugar cuál es la operación que se quiere realizar, y a continuación
 *   los datos necesarios para llevarla a cabo.
 * - El programa no puede dejar introducir números de teléfono no númericos y con más de 11 dígitos.
 *   (o el número de dígitos que quieras)
 * - También se debe proponer una operación de finalización del programa.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct contacto {
	char *nombre;
	long telefono;
};

struct agenda {
	struct contacto *contactos;
	int cantidad;
	int capacidad;
};

unsigned int hash(char *clave, int capacidad)
{
	unsigned int indice = 0;

	for (size_t i = 0; i < strlen(clave); i++) {
		indice += (unsigned int)clave[i];
	}

	return indice % capacidad;
}

void agregar_contacto(struct agenda *agenda)
{
	system("clear");

	char *nombre = calloc(1, sizeof(char) * 100);
	if (!nombre)
		return;
	long numero = 0;

	printf("Ingrese el nombre: ");
	scanf("%99s", nombre);
	printf("Ingrese el numero de telefono: ");
	scanf("%ld", &numero);
	if (numero < 1000000000 || numero > 99999999999) {
		free(nombre);
		return;
	}

	unsigned int indice = hash(nombre, agenda->capacidad);

	while (agenda->contactos[indice].nombre) {
		indice++;

		if (indice == agenda->capacidad)
			indice = 0;
	}

	agenda->contactos[indice].nombre = malloc(strlen(nombre) + 1);
	if (!agenda->contactos[indice].nombre) {
		free(nombre);
		return;
	}
	strcpy(agenda->contactos[indice].nombre, nombre);
	agenda->contactos[indice].telefono = numero;
	agenda->cantidad++;

	free(nombre);

    while (getchar() != '\n');
}

void agrandar_agenda(struct agenda *agenda)
{
	if ((float)agenda->cantidad / agenda->capacidad < 0.75)
		return;

	struct contacto *nueva_agenda =
		malloc(agenda->capacidad * 2 * sizeof(struct contacto));
	if (!nueva_agenda)
		return;

	for (int i = 0; i < agenda->capacidad; i++) {
		if (agenda->contactos[i].nombre) {
			unsigned int indice = hash(agenda->contactos[i].nombre,
						   agenda->capacidad * 2);

			strcpy(agenda->contactos[i].nombre,
			       nueva_agenda[indice].nombre);
			nueva_agenda[indice].telefono =
				agenda->contactos[i].telefono;
		}
	}

	free(agenda->contactos);
	agenda->contactos = nueva_agenda;
	agenda->capacidad = agenda->capacidad * 2;
}

void buscar_contacto(struct agenda *agenda)
{
	system("clear");

	char *nombre = malloc(sizeof(char) * 100);
	if (!nombre)
		return;

	printf("Ingrese el nombre: ");
	scanf("%s", nombre);

	unsigned int indice = hash(nombre, agenda->capacidad);

	while (agenda->contactos[indice].nombre) {
		if (strcmp(agenda->contactos[indice].nombre, nombre) == 0) {
			printf("Nombre : %s\n",
			       agenda->contactos[indice].nombre);
			printf("Telefono: %ld\n",
			       agenda->contactos[indice].telefono);

            while (getchar() != '\n');

			return;
		}

		indice++;
	}

	printf("No encontrado\n");
    while (getchar() != '\n');
}

void actualizar_contacto(struct agenda *agenda)
{
	system("clear");

	char *nombre = malloc(sizeof(char) * 100);
	if (!nombre)
		return;

	printf("Ingrese el nombre: ");
	scanf("%s", nombre);

	long numero = 0;
	printf("Ingrese el nuevo numero: ");
	scanf("%ld", &numero);

	unsigned int indice = hash(nombre, agenda->capacidad);

	while (agenda->contactos[indice].nombre) {
		if (strcmp(agenda->contactos[indice].nombre, nombre) == 0) {
			agenda->contactos[indice].telefono = numero;
            while (getchar() != '\n');
			return;
		}

		indice++;
	}

	printf("No encontrado\n");
    while (getchar() != '\n');
}

void eliminar_contacto(struct agenda *agenda)
{
	system("clear");

	char *nombre = malloc(sizeof(char) * 100);
	if (!nombre)
		return;

	printf("Ingrese el nombre: ");
	scanf("%s", nombre);

	unsigned int indice = hash(nombre, agenda->capacidad);

	while (agenda->contactos[indice].nombre) {
		if (strcmp(agenda->contactos[indice].nombre, nombre) == 0) {
			free(agenda->contactos[indice].nombre);
			agenda->contactos[indice].nombre = NULL;
			agenda->contactos[indice].telefono = 0;

            while (getchar() != '\n');

			return;
		}

		indice++;
	}

	printf("No encontrado");
    while (getchar() != '\n');
}

int main()
{
	bool continuar = true;

	struct agenda agenda;

	agenda.contactos = malloc(10 * sizeof(struct contacto));
	if (!agenda.contactos)
		return 0;

	agenda.cantidad = 0;
	agenda.capacidad = 10;

	while (continuar) {
		printf("Seleccione una opcion: \n");
		printf("1. Agregar contacto\n");
		printf("2. Buscar contacto\n");
		printf("3. Actualizar contacto\n");
		printf("4. Eliminar contacto\n");
		printf("5. Salir\n");

		char opcion = 0;
		printf("Ingrese su opcion: ");
		if (scanf(" %c", &opcion) != 1)
			printf("Error al leer");

		switch (opcion) {
		case '1':
			agregar_contacto(&agenda);
			agrandar_agenda(&agenda);
			break;
		case '2':
			buscar_contacto(&agenda);
			break;
		case '3':
			actualizar_contacto(&agenda);
			break;
		case '4':
			eliminar_contacto(&agenda);
			break;
		case '5':
			continuar = false;
			break;
		}

        system("clear");
	}
}