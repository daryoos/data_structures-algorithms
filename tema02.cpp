// heapTopDown.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Profiler.h"

using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TEST 5

int vect[MAX_SIZE + 10];
int vect2[MAX_SIZE + 10];
int vectLength;

Profiler tema2("HeapSort");

void swap(int* a, int* b);
void displayVect(int* vect, int vectLength);
void vectCopy(int* vect1, int* vect2, int vectLenght);
void demo();

void averageCase();
void worstCase();

void groupA();
void groupW();
void divTests();

//TD
void pushHeap(int* vect, int& vectLength, int key, Operation comp, Operation atr);
void buildHeapTD(int* vect, int vectLength);

//BU
void heapify(int* vect, int vectLength, int root, Operation comp, Operation atr);
void buildHeapBU(int* vect, int vectLength);
void heapSortBU(int* vect, int vectLenght);


int main() {
     worstCase();
     groupW();

     tema2.reset();

     averageCase();
     divTests();
     groupA();

     tema2.showReport();

     demo();
}

void demo() {

    vectLength = 10;

    printf("bottom up heap sort\n");
    FillRandomArray(vect, vectLength, 100, 1000);
    displayVect(vect, vectLength);
    heapSortBU(vect, vectLength);
    displayVect(vect, vectLength);
    printf("\n");

    printf("bottom up heap\n");
    FillRandomArray(vect, vectLength, 100, 1000);
    displayVect(vect, vectLength);
    buildHeapBU(vect, vectLength);
    displayVect(vect, vectLength);
    printf("\n");

    printf("top down heap\n");
    FillRandomArray(vect, vectLength, 100, 1000);
    displayVect(vect, vectLength);
    buildHeapTD(vect, vectLength);
    displayVect(vect, vectLength);
    printf("\n");
}

void displayVect(int* vect, int vectLength) {
    for (int i = 0; i < vectLength; i++) {
        printf("%d ", vect[i]);
    }
    printf("\n");
}

void swap(int* a, int* b) {
    int temp = *a;

    *a = *b;

    *b = temp;
}

void vectCopy(int* vect1, int* vect2, int vectLenght) {
    for (int i = 0; i < vectLenght; i++) {
        vect2[i] = vect1[i];
    }
}


void averageCase() {
    for (vectLength = STEP_SIZE; vectLength <= MAX_SIZE; vectLength += STEP_SIZE) {
        for (int i = 0; i < NR_TEST; i++) {
            FillRandomArray(vect, vectLength);
            vectCopy(vect, vect2, vectLength);
            buildHeapBU(vect, vectLength);
            buildHeapTD(vect2, vectLength);
        }
    }
}

void worstCase() {

    for (vectLength = STEP_SIZE; vectLength <= MAX_SIZE; vectLength += STEP_SIZE) {
        FillRandomArray(vect, vectLength, 10, 50000, false, ASCENDING);
        vectCopy(vect, vect2, vectLength);
        buildHeapBU(vect, vectLength);
        buildHeapTD(vect2, vectLength);
    }
}

void divTests() {
    tema2.divideValues("BUcomp", NR_TEST);
    tema2.divideValues("BUatr", NR_TEST);
    tema2.divideValues("TDcomp", NR_TEST);
    tema2.divideValues("BUatr", NR_TEST);
}

void groupA() {
    tema2.createGroup("Average Case Atribuiri", "BUatr", "TDatr");
    tema2.createGroup("Average Case Comparatii", "BUcomp", "TDcomp");
    tema2.createGroup("Average Case Total", "BUtotal", "TDtotal");
}

void groupW() {
    tema2.createGroup("Worst Case Atribuiri", "BUatr", "TDatr");
    tema2.createGroup("Worst Case Comparatii", "BUcomp", "TDcomp");
    tema2.createGroup("Worst Case Total", "BUtotal", "TDtotal");
}

//BU
void heapify(int* vect, int vectLength, int root, Operation comp, Operation atr) {

    int largest = root;

    int left = 2 * root + 1;

    int right = 2 * root + 2;

    if (left < vectLength) {
        comp.count();
        if (vect[left] > vect[largest]) {
            largest = left;
        }
    }

    if (right < vectLength) {
        comp.count();
        if (vect[right] > vect[largest]) {
            largest = right;
        }
    }

    if (largest != root) {
        atr.count(3);
        swap(&vect[root], &vect[largest]);
        heapify(vect, vectLength, largest, comp, atr);
    }
}

void buildHeapBU(int* vect, int vectLength) {

    Operation comp = tema2.createOperation("BUcomp", vectLength);
    Operation atr = tema2.createOperation("BUatr", vectLength);

    for (int i = vectLength / 2 - 1; i >= 0; i--) {
        heapify(vect, vectLength, i, comp, atr);
    }

    tema2.addSeries("BUtotal", "BUcomp", "BUatr");
}

void heapSortBU(int* vect, int vectLength) {
    Operation comp = tema2.createOperation("heapSort", vectLength);
    Operation atr = tema2.createOperation("heapSort", vectLength);

    buildHeapBU(vect, vectLength);

    for (int i = vectLength - 1; i >= 0; i--) {
        atr.count(3);
        swap(&vect[0], &vect[i]);
        heapify(vect, i, 0, comp, atr);
    }
}

//TD
void pushHeap(int* vect, int& vectLength, int key, Operation comp, Operation atr) {

    vectLength++;
    atr.count();
    vect[vectLength - 1] = key;

    int i = (vectLength - 1) / 2;
    int j = vectLength - 1;
    while (i != 0) {

        comp.count();
        if (vect[i] > vect[j]) {
            return;
        }

        atr.count(3);
        swap(&vect[i], &vect[j]);
        j = i;
        i = i / 2;
    }

    comp.count();
    if (vect[i] < vect[j]) {
        atr.count(3);
        swap(&vect[i], &vect[j]);
    }
}

void buildHeapTD(int* vect, int vectLength) {

    Operation comp = tema2.createOperation("TDcomp", vectLength);
    Operation atr = tema2.createOperation("TDatr", vectLength);

    int heapSize = 0;
    for (int i = 0; i < vectLength; i++) {
        pushHeap(vect, heapSize, vect[i], comp, atr);
    }

    tema2.addSeries("TDtotal", "TDcomp", "TDatr");
}
