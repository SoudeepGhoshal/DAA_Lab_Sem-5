/* Given a directed graph G (V, E) and a starting vertex ‘s’.
● Determine the lengths of the shortest paths from the starting vertex ‘s’ to all other vertices in the graph G using Dijkstra’s Algorithm.
● Display the shortest path from the given source ‘s’ to all other vertices. */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF 99999

int minDistance(int dist[], int visited[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("->%d", j + 1);
}

void dijkstra(int graph[MAX][MAX], int n, int src) {
    int dist[MAX];
    int visited[MAX] = {0};
    int parent[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t", src + 1, i + 1);
        if (dist[i] == INF)
            printf("INF\t-\n");
        else {
            printf("%d\t%d", dist[i], src + 1);
            printPath(parent, i);
            printf("\n");
        }
    }
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

    int graph[MAX][MAX];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
            if (i != j && graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }
    fclose(file);

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);
    src--;

    dijkstra(graph, n, src);

    return 0;
}