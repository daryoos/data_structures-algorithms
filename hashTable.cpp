
#include <iostream>
#include "Profiler.h"

#define n 10007
#define a 1
#define b 1

typedef struct {
    int key;
    char name[30];
}Entry;

int hashFunction(int key, int i);
void insertKey(int key, Entry* table, int (*hashFunction)(int key, int i));
bool searchKey(int key, Entry* table, int (*hashFunction)(int key, int i), int& opCount, int& opCount_max, bool countf);
void deleteKey(int key, Entry* table, int (*hashFunction)(int key, int i));

void searchTable(Entry* table, double alpha, int (*hashFunction)(int key, int i), int *opCount_found, int *opCount_notFound, int& opCount_maxF, int& opCount_maxNF, int& foundCount, int& notFoundCount);
void deleteCase(Entry* table, double alpha, int (*hashFunction)(int key, int i), int *opCount_found, int *opCount_notFound, int& opCount_maxF, int& opCount_maxNF, int& foundCount, int& notFoundCount);

void freeTable(Entry* table);

void demo(int (*hashFunction)(int key, int i));

void printTable(Entry* table);

int main()
{
    demo(hashFunction);
}

void demo(int (*hashFunction)(int key, int i)) {

    double alpha[] = { 0.8, 0.85, 0.9, 0.95, 0.99 };

    Entry table[n];
    freeTable(table);

    //printTable(table);

    printf("Factor de | Efort mediu | Efort maxim | Efort mediu | Efort maxim\n");
    printf(" umplere  |    gasite   |    gasite   |   negasite  |   negasite\n");

    int opCount_found[1500] = {0};
    int opCount_favg = 0;
    int opCount_maxF = 0;

    int opCount_notFound[1500] = {0};
    int opCount_nfavg = 0;
    int opCount_maxNF = 0;

    int foundCount = 0;
    int notFoundCount = 0;
    
    for (int i = 0; i < 5; i++) {
        searchTable(table, alpha[i], hashFunction, opCount_found, opCount_notFound, opCount_maxF, opCount_maxNF, foundCount, notFoundCount);
        freeTable(table);

        for (int j = 0; j < 1500; j++) {
            opCount_favg += opCount_found[j];
            opCount_nfavg += opCount_notFound[j];
        }

        printf("%6.2f", alpha[i]);
        printf("%13.2f", (double)opCount_favg / foundCount);
        printf("%14d", opCount_maxF);
        printf("%14.2f", (double)opCount_nfavg / notFoundCount);
        printf("%14d\n", opCount_maxNF);

        for (int j = 0; j < 1500; j++) {
             opCount_found[j] = 0;
             opCount_notFound[j] = 0;
        }

        opCount_favg = 0;
        opCount_maxF = 0;

        opCount_nfavg = 0;
        opCount_maxNF = 0;

        foundCount = 0;
        notFoundCount = 0;

    } 

    deleteCase(table, alpha[4], hashFunction, opCount_found, opCount_notFound, opCount_maxF, opCount_maxNF, foundCount, notFoundCount);
    freeTable(table);

    for (int j = 0; j < 1500; j++) {
        opCount_favg += opCount_found[j];
        opCount_nfavg += opCount_notFound[j];
    }

    printf("Delete Case\n");
    printf("%6.2f", alpha[0]);
    printf("%13.2f", (double)opCount_favg / foundCount);
    printf("%14d", opCount_maxF);
    printf("%14.2f", (double)opCount_nfavg / notFoundCount);
    printf("%14d\n", opCount_maxNF);
}

void deleteCase(Entry* table, double alpha, int (*hashFunction)(int key, int i), int *opCount_found, int *opCount_notFound, int& opCount_maxF, int& opCount_maxNF, int& foundCount, int& notFoundCount) {
    int noElements = (int)n * alpha;

    int vect[10007];
    FillRandomArray(vect, noElements, 10, 39000, true, UNSORTED);

    int foundLength = 1500;
    int indexFound[1500];
    FillRandomArray(indexFound, foundLength, 0, noElements/2 - 1, true, UNSORTED);

    int notFound[1500];
    FillRandomArray(notFound, foundLength, 39001, 50000, true, UNSORTED);

    for (int i = 0; i < noElements; i++) {
        insertKey(vect[i], table, hashFunction);
    }

    double alphaNew = 0.8;
    int noElementsNew = (int)n * alphaNew;

    int indexDelete = 0;
    int deleteKeys[2000];
    FillRandomArray(deleteKeys, 2000, noElements / 2, noElements - 1, true, UNSORTED);

    while (noElements != noElementsNew) {
        deleteKey(vect[deleteKeys[indexDelete++]], table, hashFunction);
        noElements--;
    }

    for (int i = 0; i < foundLength; i++) {
        bool f = searchKey(vect[indexFound[i]], table, hashFunction, opCount_found[i], opCount_maxF, true);
        if (f == true) {
            foundCount++;
        }

        bool nf = searchKey(notFound[i], table, hashFunction, opCount_notFound[i], opCount_maxNF, false);
        if (nf == false) {
            notFoundCount++;
        }
    }
}

void searchTable(Entry* table, double alpha, int (*hashFunction)(int key, int i), int *opCount_found, int *opCount_notFound, int &opCount_maxF, int &opCount_maxNF, int &foundCount, int &notFoundCount) {

    int noElements = (int) n * alpha;

    int vect[10007];
    FillRandomArray(vect, noElements, 10, 39000, true, UNSORTED);

    int foundLength = 1500;
    int indexFound[1500];
    FillRandomArray(indexFound, foundLength, 0, noElements - 1, true, UNSORTED);

    int notFound[1500];
    FillRandomArray(notFound, foundLength, 39001, 50000, true, UNSORTED);

    for (int i = 0; i < noElements; i++) {
        insertKey(vect[i], table, hashFunction);
    }

    for (int i = 0; i < foundLength; i++) {
        bool f = searchKey(vect[indexFound[i]], table, hashFunction, opCount_found[i], opCount_maxF, true);
        if (f == true) {
            foundCount++;
        }

        bool nf = searchKey(notFound[i], table, hashFunction, opCount_notFound[i], opCount_maxNF, false);
        if (nf == false) {
            notFoundCount++;
        }
    }
}

void printTable(Entry* table) {
    for (int i = 0; i < n; i++) {
        printf("%d,  ", table[i].key);
    }
}

void freeTable(Entry* table) {
    for (int i = 0; i < n; i++) {
        table[i] = {-1, ""};
    }
}

int hashFunction(int key, int i) {
    return ((key % n) + (a * i * i) + (b * i)) % n;
}

void insertKey(int key, Entry* table, int (*hashFunction)(int key, int i))
{
    //insereaza pe prima pozitie libera potrivit hashFunction-ului sau afiseaza ca tabela e plina
    int i = 0;
    int hf = hashFunction(key, i);
    while (i != n && table[hf].key != -1 && table[hf].key != -2)
    {
        i++;
        hf = hashFunction(key, i);
    }
    if (i != n && (table[hf].key == -1 || table[hf].key == -2))
    {
        table[hf].key = key;
    }
}

bool searchKey(int key, Entry* table, int (*hashFunction)(int key, int i), int &opCount, int &opCount_max, bool countf) {
    int i = 0;
    int hf = hashFunction(key, i);
    opCount++;
    while (i != n && table[hf].key != key && table[hf].key != - 1)
    {
        i++;
        hf = hashFunction(key, i);
        opCount++;
    }
    if (i != n && table[hf].key == key)
    {
        if (countf == true && opCount > opCount_max) {
            opCount_max = opCount;
        }
        return true;
    }
    if (countf == false && opCount > opCount_max) {
        opCount_max = opCount;
    }
    return false;
}

void deleteKey(int key, Entry* table, int (*hashFunction)(int key, int i)) {
    int i = 0;
    int hf = hashFunction(key, i);
    while (i != n && table[hf].key != key && table[hf].key != -1)
    {
        i++;
        hf = hashFunction(key, i);
    }
    if (i != n && table[hf].key == key)
    {
        table[hf].key = -2;
    }
}
