// Write a program in C to find GCD of two numbers using recursion. Read all pair of numbers from a file and store the result in a separate file.

#include <stdio.h>
#include <stdlib.h>

void find(FILE *outputFile, int n1, int n2)
{
    if (n2 == 0)
        fprintf(outputFile, "%d", n1);
    else
        find(outputFile, n2, n1 % n2);
}

void displayContent(FILE *inputFile, FILE *outputFile, int n)
{
    char c1[100], c2[100], c3[100];
    for (int i = 0; i < n; i++)
    {
        if (fscanf(inputFile, "%s", c1) != 1 || fscanf(inputFile, "%s", c2) != 1 || fscanf(outputFile, "%s", c3) != 1)
        {
            break;
        }
        printf("GCD of %s and %s is %s\n", c1, c2, c3);
    }
}

void findGcd(const char *inputFileName, const char *outputFileName, int n)
{
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputFileName, "w+");
    if (outputFile == NULL)
    {
        perror("Error opening output file.");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    int num1, num2;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(inputFile, "%d", &num1) != 1 || fscanf(inputFile, "%d", &num2) != 1)
            break;
        find(outputFile, num1, num2);
        fprintf(outputFile, "\n");
    }

    printf("Conversions:\n");
    rewind(inputFile);
    rewind(outputFile);
    displayContent(inputFile, outputFile, n);

    fclose(inputFile);
    fclose(outputFile);
}

int main()
{
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    char input[15];
    char output[15];
    int n;
    printf("Enter number of pairs of numbers to process: ");
    scanf("%d", &n);
    printf("Enter name of input file: ");
    scanf("%s", input);
    printf("Enter name of output file: ");
    scanf("%s", output);

    findGcd(input, output, n);

    return 0;
}