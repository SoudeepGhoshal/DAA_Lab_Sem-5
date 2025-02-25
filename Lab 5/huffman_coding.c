/* Huffman coding assigns variable length code words to fixed length input characters based on their frequencies or probabilities of occurrence. Given a set of characters along with their frequency of occurrences, write a c program to construct a Huffman tree.
Note#
● Declare a structure SYMBOL having members alphabet and frequency. Create a Min-Priority Queue, keyed on frequency attributes.
● Create an array of structures where size=number of alphabets. */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char alphabet;
    int frequency;
    struct Node *left, *right;
} Node;

typedef struct
{
    char alphabet;
    int frequency;
} SYMBOL;

typedef struct
{
    int size;
    int capacity;
    Node **array;
} MinHeap;

Node *createNode(char alphabet, int frequency)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->alphabet = alphabet;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void swap(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node **)malloc(capacity * sizeof(Node *));
    return minHeap;
}

void heapify(MinHeap *minHeap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
    {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
    {
        smallest = right;
    }
    if (smallest != index)
    {
        swap(&minHeap->array[smallest], &minHeap->array[index]);
        heapify(minHeap, smallest);
    }
}

Node *extractMin(MinHeap *minHeap)
{
    Node *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    heapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap *minHeap, Node *node)
{
    minHeap->size++;
    int i = minHeap->size - 1;
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

MinHeap *buildMinHeap(SYMBOL symbols[], int size)
{
    MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
    {
        minHeap->array[i] = createNode(symbols[i].alphabet, symbols[i].frequency);
    }
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
    {
        heapify(minHeap, i);
    }
    return minHeap;
}

Node *buildHuffmanTree(SYMBOL symbols[], int size)
{
    Node *left, *right, *top;
    MinHeap *minHeap = buildMinHeap(symbols, size);

    while (minHeap->size != 1)
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void inorderTraversal(Node *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    if (root->alphabet != '$')
    {
        printf("%c ", root->alphabet);
    }
    inorderTraversal(root->right);
}

int main()
{
    printf("Developed by Soudeep Ghoshal | 2205421\n");

    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    SYMBOL symbols[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &symbols[i].alphabet);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &symbols[i].frequency);
    }

    Node *root = buildHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}