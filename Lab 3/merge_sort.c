/* Write a menu driven program to sort list of array elements using Merge Sort technique and calculate the execution time only to sort the elements. Count the number of comparisons. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void mergeAsc(int arr[], int p, int q, int r, int *comp)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2)
    {
        (*comp)++;
        if (L[i] <= R[j])
        {
            arr[k++] = L[i];
            i++;
        }
        else
        {
            arr[k++] = R[j];
            j++;
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i];
        i++;
    }
    while (j < n2)
    {
        arr[k++] = R[j];
        j++;
    }
}

void mergeSortAsc(int a[], int p, int r, int *comp)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSortAsc(a, p, q, comp);
        mergeSortAsc(a, q + 1, r, comp);
        mergeAsc(a, p, q, r, comp);
    }
}

void mergeDesc(int arr[], int p, int q, int r, int *comp)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2)
    {
        (*comp)++;
        if (L[i] >= R[j])
        {
            arr[k++] = L[i];
            i++;
        }
        else
        {
            arr[k++] = R[j];
            j++;
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i];
        i++;
    }
    while (j < n2)
    {
        arr[k++] = R[j];
        j++;
    }
}

void mergeSortDesc(int a[], int p, int r, int *comp)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSortDesc(a, p, q, comp);
        mergeSortDesc(a, q + 1, r, comp);
        mergeDesc(a, p, q, r, comp);
    }
}

int main()
{
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    clock_t start = clock(), end = clock();
    double cpu_time_used;

    int ch = 0;
    printf("MAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Order\n");
    printf("2. Descending Order\n");
    printf("3. ERROR (EXIT)\n");
    printf("Enter choice: ");
    scanf("%d", &ch);

    start = clock();

    if (ch == 3)
    {
        printf("Exiting program.\n");
        exit(EXIT_SUCCESS);
    }

    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    int num[n];
    int comp = 0;

    FILE *inputFile = fopen("inRand.dat", "r");
    if (inputFile == NULL)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    FILE *outputFile = fopen("outMergeSort.dat", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file.");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++)
    {
        if (fscanf(inputFile, "%d", &num[i]) != 1)
            break;
    }

    printf("Before Sorting:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", num[i]);
    }
    printf("\n");

    switch (ch)
    {
    case 1:
        mergeSortAsc(num, 0, n - 1, &comp);
        break;

    case 2:
        mergeSortDesc(num, 0, n - 1, &comp);
        break;

    default:
        printf("Wrong Choice.");
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d\n", num[i]);
    }

    end = clock();

    fclose(inputFile);
    fclose(outputFile);

    printf("After Sorting:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", num[i]);
    }
    printf("\n");

    printf("Number of comparisons: %d\n", comp);

    cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC) * pow(10, 9);
    printf("Execution time: %lf ns", cpu_time_used);

    return 0;
}