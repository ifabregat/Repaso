#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void insertionsort(void *vector, size_t ml, size_t size,
		   int (*cmp)(const void *, const void *))
{
	byte *v = (byte *)vector;

	for (size_t i = 1; i < ml; i++) {
		size_t j = i;
		while (j > 0 && cmp(v + j * size, v + (j - 1) * size) < 0) {
			for (size_t k = 0; k < size; k++) {
				byte temp = v[j * size + k];
				v[j * size + k] = v[(j - 1) * size + k];
				v[(j - 1) * size + k] = temp;
			}
			j--;
		}
	}
}

int cmp_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int main()
{
	int vector[] = { 64, 34, 25, 12, 22, 11, 90 };
	size_t ml = sizeof(vector) / sizeof(vector[0]);

	printf("Vector original: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}

	insertionsort(vector, ml, sizeof(int), cmp_int);

	printf("\nVector ordenado: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	return 0;
}