/* Write a program to implement the matrix chain multiplication problem using M-table & S-table to find optimal parenthesization of a matrix-chain product. Print the number of scalar multiplications required for the given input. */

#include <stdio.h>
#include <limits.h>

int n = 0;

void print_optimal_parens(int s[n][n], int i, int j) {
    if (i == j)
        printf("A%d ", i);
    else {
        printf("( ");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(") ");
    }
}

int matrix_chain_order(int *p, int n) {
    int m[n+1][n+1];
    int s[n][n];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            m[i][j] = 0;
            if (i <= n && j <= n)
                s[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("M-table:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }

    printf("S-table:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            printf("%d\t", s[i][j]);
        }
        printf("\n");
    }

    printf("Optimal parenthesization: ");
    print_optimal_parens(s, 1, n);
    printf("\n");

    return m[1][n - 1];
}

int main() {
    printf("Enter size of array: ");
    scanf("%d", &n);
    int p[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    printf("Minimum number of multiplications is %d\n", matrix_chain_order(p, n));
    return 0;
}