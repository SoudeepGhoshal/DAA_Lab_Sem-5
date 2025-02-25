// Given an array arr[] of size N, find the prefix sum of the array. A prefix sum array is another array prefixSum[] of the same size, such that the value of prefixSum[i] is arr[0] + arr[1] + arr[2] . . . arr[i].

#include <stdio.h>

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

    // Prefix Sum Array
    int prefixSum[N];
    prefixSum[0] = array[0];
    for (int i = 1; i < N; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + array[i];
    }

    printf("Prefix Sum Array:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d  ", prefixSum[i]);
    }
}