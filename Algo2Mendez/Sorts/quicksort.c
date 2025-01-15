#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

size_t particion(void *vector, size_t izq, size_t der, size_t size,
		 int (*cmp)(const void *, const void *))
{
	byte *v = (byte *)vector;
	byte *pivote = v + izq * size;
	size_t i = izq + 1;
	size_t j = der;

	while (i <= j) {
		while (i <= j && cmp(v + i * size, pivote) <= 0) {
			i++;
		}

		while (i <= j && cmp(v + j * size, pivote) > 0) {
			j--;
		}

		if (i < j) {
			for (size_t k = 0; k < size; k++) {
				byte temp = v[i * size + k];
				v[i * size + k] = v[j * size + k];
				v[j * size + k] = temp;
			}
		}
	}

	for (size_t k = 0; k < size; k++) {
		byte temp = v[izq * size + k];
		v[izq * size + k] = v[j * size + k];
		v[j * size + k] = temp;
	}

	return j;
}

void quicksort(void *vector, size_t izq, size_t der, size_t size,
	       int (*cmp)(const void *, const void *))
{
	if (izq < der) {
		size_t pivote = particion(vector, izq, der, size, cmp);

		if (izq < pivote) {
			quicksort(vector, izq, pivote - 1, size, cmp);
		}

		if (pivote < der) {
			quicksort(vector, pivote + 1, der, size, cmp);
		}
	}
}

int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main()
{
	int vector[] = { 23, 1, 12, 9, 3, 32, 5, 17 };

	size_t ml = sizeof(vector) / sizeof(vector[0]);

	printf("Vector original: ");

	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}

	printf("\n");

	quicksort(vector, 0, ml - 1, sizeof(int), cmp);

	printf("Vector ordenado: ");

	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}

	printf("\n");

	return 0;
}
