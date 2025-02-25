/* Write a menu driven program to sort a list of elements in ascending order using Quick Sort technique. Each choice for the input data has its own disc file. A separate output file can be used for sorted elements. After sorting display the content of the output file along with number of comparisons. Based on the partitioning position for each recursive call, conclude the input scenario is either best-case partitioning or worst-case partitioning. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partitionAsc(int arr[], int low, int high, int *comp)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        (*comp)++;
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortAsc(int arr[], int low, int high, int *comp, int depth)
{
    if (low < high)
    {
        int pi = partitionAsc(arr, low, high, comp);

        quickSortAsc(arr, low, pi - 1, comp, depth + 1);
        quickSortAsc(arr, pi + 1, high, comp, depth + 1);
    }
}

int partitionDesc(int arr[], int low, int high, int *comp)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        (*comp)++;
        if (arr[j] > pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortDesc(int arr[], int low, int high, int *comp, int depth)
{
    if (low < high)
    {
        int pi = partitionDesc(arr, low, high, comp);

        quickSortDesc(arr, low, pi - 1, comp, depth + 1);
        quickSortDesc(arr, pi + 1, high, comp, depth + 1);
    }
}

int main()
{
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    clock_t start, end;
    double cpu_time_used;

    int ch = 0;
    printf("MAIN MENU (QUICK SORT)\n");
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
    FILE *outputFile = fopen("outQuickSort.dat", "w");
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
        quickSortAsc(num, 0, n - 1, &comp, 0);
        break;

    case 2:
        quickSortDesc(num, 0, n - 1, &comp, 0);
        break;

    default:
        printf("Wrong Choice.");
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d\n", num[i]);
    }

    fclose(inputFile);
    fclose(outputFile);

    end = clock();

    printf("After Sorting:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", num[i]);
    }
    printf("\n");

    printf("Number of comparisons: %d\n", comp);

    cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC) * pow(10, 9);
    printf("Execution time: %lf", cpu_time_used);

    return 0;
}