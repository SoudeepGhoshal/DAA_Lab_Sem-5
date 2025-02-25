// Read 10 intgers from a file and display on the terminal

#include <stdio.h>
#include <stdlib.h>

#define NUMS 10

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

    for (int i = 0; i < NUMS; i++)
    {
        printf("%d  ", num[i]);
    }

    return 0;
}