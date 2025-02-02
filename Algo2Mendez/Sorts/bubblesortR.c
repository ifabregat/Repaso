#include <stdio.h>
#include <stdlib.h>

void bubblesort_r(int *vector, int ml)
{
	if (ml == 1)
		return;

	for (int i = 0; i < ml - 1; i++) {
		if (vector[i] > vector[i + 1]) {
			int temp = vector[i];
			vector[i] = vector[i + 1];
			vector[i + 1] = temp;
		}
	}

	bubblesort_r(vector, ml - 1);
}

int main()
{
	int vector[] = { 64, 34, 25, 12, 22, 11, 90 };
	size_t ml = sizeof(vector) / sizeof(vector[0]);

	printf("Vector original: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}

	bubblesort_r(vector, ml);

	printf("\nVector ordenado: ");
	for (int i = 0; i < ml; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	return 0;
}
