/* Write a program to find the maximum profit nearest to but not exceeding the given knapsack capacity using the Fractional Knapsack algorithm.
Note: Declare a structure ITEM having data members item_id, item_profit, item_weight and profit_weight_ratio. Apply heap sort technique to sort the items in non-increasing order, according to their profit/weight. */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int item_id;
    int item_profit;
    int item_weight;
    float profit_weight_ratio;
} ITEM;

void heapify(ITEM *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        ITEM temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heap_sort(ITEM *arr, int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        ITEM temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

float fractional_knapsack(ITEM *items, int n, int knapsack_capacity) {
    float total_profit = 0.0;
    int remaining_capacity = knapsack_capacity;

    heap_sort(items, n);

    printf("\nSorted items (in descending order of profit/weight ratio):\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("Item %d: profit = %d, weight = %d, ratio = %.2f\n",
               items[i].item_id, items[i].item_profit, items[i].item_weight, items[i].profit_weight_ratio);
    }

    for (int i = n - 1; i >= 0; i--) {
        if (items[i].item_weight <= remaining_capacity) {
            total_profit += items[i].item_profit;
            remaining_capacity -= items[i].item_weight;
            printf("Adding item %d completely. Profit: %.2f, Remaining capacity: %d\n",
                   items[i].item_id, total_profit, remaining_capacity);
        } else {
            float fraction = (float)remaining_capacity / items[i].item_weight;
            total_profit += fraction * items[i].item_profit;
            printf("Adding fraction %.2f of item %d. Profit: %.2f, Remaining capacity: 0\n",
                   fraction, items[i].item_id, total_profit);
            remaining_capacity = 0;
            break;
        }
    }

    return total_profit;
}

int main() {
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    int n, knapsack_capacity;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the knapsack capacity: ");
    scanf("%d", &knapsack_capacity);

    ITEM *items = (ITEM *)malloc(n * sizeof(ITEM));

    for (int i = 0; i < n; i++) {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item %d: ", items[i].item_id);
        scanf("%d %d", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = (float)items[i].item_profit / items[i].item_weight;
    }

    float max_profit = fractional_knapsack(items, n, knapsack_capacity);

    printf("Maximum profit: %.2f\n", max_profit);

    free(items);

    return 0;
}