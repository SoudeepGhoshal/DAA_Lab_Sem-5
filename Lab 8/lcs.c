/* Write a program to find out the Longest Common Subsequence of two given strings. Calculate length of the LCS. */

#include <stdio.h>
#include <string.h>

void print_LCS(int m, int n, int B[m+1][n+1], char *X, int i, int j);

int LCS_Length(char *X, char *Y, int m, int n) {
    int B[m+1][n+1];
    int C[m+1][n+1];

    for (int i = 0; i <= m; i++)
        C[i][0] = 0;
    for (int j = 0; j <= n; j++)
        C[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                C[i][j] = C[i-1][j-1] + 1;
                B[i][j] = 1;
            } else if (C[i-1][j] >= C[i][j-1]) {
                C[i][j] = C[i-1][j];
                B[i][j] = 2;
            } else {
                C[i][j] = C[i][j-1];
                B[i][j] = 3;
            }
        }
    }

    // Print the LCS
    printf("LCS: ");
    print_LCS(m, n, B, X, m, n);
    printf("\n");

    return C[m][n];
}

void print_LCS(int m, int n, int B[m+1][n+1], char *X, int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (B[i][j] == 1) {
        print_LCS(m, n, B, X, i-1, j-1);
        printf("%c", X[i-1]);
    } else if (B[i][j] == 2) {
        print_LCS(m, n, B, X, i-1, j);
    } else {
        print_LCS(m, n, B, X, i, j-1);
    }
}

int main() {
    char X[50], Y[50];
    printf("Enter first String: ");
    scanf("%s", X);
    printf("Enter second String: ");
    scanf("%s", Y);
    int m = strlen(X);
    int n = strlen(Y);

    printf("Length of LCS: %d\n", LCS_Length(X, Y, m, n));
    return 0;
}