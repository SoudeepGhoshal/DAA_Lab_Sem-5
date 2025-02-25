/* Given an undirected weighted connected graph G(V, E) and starring vertex ‘s’. Maintain a Min-Priority Queue ‘Q’ from the vertex set V and apply Prim’s algorithm to
● Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’.
● Display total cost of the minimum spanning tree T. */

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define INF INT_MAX

int minKey(int key[], bool mstSet[], int n) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int n, int **graph) {
    printf("Cost Adjacency Matrix of the Minimum Spanning Tree:\n");
    int totalCost = 0;
    int **mstMatrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        mstMatrix[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            mstMatrix[i][j] = 0;
    }

    for (int i = 1; i < n; i++) {
        int u = parent[i];
        int v = i;
        mstMatrix[u][v] = mstMatrix[v][u] = graph[u][v];
        totalCost += graph[u][v];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mstMatrix[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", mstMatrix[i][j]);
        }
        printf("\n");
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalCost);

    for (int i = 0; i < n; i++)
        free(mstMatrix[i]);
    free(mstMatrix);
}

void primMST(int **graph, int n) {
    int parent[n];
    int key[n];
    bool mstSet[n];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printMST(parent, n, graph);
}

int main() {
    int n;
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
    }

    FILE *file = fopen("input.dat", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = INF;
        }
    }
    fclose(file);

    primMST(graph, n);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
