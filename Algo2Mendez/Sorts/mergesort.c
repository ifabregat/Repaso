#include <stdio.h>
#include <stdlib.h>

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
			for (size_t l = 0; l < size; ++l) {
				t[k * size + l] = v[i * size + l];
			}
			i++;
		} else {
			for (size_t l = 0; l < size; ++l) {
				t[k * size + l] = v[j * size + l];
			}
			j++;
		}
		k++;
	}

	while (i <= mitad) {
		for (size_t l = 0; l < size; ++l) {
			t[k * size + l] = v[i * size + l];
		}
		i++;
		k++;
	}

	while (j <= der) {
		for (size_t l = 0; l < size; ++l) {
			t[k * size + l] = v[j * size + l];
		}
		j++;
		k++;
	}

	for (i = izq; i <= der; i++) {
		for (size_t l = 0; l < size; ++l) {
			v[i * size + l] = t[i * size + l];
		}
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
