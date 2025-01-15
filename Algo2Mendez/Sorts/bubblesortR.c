#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void intercambio(void *vector, int ml, int i, size_t size,
		 int (*cmp)(const void *, const void *))
{
	if (i == ml - 1)
		return;

	byte *a = (byte *)vector + i * size;
	byte *b = (byte *)vector + (i + 1) * size;

	if (cmp(a, b) > 0) {
		for (size_t j = 0; j < size; j++) {
			byte tmp = a[j];
			a[j] = b[j];
			b[j] = tmp;
		}
	}

	intercambio(vector, ml, i + 1, size, cmp);
}

void bubblesort_r(void *vector, int ml, size_t size,
		  int (*cmp)(const void *, const void *))
{
	if (ml == 1)
		return;

	intercambio(vector, ml, 0, size, cmp);
	bubblesort_r(vector, ml - 1, size, cmp);
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

	bubblesort_r(vector, ml, sizeof(int), cmp_int);

	printf("\nVector ordenado: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	return 0;
}
