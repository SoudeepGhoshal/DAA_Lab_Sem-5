/* Define a struct person as follows:
struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};
Write a menu driven program to read the data of ‘n’ students from a file and store them in a dynamically allocated array of struct person. Implement the min-heap or max-heap and its operations based on the menu options.
Sample Input/Output:
MAIN MENU (HEAP)
1. Read Data
2. Create a Min-heap based on the age
3. Create a Max-heap based on the weight
4. Display weight of the youngest person
5. Insert a new person into the Min-heap
6. Delete the oldest person
7. Exit
Enter option: 1
Id Name           Age Height Weight(pound)
0  Adarsh Hota    39  77     231
1  Levi Maier     56  77     129
2  Priya Kumari   63  78     240
3  Dorothy Helton 47  72     229
4  Florence Smith 24  75     171
5  Erica Anyan    38  73     102
6  Norma Webster  23  75     145
Enter option: 4
Weight of youngest student: 65.77 kg
Note#: Other menu choices are similarly verified. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

struct heap
{
    struct person *array;
    int size;
    int capacity;
    int (*compare)(struct person *, struct person *);
};

struct heap *create_heap(int capacity, int (*compare)(struct person *, struct person *));
void read_data(struct heap *h, const char *filename);
void print_data(struct heap *h);
void heapify(struct heap *h, int i);
void build_heap(struct heap *h);
void insert_person(struct heap *h, struct person p);
void display_weight_youngest(struct heap *h);
int compare_age_min(struct person *a, struct person *b);
int compare_weight_max(struct person *a, struct person *b);
void free_heap(struct heap *h);
struct person delete_oldest_person(struct heap *h);

void heapify(struct heap *h, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->compare(&h->array[left], &h->array[smallest]) < 0)
        smallest = left;

    if (right < h->size && h->compare(&h->array[right], &h->array[smallest]) < 0)
        smallest = right;

    if (smallest != i)
    {
        struct person temp = h->array[i];
        h->array[i] = h->array[smallest];
        h->array[smallest] = temp;
        heapify(h, smallest);
    }
}

struct heap *create_heap(int capacity, int (*compare)(struct person *, struct person *))
{
    struct heap *h = (struct heap *)malloc(sizeof(struct heap));
    h->array = (struct person *)malloc(capacity * sizeof(struct person));
    h->capacity = capacity;
    h->size = 0;
    h->compare = compare;
    return h;
}

void read_data(struct heap *h, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    h->size = 0;
    char name_buffer[MAX_NAME];

    while (fscanf(file, "%d %49s %d %d %d", &h->array[h->size].id, name_buffer,
                  &h->array[h->size].age, &h->array[h->size].height, &h->array[h->size].weight) == 5)
    {
        h->array[h->size].name = strdup(name_buffer);
        if (h->array[h->size].name == NULL)
        {
            printf("Memory allocation error for name.\n");
            fclose(file);
            return;
        }

        h->size++;
        if (h->size >= h->capacity)
        {
            h->capacity *= 2;
            h->array = (struct person *)realloc(h->array, h->capacity * sizeof(struct person));
            if (h->array == NULL)
            {
                printf("Memory reallocation error.\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    build_heap(h);
    printf("Data read successfully. Total records: %d\n", h->size);
}

void print_data(struct heap *h)
{
    printf("ID\tName\t\tAge\tHeight(cm)\tWeight(kg)\n");
    for (int i = 0; i < h->size; i++)
    {
        printf("%d\t%10s\t%d\t%d\t\t%d\n", h->array[i].id, h->array[i].name, h->array[i].age,
               h->array[i].height, h->array[i].weight);
    }
}

void build_heap(struct heap *h)
{
    for (int i = h->size / 2 - 1; i >= 0; i--)
        heapify(h, i);
}

void insert_person(struct heap *h, struct person p)
{
    if (h->size >= h->capacity)
    {
        h->capacity *= 2;
        h->array = (struct person *)realloc(h->array, h->capacity * sizeof(struct person));
        if (h->array == NULL)
        {
            printf("Memory reallocation failed\n");
            return;
        }
    }

    int i = h->size;
    h->array[i] = p;
    h->size++;

    while (i > 0 && h->compare(&h->array[i], &h->array[(i - 1) / 2]) < 0)
    {
        struct person temp = h->array[i];
        h->array[i] = h->array[(i - 1) / 2];
        h->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

struct person delete_oldest_person(struct heap *h)
{
    if (h->size <= 0)
    {
        printf("Heap is empty\n");
        struct person dummy = {-1, "", -1, -1, -1};
        return dummy;
    }

    int oldest_index = 0;
    for (int i = 1; i < h->size; i++)
    {
        if (h->array[i].age > h->array[oldest_index].age)
        {
            oldest_index = i;
        }
    }

    struct person oldest = h->array[oldest_index];

    h->array[oldest_index] = h->array[h->size - 1];
    h->size--;

    heapify(h, oldest_index);

    return oldest;
}

void display_weight_youngest(struct heap *h)
{
    if (h->size > 0)
    {
        printf("Weight of youngest person: %d kg\n", h->array[0].weight);
    }
    else
    {
        printf("Heap is empty\n");
    }
}

int compare_age_min(struct person *a, struct person *b)
{
    return a->age - b->age;
}

int compare_weight_max(struct person *a, struct person *b)
{
    return b->weight - a->weight;
}

void free_heap(struct heap *h)
{
    for (int i = 0; i < h->size; i++)
    {
        free(h->array[i].name);
    }
    free(h->array);
    free(h);
}

int main()
{
    struct heap *h = NULL;
    int choice;
    char name_buffer[MAX_NAME];

    printf("MAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Exit\n");

    do
    {
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (h != NULL)
            {
                free_heap(h);
            }
            h = create_heap(100, compare_age_min);
            read_data(h, "people.dat");
            print_data(h);
            break;
        case 2:
            if (h != NULL)
            {
                h->compare = compare_age_min;
                build_heap(h);
                printf("Min-heap based on age created.\n");
            }
            else
            {
                printf("Please read data first.\n");
            }
            break;
        case 3:
            if (h != NULL)
            {
                h->compare = compare_weight_max;
                build_heap(h);
                printf("Max-heap based on weight created.\n");
            }
            else
            {
                printf("Please read data first.\n");
            }
            break;
        case 4:
            if (h != NULL && h->compare == compare_age_min)
            {
                display_weight_youngest(h);
            }
            else
            {
                printf("Please create a min-heap based on age first.\n");
            }
            break;
        case 5:
            if (h != NULL && h->compare == compare_age_min)
            {
                struct person p;
                printf("Enter id, name, age, height, weight: ");
                scanf("%d %s %d %d %d", &p.id, name_buffer, &p.age, &p.height, &p.weight);
                p.name = strdup(name_buffer);
                insert_person(h, p);
                printf("Person inserted into the min-heap.\n");
            }
            else
            {
                printf("Please create a min-heap based on age first.\n");
            }
            break;
        case 6:
            if (h != NULL && h->compare == compare_age_min)
            {
                struct person p = delete_oldest_person(h);
                if (p.id != -1)
                {
                    printf("Oldest person removed: %s (Age: %d)\n", p.name, p.age);
                    free(p.name);
                }
            }
            else
            {
                printf("Please create a min-heap based on age first.\n");
            }
            break;
        case 7:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 7);

    if (h != NULL)
    {
        free_heap(h);
    }

    return 0;
}