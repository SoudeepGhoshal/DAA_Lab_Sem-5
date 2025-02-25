// Write a program to find out the second smallest and second largest element stored in an array of n integers.

#include <stdio.h>
#include <stdlib.h>

#define NUMS 10

int main() {
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    FILE *file = fopen("input0.txt", "r");
    if (file == NULL) {
        perror("File does not exist");
        return EXIT_FAILURE;
    }

    int num[NUMS];
    for (int i = 0; i < NUMS; i++) {
        if (fscanf(file, "%d", &num[i]) != 1) {
            perror("Error reading integer from file");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);

    for (int i = 0; i < NUMS; i++) {
        int smallest = i;
        for (int j = i + 1; j < NUMS; j++) {
            if (num[j] < num[smallest])
                smallest = j;
        }
        if (num[smallest] == num[i])
            continue;
        num[smallest] += num[i];
        num[i] = num[smallest] - num[i];
        num[smallest] -= num[i]; 
    }

    for (int i = 0; i < NUMS; i++) {
        printf("%d  ", num[i]);
    }

    printf("\nSecond smallest = %d\n", num[1]);
    printf("Second largest = %d\n", num[NUMS - 2]);

    return 0;
}