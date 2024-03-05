
#include <iostream>
#include "Profiler.h"

using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TEST 5
#define NR_TEST_BS 10

int vect[MAX_SIZE + 10];
int vect2[MAX_SIZE + 10];
int vect3[MAX_SIZE + 10];
int vect4[MAX_SIZE + 10];
int vect5[MAX_SIZE + 10];
int vectLength;

Profiler tema3("quickSort");
Profiler bubble("bubble");

void displayVect(int* vect, int vectLength);
void vectCopy(int* vect1, int* vect2, int vectLenght);
void demo();

void bestCaseQS();
void bestCaseHS();
void averageCase();
void worstCase();

void groupB();
void groupA();
void groupW();
void divTests();

//HS
void heapify(int* vect, int vectLength, int root, Operation &comp, Operation &atr);
void buildHeap(int* vect, int vectLength, Operation &comp, Operation &atr);
void heapSort(int* vect, int vectLenght);

//QS
int partition(int* vect, int low, int high, Operation &comp, Operation &atr, bool bestCase);
void quickSort(int* vect, int low, int high, Operation &comp, Operation &atr, bool bestCase);

//QSelect
int partitionSelect(int* vect, int low, int high);
int kthSmallest(int* vect, int low, int high, int k);

//BS
void bubbleSort(int* vect, int vectLenght);
void bubbleRec(int* vect, int vectLenght, Operation &comp, Operation &atr);

void compareBS();

int main()
{
    /*worstCase();

    tema3.reset();

    averageCase();
    divTests();

    tema3.reset();
    
    bestCaseQS();
    bestCaseHS();

    tema3.reset();*/

    /*compareBS();

    tema3.reset();*/
    
    //demo();
}

void demo() {
    vectLength = 10;

    Operation comp = tema3.createOperation("demo", vectLength);
    Operation atr = tema3.createOperation("demo", vectLength);

    FillRandomArray(vect, vectLength, 10, 90);
    displayVect(vect, vectLength);
    cout << "\n";

    vectCopy(vect, vect2, vectLength);
    vectCopy(vect, vect3, vectLength);
    vectCopy(vect, vect4, vectLength);
    vectCopy(vect, vect5, vectLength);

    quickSort(vect, 0, vectLength - 1, comp, atr, false);
    cout << "quickSort\n";
    displayVect(vect, vectLength);

    heapSort(vect2, vectLength);
    cout << "heapSort\n";
    displayVect(vect2, vectLength);

    printf("kth smallest\n%d", kthSmallest(vect, 0, vectLength - 1, vectLength / 2));

    bubbleSort(vect4, vectLength);
    cout << "bubbleSort\n";
    displayVect(vect4, vectLength);

    bubbleRec(vect5, vectLength, comp, atr);
    cout << "bubbleRec\n";
    displayVect(vect5, vectLength);

}

void displayVect(int* vect, int vectLength) {
    for (int i = 0; i < vectLength; i++) {
        printf("%d ", vect[i]);
    }
    printf("\n");
}

void vectCopy(int* vect1, int* vect2, int vectLenght) {
    for (int i = 0; i < vectLenght; i++) {
        vect2[i] = vect1[i];
    }
}

void bestCaseQS() {
    for (vectLength = STEP_SIZE; vectLength <= MAX_SIZE; vectLength += STEP_SIZE) {
        Operation compQS = tema3.createOperation("QScomp", vectLength);
        Operation atrQS = tema3.createOperation("QSatr", vectLength);
        FillRandomArray(vect, vectLength, 10, 50000, false, ASCENDING);
        quickSort(vect, 0, vectLength - 1, compQS, atrQS, true);
    }
}

void bestCaseHS() {
    for (vectLength = STEP_SIZE; vectLength <= MAX_SIZE; vectLength += STEP_SIZE) {
        FillRandomArray(vect, vectLength, 10, 50000, false, DESCENDING);
        heapSort(vect, vectLength);
    }
    groupB();
}

void averageCase() {
    for (vectLength = STEP_SIZE; vectLength <= MAX_SIZE; vectLength += STEP_SIZE) {
        for (int i = 0; i < NR_TEST; i++) {
            Operation compQS = tema3.createOperation("QScomp", vectLength);
            Operation atrQS = tema3.createOperation("QSatr", vectLength);
            FillRandomArray(vect, vectLength);
            vectCopy(vect, vect2, vectLength);
            quickSort(vect, 0, vectLength - 1, compQS, atrQS, false);
            heapSort(vect2, vectLength);
        }
    }
    groupA();
}

void worstCase() {
    for (vectLength = STEP_SIZE; vectLength <= MAX_SIZE; vectLength += STEP_SIZE) {
        Operation compQS = tema3.createOperation("QScomp", vectLength);
        Operation atrQS = tema3.createOperation("QSatr", vectLength);
        FillRandomArray(vect, vectLength, 10, 50000, false, ASCENDING);
        vectCopy(vect, vect2, vectLength);
        quickSort(vect, 0, vectLength - 1, compQS, atrQS, false);
        heapSort(vect2, vectLength);
    }
    //groupW();
}

void divTests() {
    tema3.divideValues("QScomp", NR_TEST);
    tema3.divideValues("QSatr", NR_TEST);
    tema3.divideValues("HScomp", NR_TEST);
    tema3.divideValues("HSatr", NR_TEST);
    tema3.addSeries("HStotal", "HScomp", "HSatr");
    tema3.addSeries("QStotal", "QScomp", "QSatr");
    
}

void groupB() {
    tema3.createGroup("Best Case Atribuiri", "QSatr", "HSatr");
    tema3.createGroup("Best Case Comparatii", "QScomp", "HScomp");
    tema3.createGroup("Best Case Total", "QStotal", "HStotal");
}

void groupA() {
    tema3.createGroup("Average Case Atribuiri", "QSatr", "HSatr");
    tema3.createGroup("Average Case Comparatii", "QScomp", "HScomp");
    tema3.createGroup("Average Case Total", "QStotal", "HStotal");
}

void groupW() {
    tema3.createGroup("Worst Case Atribuiri", "QSatr", "HSatr");
    tema3.createGroup("Worst Case Comparatii", "QScomp", "HScomp");
    tema3.createGroup("Worst Case Total", "QStotal", "HStotal");
}

//HS
void heapify(int* vect, int vectLength, int root, Operation &comp, Operation &atr) {

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
        swap(vect[root], vect[largest]);
        heapify(vect, vectLength, largest, comp, atr);
    }
}

void buildHeap(int* vect, int vectLength, Operation &comp, Operation &atr) {
    for (int i = vectLength / 2 - 1; i >= 0; i--) {
        heapify(vect, vectLength, i, comp, atr);
    }
}

void heapSort(int* vect, int vectLength) {

    Operation comp = tema3.createOperation("HScomp", vectLength);
    Operation atr = tema3.createOperation("HSatr", vectLength);

    buildHeap(vect, vectLength, comp, atr);

    for (int i = vectLength - 1; i >= 0; i--) {
        atr.count(3);
        swap(vect[0], vect[i]);
        heapify(vect, i, 0, comp, atr);
    }
}

//QS
int partition(int* vect, int low, int high, Operation &comp, Operation &atr, bool bestCase) { 
    if (bestCase == true) {
        swap(vect[(high + low) / 2], vect[high]);
    }
    atr.count();
    int pivot = vect[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        comp.count();
        if (vect[j] < pivot) {
            atr.count(3);
            swap(vect[++i], vect[j]);
        }
    }
    if (i + 1 != high) {
        atr.count(3);
        swap(vect[i + 1], vect[high]);
    }
    return i + 1;
}

void quickSort(int* vect, int low, int high, Operation &comp, Operation &atr, bool bestCase) {
    if (low < high) {
        int p = partition(vect, low, high, comp, atr, bestCase);
        quickSort(vect, low, p - 1, comp, atr, bestCase);
        quickSort(vect, p + 1, high, comp, atr, bestCase);
    }
}

//QSelect
int partitionSelect(int* vect, int low, int high) {
    int x = vect[high];
    int i = low;

    for (int j = low; j <= high - 1; j++) {
        if (vect[j] <= x) {
            swap(vect[i], vect[j]);
            i++;
        }
    }
    swap(vect[i], vect[high]);
    return i;
}

int kthSmallest(int* vect, int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int i = partitionSelect(vect, low, high);

        if (i - low == k - 1) {
            return vect[i];
        }

        if (i - low > k - 1) {
            return kthSmallest(vect, low, i - 1, k);
        }

        return kthSmallest(vect, i + 1, high, k - i + low - 1);
    }
    return INT_MAX;
}

//BS
void bubbleSort(int* vect, int vectLenght) {

    Operation comp = tema3.createOperation("BScomp", vectLenght);
    Operation atr = tema3.createOperation("BSatr", vectLenght); 

    for (int i = 0; i < vectLenght; i++) {
        bool sorted = true;
        for (int j = 0; j < vectLenght - i - 1; j++) {
            comp.count();
            if (vect[j] > vect[j + 1]) {
                atr.count(3);
                sorted = false;
                int aux = vect[j + 1];
                vect[j + 1] = vect[j];
                vect[j] = aux;
            }
        }
        if (sorted == true) {
            break;
        }
    }
}

void bubbleRec(int* vect, int vectLenght, Operation &comp, Operation &atr) {
    if (vectLenght == 1)
        return;

    int count = 0;

    for (int i = 0; i < vectLenght - 1; i++) {
        comp.count();
        if (vect[i] > vect[i + 1]) {
            atr.count(3);
            swap(vect[i], vect[i + 1]);
            count++;
        }
    }

    if (count == 0) {
        return;
    }

    bubbleRec(vect, vectLenght - 1, comp, atr);
}

void compareBS() {
    for (vectLength = STEP_SIZE; vectLength <= MAX_SIZE; vectLength += STEP_SIZE) {
        for (int i = 0; i < NR_TEST_BS; i++) {

            Operation compBR = tema3.createOperation("BRcomp", vectLength);
            Operation atrBR = tema3.createOperation("BRatr", vectLength);
            
            FillRandomArray(vect, vectLength);
            vectCopy(vect, vect2, vectLength);
            vectCopy(vect, vect3, vectLength);
            vectCopy(vect, vect4, vectLength);

            bubbleSort(vect, vectLength);

            bubbleRec(vect2, vectLength, compBR, atrBR);

            
        }
        for (int i = 0; i < NR_TEST_BS; i++) {
            Operation compBR = bubble.createOperation("BRTime1", vectLength);
            Operation atrBR = bubble.createOperation("BRTime2", vectLength);

            tema3.startTimer("timerBS", vectLength);
            bubbleSort(vect3, vectLength);
            tema3.stopTimer("timerBS", vectLength);

            tema3.startTimer("timerBR", vectLength);
            bubbleRec(vect4, vectLength, compBR, atrBR);
            tema3.stopTimer("timerBR", vectLength);
        }
    }
    tema3.divideValues("BScomp", NR_TEST_BS);
    tema3.divideValues("BSatr", NR_TEST_BS);
    tema3.divideValues("BRcomp", NR_TEST_BS);
    tema3.divideValues("BRatr", NR_TEST_BS);

    tema3.createGroup("Timer", "timerBS", "timerBR");

    tema3.addSeries("BStotal", "BScomp", "BSatr");
    tema3.addSeries("BRtotal", "BRcomp", "BRatr");

    tema3.createGroup("Total", "BStotal", "BRtotal");
    tema3.createGroup("Comp", "BScomp", "BRcomp");
    tema3.createGroup("Atr", "BSatr", "BRatr");

}