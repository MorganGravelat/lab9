#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Node structure for chaining
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// Fill out this structure
struct HashType
{
    struct Node** table;  // Array of pointers to Node
    int size;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    int prime = 31;  // You gave me 31 inputs which is a good prime number for hash
    //returns the hash value using the remainder of the prime * id number divided by tableSize
    return (prime * x) % tableSize; 
    
}

// I made this to make the hash table work with the prime number you gave of inputs
struct HashType* initHashTable(int size)
{
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType));
    hashTable->size = size;
    hashTable->table = (struct Node**)malloc(sizeof(struct Node*) * size);
    for (int i = 0; i < size; i++)
        hashTable->table[i] = NULL;
    return hashTable;
}


// Insert record into hash table using separate chaining
void insert(struct HashType* hashTable, struct RecordType record)
{
    int ind = hash(record.id, hashTable->size);
    struct Node* addNode = (struct Node*)malloc(sizeof(struct Node));
    addNode->data = record;
    addNode->next = hashTable->table[ind];
    hashTable->table[ind] = addNode;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray)
{
    for (int i = 0; i < pHashArray->size; ++i)
    {
        //creating a temporary node 
        struct Node* temp = pHashArray->table[i]; 
        //
        if (temp != NULL)
        {
            printf("index %d -> ", i);
            while (temp != NULL)
            {
                //Given format in the comments above plus based off in lab output shown
                printf("%d, %c, %d", temp->data.id, temp->data.name, temp->data.order);
                if (temp->next != NULL)
                    printf(" -> ");
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    //23 again selected based off input and it is common to use for hash.
    struct HashType* hashTable = initHashTable(23); // Size of hash table using our init function
    //loop that inserts the proper records into the hash table from the input
    for (int i = 0; i < recordSz; ++i)
    {
        insert(hashTable, pRecords[i]);
    }

    //Call the display function I filled out
    displayRecordsInHash(hashTable);

    //int main returns 0 at the end of it all
    return 0;
}
