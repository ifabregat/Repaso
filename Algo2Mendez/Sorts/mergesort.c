#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(void *vector, void *temp, int izq, int mitad, int der, size_t size,
	   int (*cmp)(const void *, const void *))
{
	int i = izq;
	int j = mitad + 1;
	int k = izq;

	char *v = (char *)vector;
	char *t = (char *)temp;

	while (i <= mitad && j <= der) {
		if (cmp(v + i * size, v + j * size) <= 0) {
			memcpy(t + k * size, v + i * size, size);
			i++;
		} else {
			memcpy(t + k * size, v + j * size, size);
			j++;
		}
		k++;
	}

	while (i <= mitad) {
		memcpy(t + k * size, v + i * size, size);
		i++;
		k++;
	}

	while (j <= der) {
		memcpy(t + k * size, v + j * size, size);
		j++;
		k++;
	}

	for (i = izq; i <= der; i++) {
		memcpy(v + i * size, t + i * size, size);
	}
}

void mergesort(void *vector, void *temp, int izq, int der, size_t size,
	       int (*cmp)(const void *, const void *))
{
	if (izq < der) {
		int mitad = izq + (der - izq) / 2;

		mergesort(vector, temp, izq, mitad, size, cmp);
		mergesort(vector, temp, mitad + 1, der, size, cmp);

		merge(vector, temp, izq, mitad, der, size, cmp);
	}
}

int cmp_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int main()
{
	int vector[] = { 23, 1, 12, 9, 3, 32, 5, 17 };

	size_t ml = sizeof(vector) / sizeof(vector[0]);

	void *temp = malloc(ml * sizeof(int));
	if (temp == NULL) {
		fprintf(stderr, "Error al asignar memoria\n");
		return 1;
	}

	printf("Vector original: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	mergesort(vector, temp, 0, ml - 1, sizeof(int), cmp_int);

	printf("Vector ordenado: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	free(temp);

	return 0;
}
