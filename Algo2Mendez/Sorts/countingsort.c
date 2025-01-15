#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countingSort(int *vector, size_t n)
{
	if (n == 0)
		return;

	int max = vector[0];
	int min = vector[0];
	for (size_t i = 1; i < n; i++) {
		if (vector[i] > max)
			max = vector[i];
		if (vector[i] < min)
			min = vector[i];
	}

	int range = max - min + 1;

	int *count = (int *)calloc(range, sizeof(int));
	int *output = (int *)malloc(n * sizeof(int));

	for (size_t i = 0; i < n; i++) {
		count[vector[i] - min]++;
	}

	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	for (size_t i = n; i > 0; i--) {
		output[count[vector[i - 1] - min] - 1] = vector[i - 1];
		count[vector[i - 1] - min]--;
	}

	memcpy(vector, output, n * sizeof(int));

	free(count);
	free(output);
}

int main()
{
	int vector[] = { 23, 1, 12, 9, 3, 32, 5, 17 };
	int n = sizeof(vector) / sizeof(vector[0]);

	printf("Vector original: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	countingSort(vector, n);

	printf("Vector ordenado: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	return 0;
}
