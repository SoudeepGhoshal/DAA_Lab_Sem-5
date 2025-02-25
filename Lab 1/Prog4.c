// Write a function to ROTATE_RIGHT(p1, p2) right an array for first p2 elements by 1 position using EXCHANGE(p, q) function that swaps/exchanges the numbers p & q. Parameter p1 be the starting address of the array and p2 be the number of elements to be rotated.

#include <stdio.h>

void ROTATE_RIGHT(int *A, int rot)
{
    int temp = A[rot - 1];
    for (int i = rot - 1; i > 0; i--)
    {
        A[i] = A[i - 1];
    }
    A[0] = temp;
}

int main()
{
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    int N = 0;
    printf("Enter number of elements: ");
    scanf("%d", &N);
    int array[N];

    printf("Enter %d integers:\n", N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Enter rotation value: ");
    int rot = 0;
    scanf("%d", &rot);

    printf("Original Array:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d  ", array[i]);
    }

    ROTATE_RIGHT(array, rot);

    printf("\nRotated Array:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d  ", array[i]);
    }
}