#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    char *key;
    struct node *next;
} node;


typedef struct {
    node **buckets;
    int size;
} HashTable;


HashTable *createHashTable(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = malloc(sizeof(node*) * size);
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}


unsigned int hash(char *key, int tableSize) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % tableSize;
}


void insert(HashTable *table, char *key) {
    unsigned int index = hash(key, table->size);
    node *newNode = malloc(sizeof(node));
    newNode->key = strdup(key);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}


void displayHashTable(HashTable *table) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < table->size; i++) {
        node *current = table->buckets[i];
        printf("%d: ", i);
        while (current != NULL) {
            printf("%s -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}


int main() {
    HashTable *myTable = createHashTable(10);
    insert(myTable, "apple");
    insert(myTable, "banana");
    insert(myTable, "cherry");
    displayHashTable(myTable);
    // Free memory and exit
    return 0;
}
