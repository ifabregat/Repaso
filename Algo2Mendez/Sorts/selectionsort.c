#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void selectionsort(void *vector, size_t ml, size_t size,
           int (*cmp)(const void *, const void *))
{
    byte *v = (byte *)vector;

    for (size_t i = 0; i < ml - 1; i++) {
        size_t min = i;

        for (size_t j = i + 1; j < ml; j++) {
            if (cmp(v + j * size, v + min * size) < 0) {
                min = j;
            }
        }

        if (min != i) {
            for (size_t j = 0; j < size; j++) {
                byte temp = v[i * size + j];
                v[i * size + j] = v[min * size + j];
                v[min * size + j] = temp;
            }
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

    selectionsort(vector, ml, sizeof(int), cmp_int);

    printf("\nVector ordenado: ");
    for (int i = 0; i < ml; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    return 0;
}