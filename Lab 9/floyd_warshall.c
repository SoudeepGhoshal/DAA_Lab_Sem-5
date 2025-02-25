/* Given a directed weighted graph G (V, E) where weight indicates distance. Vertices will be numbered consecutively from 1 to n (user input), and edges will have varying distances or lengths.
● Determine the length of the shortest path between every pair of vertices using Floyd-Warshall’s algorithm.
● Display the intermediate vertices on the shortest-path from the given pair of vertices (u,v). */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 99999
#define MAX 100

void floydWarshall(int dist[][MAX], int next[][MAX], int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printPath(int next[][MAX], int u, int v) {
    if (next[u][v] == -1) {
        printf("No path");
        return;
    }
    printf("%d", u + 1);
    while (u != v) {
        u = next[u][v];
        printf(" --> %d", u + 1);
    }
    printf("\n");
}

int main() {
    int n;
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error: File not found.\n");
        return 1;
    }

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int dist[MAX][MAX], next[MAX][MAX];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &dist[i][j]);
            if (i != j && dist[i][j] == 0)
                dist[i][j] = INF;
            if (dist[i][j] != INF)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }
    fclose(file);

    floydWarshall(dist, next, n);

    printf("\nShortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    int u, v;
    printf("Enter the source and destination vertices: ");
    scanf("%d %d", &u, &v);
    u--; v--;

    printf("Shortest Path from vertex %d to vertex %d: ", u + 1, v + 1);
    printPath(next, u, v);
    printf("Path weight: %d\n", dist[u][v]);

    return 0;
}