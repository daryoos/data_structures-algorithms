// tema0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*

Dintre toti algoritmi acestia de sortare, bubble sortul este cel mai ineficient pe average case si worst case, insa este cel mai rapid pentru best case.
Bubble sort este atat de rapid pe best case, fiindca parcurge doar o singura data vectorul pentru verificarea acetuia.
Dupa cum putem observa din grafice, binary insertion sort este cel mai eficient.
Diferenta dintre binary insertion sort si insertion sort simplu este ca in forma binary, o sa se execute mai putine comparatii, insa sunt la fel de multi pasi de parcurs.
Selection sort si insertion sort au la fel de multe operatii de parcurs pe average case, ele fiind asemanatoare cand este de eficienta. 
Insa pe best case, selection sortul se comporta cel mai prost.

*/

#include <iostream>
#include "Profiler.h"

#define CRT_SESCURE_NO_WARNINGS

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TEST 5

int vect[MAX_SIZE];
int vectLenght;
int vect2[MAX_SIZE];
int vect3[MAX_SIZE];
int vect4[MAX_SIZE];

Profiler tema0("GraficeSortari");

void bubbleSort(int* vect, int vectLenght);
void selectionSort(int* vect, int vectLenght);
int binarySearch(int* vect, int item, int low, int high, Operation& comp);
void binaryInsertionSort(int* vect, int vectLenght);
void insertionSort(int* vect, int vectLenght);
void vectCopy(int* vect1, int* vect2, int vectLenght);
void bestCase();
void worstCase();
void averageCase();
void showVect(int* vect, int vectLenght);
void divTests();
void groupB();
void groupW();
void groupA();
void demo();

int main() {
	bestCase();
	groupB();

	tema0.reset();
	
	worstCase();
	groupW();

	tema0.reset();

	averageCase();
	divTests();
	groupA();

	tema0.showReport();

	demo();
}

void demo() {
	vectLenght = 10;

	printf("bubble sort\n");
	FillRandomArray(vect, vectLenght, 100, 1000);
	showVect(vect, vectLenght);
	bubbleSort(vect, vectLenght);
	showVect(vect, vectLenght);
	printf("\n");

	printf("selection sort\n");
	FillRandomArray(vect, vectLenght, 100, 1000);
	showVect(vect, vectLenght);
	selectionSort(vect, vectLenght);
	showVect(vect, vectLenght);
	printf("\n");

	printf("insertion sort\n");
	FillRandomArray(vect, vectLenght, 100, 1000);
	showVect(vect, vectLenght);
	insertionSort(vect, vectLenght);
	showVect(vect, vectLenght);
	printf("\n");

	printf("binary insertion sort\n");
	FillRandomArray(vect, vectLenght, 100, 1000);
	showVect(vect, vectLenght);
	binaryInsertionSort(vect, vectLenght);
	showVect(vect, vectLenght);
}

void groupB() {
	tema0.createGroup("Best Case Atribuiri", "BBatr", "SSatr", "ISatr", "BISatr");
	tema0.createGroup("Best Case Comparatii", "BBcomp", "SScomp", "IScomp", "BIScomp");
	tema0.createGroup("Best Case Total", "BBtotal", "SStotal", "IStotal", "BIStotal");
}

void groupW() {
	tema0.createGroup("Worst Case Atribuiri", "BBatr", "SSatr", "ISatr", "BISatr");
	tema0.createGroup("Worst Case Comparatii", "BBcomp", "SScomp", "IScomp", "BIScomp");
	tema0.createGroup("Worst Case Total", "BBtotal", "SStotal", "IStotal", "BIStotal");
}

void groupA() {
	tema0.createGroup("Average Case Atribuiri", "BBatr", "SSatr", "ISatr", "BISatr");
	tema0.createGroup("Average Case Comparatii", "BBcomp", "SScomp", "IScomp", "BIScomp");
	tema0.createGroup("Average Case Total", "BBtotal", "SStotal", "IStotal", "BIStotal");
}

void divTests() {
	tema0.divideValues("BBcomp", NR_TEST);
	tema0.divideValues("SScomp", NR_TEST);
	tema0.divideValues("IScomp", NR_TEST);
	tema0.divideValues("BIScomp", NR_TEST);
	tema0.divideValues("BBatr", NR_TEST);
	tema0.divideValues("SSatr", NR_TEST);
	tema0.divideValues("ISatr", NR_TEST);
	tema0.divideValues("BISatr", NR_TEST);
	tema0.divideValues("BBtotal", NR_TEST);
	tema0.divideValues("SStotal", NR_TEST);
	tema0.divideValues("IStotal", NR_TEST);
	tema0.divideValues("BIStotal", NR_TEST);
}

void bestCase() {
	for (vectLenght = STEP_SIZE; vectLenght < MAX_SIZE; vectLenght += STEP_SIZE) {
		FillRandomArray(vect, vectLenght, 10, 50000, false, ASCENDING);
		vectCopy(vect, vect2, vectLenght);
		vectCopy(vect, vect3, vectLenght);
		vectCopy(vect, vect4, vectLenght);
		bubbleSort(vect, vectLenght);
		selectionSort(vect2, vectLenght);
		insertionSort(vect3, vectLenght);
		binaryInsertionSort(vect4, vectLenght);
	}
}

void worstCase() {
	for (vectLenght = STEP_SIZE; vectLenght < MAX_SIZE; vectLenght += STEP_SIZE) {
		FillRandomArray(vect, vectLenght, 10, 50000, false, DESCENDING);
		vectCopy(vect, vect2, vectLenght);
		vectCopy(vect, vect3, vectLenght);
		vectCopy(vect, vect4, vectLenght);
		bubbleSort(vect, vectLenght);
		selectionSort(vect2, vectLenght);
		insertionSort(vect3, vectLenght);
		binaryInsertionSort(vect4, vectLenght);
	}
}

void averageCase() {
	for (vectLenght = STEP_SIZE; vectLenght < MAX_SIZE; vectLenght += STEP_SIZE) {
		for (int i = 0; i < NR_TEST; i++) {
			FillRandomArray(vect, vectLenght);
			vectCopy(vect, vect2, vectLenght);
			vectCopy(vect, vect3, vectLenght);
			vectCopy(vect, vect4, vectLenght);
			bubbleSort(vect, vectLenght);
			selectionSort(vect2, vectLenght);
			insertionSort(vect3, vectLenght);
			binaryInsertionSort(vect4, vectLenght);
		}	
	}
}

void bubbleSort(int* vect, int vectLenght) {

	Operation comp = tema0.createOperation("BBcomp", vectLenght);
	Operation atr = tema0.createOperation("BBatr", vectLenght);

	for (int i = 0; i < vectLenght - 1; i++) {
		bool sorted = true;
		for (int j = i + 1; j < vectLenght; j++) {
			comp.count();
			if (vect[i] > vect[j]) {
				atr.count(3);
				sorted = false;
				int aux = vect[i];
				vect[i] = vect[j];
				vect[j] = aux;
			}
		}
		if (sorted == true) {
			break;
		}
	}
	tema0.addSeries("BBtotal", "BBcomp", "BBatr");
}

void selectionSort(int* vect, int vectLenght) {
	Operation comp = tema0.createOperation("SScomp", vectLenght);
	Operation atr = tema0.createOperation("SSatr", vectLenght);

	int i, j, min_idx;

	for (i = 0; i < vectLenght - 1; i++) {
		min_idx = i;
		for (j = i + 1; j < vectLenght; j++) {
			comp.count();
			if (vect[j] < vect[min_idx]) {
				min_idx = j;
			}
		}
		if (min_idx != i) {
			atr.count(3);
			int aux = vect[i];
			vect[i] = vect[min_idx];
			vect[min_idx] = aux;
		}
	}

	tema0.addSeries("SStotal", "SScomp", "SSatr");
}

int binarySearch(int* vect, int item, int low, int high, Operation& comp)
{
	while (low <= high) {
		int mid = low + (high - low) / 2;
		comp.count();
		if (item == vect[mid])
			return mid + 1;
		else {
			comp.count();
			if (item > vect[mid])
				low = mid + 1;
			else
				high = mid - 1;
		}
	}

	return low;
}

void binaryInsertionSort(int* vect, int vectLenght) {
	Operation comp = tema0.createOperation("BIScomp", vectLenght);
	Operation atr = tema0.createOperation("BISatr", vectLenght);

	int i, loc, j, k, selected;

	for (i = 1; i < vectLenght; ++i) {
		j = i - 1;
		selected = vect[i];
		atr.count();

		//gasim locul unde selection trebuie inserat
		loc = binarySearch(vect, selected, 0, j, comp);

		//mutam toate elementele dupa loc pentru a crea spatiu
		while (j >= loc) {
			vect[j + 1] = vect[j];
			atr.count();
			j--;
		}

		if (j + 1 != i)
		{
			atr.count();
			vect[j + 1] = selected;
		}
	}

	tema0.addSeries("BIStotal", "BIScomp", "BISatr");
}

void insertionSort(int* vect, int vectLenght){
	Operation comp = tema0.createOperation("IScomp", vectLenght);
	Operation atr = tema0.createOperation("ISatr", vectLenght);
	int i, key, j;
	for (i = 1; i < vectLenght; i++)
	{
		atr.count();
		key = vect[i];
		j = i - 1;

		//mutam elementele vectorului de la 0 la i -1 care sunt mai mari decat key, cu o pozitie la stanga
		while (j >= 0 && vect[j] > key)
		{
			comp.count();
			atr.count();
			vect[j + 1] = vect[j];
			j = j - 1;
		}
		if (j != 0) {
			comp.count();
		}
		if (j + 1 != i)
		{
			atr.count();
			vect[j + 1] = key;
		}
	}

	tema0.addSeries("IStotal", "IScomp", "ISatr");
}

void vectCopy(int* vect1, int* vect2, int vectLenght) {
	for (int i = 0; i < vectLenght; i++) {
		vect2[i] = vect1[i];
	}
}

void showVect(int* vect, int vectLenght) {
	for (int i = 0; i < vectLenght; i++) {
		printf("%d ", vect[i]);
	}
	printf("\n");
}