#include <stdio.h>
#include <stdlib.h>

void insertionsort(int *vector, size_t ml)
{
	for (size_t i = 1; i < ml; i++) {
		int key = vector[i];
		int j = i - 1;

		while (j >= 0 && vector[j] > key) {
			vector[j + 1] = vector[j];
			j--;
		}

		vector[j + 1] = key;
	}
}

int main()
{
	int vector[] = { 64, 34, 25, 12, 22, 11, 90 };
	size_t ml = sizeof(vector) / sizeof(vector[0]);

	printf("Vector original: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}

	insertionsort(vector, ml);

	printf("\nVector ordenado: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	return 0;
}