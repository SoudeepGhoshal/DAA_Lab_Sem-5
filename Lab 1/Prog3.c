// Write a program to read ‘n’ integers from a disc file that must contain some duplicate values and store them into an array. Perform the following operations on the array.
// a) Find out the total number of duplicate elements.
// b) Find out the most repeating element in the array.

#include <stdio.h>
#include <stdlib.h>

#define NUMS 30

int main()
{
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    FILE *file = fopen("input0.txt", "r");
    if (file == NULL)
    {
        perror("File does not exist");
        return EXIT_FAILURE;
    }

    int num[NUMS];
    for (int i = 0; i < NUMS; i++)
    {
        if (fscanf(file, "%d", &num[i]) != 1)
        {
            perror("Error reading integer from file");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);

    int freq[NUMS][2];
    int k = 0;
    int flag = 0;
    for (int i = 0; i < NUMS; i++)
    {
        flag = 0;
        for (int j = 0; j < k; j++)
        {
            if (freq[j][0] == num[i])
            {
                freq[j][1]++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            freq[k][0] = num[i];
            freq[k][1] = 1;
            k++;
        }
    }

    int dupli_count = 0;
    int max_dupli_index = 0;
    for (int i = 0; i < k; i++)
    {
        if (freq[i][1] > 1)
        {
            dupli_count++;
            if (freq[i][1] > freq[max_dupli_index][1])
                max_dupli_index = i;
        }
    }

    printf("The content of the array: ");
    for (int i = 0; i < NUMS; i++)
    {
        printf("%d  ", num[i]);
    }
    printf("\nTotal number of duplicate values: %d", dupli_count);
    printf("\nMost repeating element: %d", freq[max_dupli_index][0]);

    return 0;
}