#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t particion(void *vector, size_t izq, size_t der, size_t size,
		 int (*cmp)(const void *, const void *))
{
	char *i = (char *)vector + izq * size;
	char *j = (char *)vector + der * size;
	char *pivote = (char *)malloc(size);
	memcpy(pivote, i, size);

	while (i < j) {
		while (i < j && cmp(j, pivote) >= 0) {
			j -= size;
		}

		if (i < j) {
			memcpy(i, j, size);
			i += size;
		}

		while (i < j && cmp(i, pivote) <= 0) {
			i += size;
		}

		if (i < j) {
			memcpy(j, i, size);
			j -= size;
		}
	}

	memcpy(i, pivote, size);
	free(pivote);
	return (i - (char *)vector) / size;
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

	return 0;
}
