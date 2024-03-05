/*

	Algoritmul Merge Sort pe liste are complexitate nlogn.

	Avem nevoie de 3 functii:
		- heapify : 
					dintr-un vectori de noduri, facem un heap;
					ne folosim de aceasta functie sa cream un min heap;
		- pop :
				luam primul element din heap si il returnam;
				dupa ce l-am extras din heap, trebuie sa verificam ca elementele ramase formeaza un heap; 
				pentru asta, aplicam heapify;
		- mergeSort :
					cat timp mai sunt elemente in heap,
					extragem primul element din heap intr-un vector,
					ultimul element din heap va deveni primul,
					iar noul ultimul element o sa ia valoarea urmatorului nod din aceea lista

	Din grafice putem observa faptul ca algoritmul functioneaza mai rapid daca sunt mai putine liste,
	deoarece o sa avem un heap de dimensiune mai mica, functia heapify o sa se apeleze de mai putine ori.

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100

Profiler tema4("MergeSort");
Profiler test("test");

typedef struct node {
	int key;
	struct node* next;
}Node;


Node* create(int key);
void insert(Node** first, int key);
Node* pop(Node* heap[], int& heapSize, Operation comp, Operation atr);

void printList(Node* list);
void printLists(Node* list[], int k);

void heapify(Node* list[], int i, int k, Operation comp, Operation atr);

void pushHeap(Node* heap[], Node* key, int &heapSize, Operation comp, Operation atr);

void mergeSort(Node* list[], int k, int* vect, Operation comp, Operation atr);

void demo();

void generateLists(Node* list[], int n, int k);

void averageCase1();
void averageCase2();

int main() {

	averageCase1();

	tema4.reset();

	averageCase2();

	tema4.reset();

	demo();
}

void demo() {

	int n1 = 10;
	int vect1[10];

	Operation comp = test.createOperation("comp", n1);
	Operation atr = test.createOperation("atr", n1);

	int k1 = 4;
	Node** list1 = (Node**)malloc(k1 * sizeof(Node*));
	for (int i = 0; i < k1; i++) {
		list1[i] = NULL;
	}

	/*insert(&list1[0], 8);
	insert(&list1[0], 6);
	insert(&list1[1], 9);
	insert(&list1[1], 4);
	insert(&list1[1], 3);
	insert(&list1[2], 12);
	insert(&list1[3], 15);
	insert(&list1[3], 11);
	insert(&list1[3], 2);
	insert(&list1[3], 1);*/

	generateLists(list1, n1, k1);

	printLists(list1, k1);

	/*Node** heap1 = (Node**)malloc(k1 * sizeof(Node*));
	int heapSize1 = 0;

	for (int i = 0; i < k1; i++) {
		pushHeap(heap1, list1[i], heapSize1, comp, atr);
	}

	for (int i = 0; i < heapSize1; i++) {
		printf("%d ", heap1[i]->key);
	}*/

	mergeSort(list1, k1, vect1, comp, atr);

	printf("\nMerge Sort : \n");
	for (int i = 0; i < n1; i++) {
		printf("%d ", vect1[i]);
	}
	printf("\n");
}

void generateLists(Node* list[], int n, int k) {

	int listLength = n / k;
	int restLength = n % k;
	int r = 0;

	for (int i = 0; i < k; i++) {
		int vect[MAX_SIZE];
		FillRandomArray(vect, listLength + 1, 10, 50000, false, DESCENDING);

		for (int j = 0; j < listLength; j++) {
			insert(&list[i], vect[j]);
		}

		if (r != restLength) {
			insert(&list[i], vect[listLength]);
			r++;
		}
	}
}

void averageCase1() {

	int k[] = { 5, 10, 50 };

	for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {

		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				Operation comp = tema4.createOperation("K5_comp", n);
				Operation atr = tema4.createOperation("K5_atr", n);

				Node** list = (Node**)malloc(k[i] * sizeof(Node*));
				for (int j = 0; j < k[i]; j++) {
					list[j] = NULL;
				}

				generateLists(list, n, k[i]);

				int vect[MAX_SIZE];
				mergeSort(list, k[i], vect, comp, atr);

				/*for (int i = 0; i < n; i++) {
				printf("%d ", vect[i]);
				}
				printf("\n");*/
				free(list);
			}

			if (i == 1) {
				Operation comp = tema4.createOperation("K10_comp", n);
				Operation atr = tema4.createOperation("K10_atr", n);

				Node** list = (Node**)malloc(k[i] * sizeof(Node*));
				for (int j = 0; j < k[i]; j++) {
					list[j] = NULL;
				}

				generateLists(list, n, k[i]);

				int vect[MAX_SIZE];
				mergeSort(list, k[i], vect, comp, atr);

				/*for (int i = 0; i < n; i++) {
				printf("%d ", vect[i]);
				}
				printf("\n");*/
				free(list);
			}

			if (i == 2) {
				Operation comp = tema4.createOperation("K50_comp", n);
				Operation atr = tema4.createOperation("K50_atr", n);

				Node** list = (Node**)malloc(k[i] * sizeof(Node*));
				for (int j = 0; j < k[i]; j++) {
					list[j] = NULL;
				}

				generateLists(list, n, k[i]);

				int vect[MAX_SIZE];
				mergeSort(list, k[i], vect, comp, atr);

				/*for (int i = 0; i < n; i++) {
				printf("%d ", vect[i]);
				}
				printf("\n");*/
				free(list);
			}
		}
	}
	
	tema4.addSeries("K50", "K50_comp", "K50_atr");
	tema4.addSeries("K10", "K10_comp", "K10_atr");
	tema4.addSeries("K5", "K5_comp", "K5_atr");
	tema4.createGroup("K", "K5", "K10", "K50");
}

void averageCase2() {

	int n = MAX_SIZE;

	for (int k = 10; k <= 500; k += 10) {
		Operation comp = tema4.createOperation("Case2_comp", k);
		Operation atr = tema4.createOperation("Case2_atr", k);

		Node** list = (Node**)malloc(k * sizeof(Node*));
		for (int i = 0; i < k; i++) {
			list[i] = NULL;
		}

		generateLists(list, n, k);

		int vect[MAX_SIZE];
		mergeSort(list, k, vect, comp, atr);

		/*for (int i = 0; i < n; i++) {
			printf("%d ", vect[i]);
		}
		printf("\n");*/

		free(list);
	}

	tema4.addSeries("Case2_total", "Case2_comp", "Case2_atr");
}

Node* create(int key) {

	Node* node = (Node*)malloc(sizeof(Node));

	node->key = key;
	node->next = NULL;

	return node;
}

void insert(Node** first, int key) {

	Node* node = create(key);

	if (*first == NULL) {
		*first = node;
	}
	else {
		node->next = *first;
		*first = node;
	}
}

void heapify(Node* list[], int i, int k, Operation comp, Operation atr) {

	int smallest = i;

	int left = 2 * i + 1;

	int right = 2 * i + 2;

	if (left < k) {
		comp.count();
		if ((list[left])->key < (list[smallest])->key) {
			smallest = left;
		}
	}

	if (right < k) {
		comp.count();
		if ((list[right])->key < (list[smallest])->key) {
			smallest = right;
		}
	}

	if (smallest != i) {
		atr.count(3);
		swap(list[i], list[smallest]);
		heapify(list, smallest, k, comp, atr);
	}
}

Node* pop(Node* heap[], int& heapSize, Operation comp, Operation atr) {

	atr.count(2);
	Node* aux = heap[0];
	heap[0] = heap[heapSize - 1];
	heapSize--;

	heapify(heap, 0, heapSize, comp, atr);

	return aux;
}

void pushHeap(Node* heap[], Node* key, int& heapSize, Operation comp, Operation atr) {
	atr.count();

	heapSize++;
	heap[heapSize - 1] = key;


	int i = (heapSize - 1) / 2;
	int j = heapSize - 1;
	while (i != 0) {

		comp.count();
		if (heap[i]->key < heap[j]->key) {
			return;
		}

		atr.count(3);
		swap(heap[i], heap[j]);
		j = i;
		i = i / 2;
	}

	comp.count();
	if (heap[i]->key > heap[j]->key) {
		atr.count(3);
		swap(heap[i], heap[j]);
	}
}


void mergeSort(Node* list[], int k, int* vect, Operation comp, Operation atr) {

	Node** heap = (Node**)malloc(k * sizeof(Node*));
	
	int heapSize = 0;
	for (int i = 0; i < k; i++) {
		pushHeap(heap, list[i], heapSize, comp, atr);
	}

	Node* heapHead = NULL;
	Node* heapTail = NULL;

	int i = 0;
	int j = 0;
	while (heapSize) {
		Node* smallest = pop(heap, heapSize, comp, atr);
		atr.count();
		vect[j++] = smallest->key;

		comp.count();
		atr.count(2);
		if (heapHead == NULL)
		{
			heapHead = smallest;
			heapTail = smallest;
		}
		else
		{
			heapTail->next = smallest;
			heapTail = smallest;
		}

		comp.count();
		if (smallest->next){
			pushHeap(heap, smallest->next, heapSize, comp, atr);
		}
	}
}

void printList(Node* list) {

	while (list != NULL) {
		printf("%d ", list->key);
		list = list->next;
	}
	printf("\n");

}

void printLists(Node* list[], int k) {

	for (int i = 0; i < k; i++) {
		printf("list %d : ", i);
		printList(list[i]);
	}
}


