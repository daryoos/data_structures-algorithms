#include <stack>
#include <iostream>
#include "Profiler.h"

using namespace std;

#define NR_TEST 100

Profiler tema8("tema8");
Profiler test("test");

typedef struct node {
	int key;
	node* left;
	node* right;
}node;

typedef struct nodeStack {
	node* nod;
	nodeStack* next;
}nodeStack;

node* buildTree(int a, int b);

void preorder(node* root, Operation& op, bool print);

nodeStack* newNode(node* nod);
void pushNode(nodeStack** first, node* nod);
node* popNode(nodeStack** first);
void preorderIt(node* root, Operation& op, bool print);

void insertionSort(int* vect, int low, int high, Operation& comp, Operation& atr);

int partition(int* vect, int low, int high, Operation& comp, Operation& atr);
void quickSort(int* vect, int low, int high, Operation& comp, Operation& atr);
void quickSortH(int* vect, int low, int high, Operation& comp, Operation& atr, int prag);

void vectCopy(int* vect1, int* vect2, int vectLenght);
void displayVect(int* vect, int vectLength);

void treeCase();
void qsCase();

void demo();

int main()
{
	//qsCase();
	//treeCase();
	demo();
}

void demo() {
	
	int k = 10;
	Operation op = test.createOperation("test0", k);
	node* root = buildTree(1, k);
	preorder(root, op, true);
	printf("\n");
	preorderIt(root, op, true);

	printf("\n\n");

	int n = 50;
	int vect[50];
	int vect2[50];
	FillRandomArray(vect, n, 10 , 100);
	vectCopy(vect, vect2, n);
	Operation comp = test.createOperation("test1", n);
	Operation atr = test.createOperation("test2", n);
	quickSort(vect, 0, n - 1, comp, atr);
	for (int i = 0; i < n; i++) {
		printf("%d ", vect[i]);
	}
	printf("\n\n");
	quickSortH(vect2, 0, n - 1, comp, atr, 30);
	for (int i = 0; i < n; i++) {
		printf("%d ", vect[i]);
	}
}


void qsCase() {
	int n = 10000;
	int nr_teste = 20;
	int vect[10000];
	int vect2[10000];

	for (nr_teste = 1; nr_teste <= NR_TEST; nr_teste++) {
		Operation comp1 = tema8.createOperation("comp", nr_teste);
		Operation atr1 = tema8.createOperation("atr", nr_teste);

		Operation comp2 = tema8.createOperation("compH", nr_teste);
		Operation atr2 = tema8.createOperation("atrH", nr_teste);

		FillRandomArray(vect, n);
		vectCopy(vect, vect2, n);
		quickSort(vect, 0, n - 1, comp1, atr1);
		quickSortH(vect2, 0, n - 1, comp2, atr2, 30);
	}

	FillRandomArray(vect, n);
	vectCopy(vect, vect2, n);

	Operation comp = test.createOperation("time1", NR_TEST);
	Operation atr = test.createOperation("time2", NR_TEST);

	
	for (nr_teste = 1; nr_teste <= NR_TEST; nr_teste++) {

		tema8.startTimer("timer1", nr_teste);
		quickSort(vect, 0, n - 1, comp, atr);
		tema8.stopTimer("timer1", nr_teste);

		tema8.startTimer("timer2", nr_teste);
		quickSortH(vect, 0, n - 1, comp, atr, 30);
		tema8.stopTimer("timer2", nr_teste);
	}
	

	/*tema8.divideValues("comp", nr_teste);
	tema8.divideValues("atr", nr_teste);
	tema8.divideValues("compH", nr_teste);
	tema8.divideValues("atrH", nr_teste);*/

	tema8.addSeries("total1", "comp", "atr");
	tema8.addSeries("total2", "compH", "atrH");
	tema8.createGroup("comparatii", "comp", "compH");
	tema8.createGroup("atribuiri", "atr", "atrH");
	tema8.createGroup("total", "total1", "total2");
	
	tema8.reset();
}

//QUICKSORT HIBRID

void quickSortH(int* vect, int low, int high, Operation& comp, Operation& atr, int prag) {
	if (low < high) {
		if (high - low < prag) {
			insertionSort(vect, low, high, comp, atr);
			return;
		}
		else {
			int p = partition(vect, low, high, comp, atr);
			quickSortH(vect, low, p - 1, comp, atr, prag);
			quickSortH(vect, p + 1, high, comp, atr, prag);
		}
	}
}

//QUICKSORT

void quickSort(int* vect, int low, int high, Operation& comp, Operation& atr) {
	if (low < high) {
		int p = partition(vect, low, high, comp, atr);
		quickSort(vect, low, p - 1, comp, atr);
		quickSort(vect, p + 1, high, comp, atr);
	}
}

int partition(int* vect, int low, int high, Operation& comp, Operation& atr) {
	atr.count();
	int pivot = vect[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
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

//VECTOR

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

//INSERTION

void insertionSort(int* vect, int low, int high, Operation& comp, Operation& atr) {
	int i, key, j;
	for (i = low + 1; i <= high; i++)
	{
		atr.count();
		key = vect[i];
		j = i - 1;

		while (j >= low && vect[j] > key)
		{
			comp.count();
			atr.count();
			vect[j + 1] = vect[j];
			j = j - 1;
		}
		if (j != low) {
			comp.count();
		}
		if (j + 1 != i)
		{
			atr.count();
			vect[j + 1] = key;
		}
	}
}

//ARBORI

void treeCase() {
	for (int n = 100; n <= 10000; n += 100) {
		Operation op1 = tema8.createOperation("Recursiv", n);
		Operation op2 = tema8.createOperation("Iterativ", n);

		node* root = buildTree(1, n);
		
		preorder(root, op1, false);
		preorderIt(root, op2, false);
	}

	tema8.createGroup("Preorder", "Recursiv", "Iterativ");
	tema8.reset();
}

void preorderIt(node* root, Operation& op, bool print)
{
	if (root == NULL) {
		return;
	}

	nodeStack* first = newNode(root);


	while (first != NULL) {
		node* aux = popNode(&first);
		if(print == true)
			printf("%d ", aux->key);
		op.count();

		if (aux->right != NULL) {
			node* aux2 = aux->right;
			pushNode(&first, aux2);
		}
		if (aux->left != NULL) {
			node* aux2 = aux->left;
			pushNode(&first, aux2);
		}
	}
}

node* popNode(nodeStack** first) {
	if (*first == NULL) {
		return NULL;
	}
	node* nod = (*first)->nod;
	if ((*first)->next == NULL) {
		*first = NULL;
		return nod;
	}
	*first = (*first)->next;
	return nod;
}

void pushNode(nodeStack** first, node* nod) {
	nodeStack* aux = newNode(nod);
	if (*first == NULL) {
		*first = aux;
	}
	else {
		aux->next = *first;
		*first = aux;
	}
}

nodeStack* newNode(node* nod) {
	if (nod == NULL) {
		return NULL;
	}
	nodeStack* nodStack = (nodeStack*)malloc(sizeof(nodeStack));
	nodStack->nod = nod;
	nodStack->next = NULL;
	return nodStack;
}

void preorder(node* root, Operation& op, bool print) 
{
	if (root == NULL) {
		return;
	}
	if(print == true)
		printf("%d ", root->key);
	op.count();
	preorder(root->left, op, print);
	preorder(root->right, op, print);
}

node* buildTree(int a, int b) 
{
	if (a > b)
	{
		return NULL;
	}
	else
	{
		node* root = (node*)malloc(sizeof(node));

		root->key = (a + b) / 2;

		root->left = buildTree(a, root->key - 1);
		root->right = buildTree(root->key + 1, b);

		return root;
	}
}
