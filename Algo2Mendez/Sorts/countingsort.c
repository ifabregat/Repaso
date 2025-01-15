#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

void countingSort(void *array, size_t n, size_t size, int (*key)(const void *))
{
	if (n == 0)
		return;

	byte *vector = array;

	int min = key(vector);
	int max = key(vector);

	for (size_t i = 1; i < n; i++) {
		int val = key(vector + i * size);
		if (val > max)
			max = val;
		if (val < min)
			min = val;
	}

	int range = max - min + 1;

	int *count = (int *)calloc(range, sizeof(int));
	byte *output = malloc(n * size);

	if (!count || !output) {
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < n; i++) {
		int val = key(vector + i * size);
		count[val - min]++;
	}

	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	for (size_t i = n; i > 0; i--) {
		int val = key(vector + (i - 1) * size);
		int pos = count[val - min] - 1;
		memcpy(output + pos * size, vector + (i - 1) * size, size);
		count[val - min]--;
	}

	memcpy(vector, output, n * size);

	free(count);
	free(output);
}

int keyInt(const void *element)
{
	return *(int *)element;
}

int main()
{
	int vector[] = { 23, 1, 12, 9, 3, 32, 5, 17 };
	size_t n = sizeof(vector) / sizeof(vector[0]);

	printf("Vector original: ");
	for (size_t i = 0; i < n; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	countingSort(vector, n, sizeof(int), keyInt);

	printf("Vector ordenado: ");
	for (size_t i = 0; i < n; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	return 0;
}
