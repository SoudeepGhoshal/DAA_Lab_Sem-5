// Write a program in C to convert the first ‘n’ decimal numbers of a disc file to binary using recursion. Store the binary value in a separate disc file.

#include <stdio.h>
#include <stdlib.h>

void convert(FILE *outputFile, int n)
{
    if (n > 1)
    {
        convert(outputFile, n / 2);
    }
    fprintf(outputFile, "%d", n % 2);
}

void displayContent(FILE *inputFile, FILE *outputFile, int n)
{
    char c1[100], c2[100];
    for (int i = 0; i < n; i++)
    {
        if (fscanf(inputFile, "%s", c1) != 1 || fscanf(outputFile, "%s", c2) != 1)
        {
            break;
        }
        printf("Binary equivalent of %s is %s\n", c1, c2);
    }
}

void decToBin(const char *inputFileName, const char *outputFileName, int n)
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

    int num;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(inputFile, "%d", &num) != 1)
            break;
        convert(outputFile, num);
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
    printf("Enter number of Decimals to convert: ");
    scanf("%d", &n);
    printf("Enter name of input file: ");
    scanf("%s", input);
    printf("Enter name of output file: ");
    scanf("%s", output);

    decToBin(input, output, n);

    return 0;
}