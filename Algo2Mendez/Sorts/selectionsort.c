#include <stdio.h>
#include <stdlib.h>

void selectionsort(int *vector, size_t ml)
{
	for (size_t i = 0; i < ml; i++) {
		size_t min = i;
		for (size_t j = i + 1; j < ml; j++) {
			if (vector[j] < vector[min]) {
				min = j;
			}
		}
		if (min != i) {
			int temp = vector[i];
			vector[i] = vector[min];
			vector[min] = temp;
		}
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

	selectionsort(vector, ml);

	printf("\nVector ordenado: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	return 0;
}