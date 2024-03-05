#include <iostream>
#include "Profiler.h"

Profiler tema9("tema9");
Profiler test("test");

using namespace std;

typedef struct nodeT {
	int key;
	int rank;
	nodeT* parent;
}nodeT;

typedef struct muchie {
	int weight;
	nodeT* x;
	nodeT* y;
}muchie;

typedef struct graf {
	int nrNod;
	int nrMuchii;
	muchie** muchii;
}graf;

int partition(muchie** muchii, int low, int high, Operation& comp, Operation& atr);
void quickSort(muchie** muchii, int low, int high, Operation& comp, Operation& atr);

nodeT* makeSet(int key);
nodeT* findSet(nodeT* x, Operation& comp, Operation& atr);
void link(nodeT* x, nodeT* y, Operation& comp, Operation& atr);
void unionT(nodeT* x, nodeT* y, Operation& comp, Operation& atr);
muchie** kruskal(graf* g, int& nrK, Operation& comp, Operation& atr);

graf* generateGraf(int nrNod, int nrMuchii);

void demo();

void averageCase();


int main()
{
	demo();
	//averageCase();
}

void demo() {
	Operation op = test.createOperation("op", 1);

	/*int n = 10;
	nodeT** nod = (nodeT**)malloc(n * sizeof(nodeT*));
	for (int i = 0; i < n; i++) {
		nod[i] = makeSet(i + 1);
	}
	unionT(nod[0], nod[1], op, op);
	unionT(nod[0], nod[2], op, op);
	unionT(nod[1], nod[5], op, op);
	unionT(nod[3], nod[5], op, op);

	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", nod[i]->key, nod[i]->rank, nod[i]->parent->key);
	}

	printf("\n");*/

	/*graf* g = (graf*)malloc(sizeof(graf));
	g->nrNod = 4;
	g->nrMuchii = 5;
	g->muchii = (muchie**)malloc(g->nrMuchii * sizeof(muchie*));

	nodeT** noduri = (nodeT**)malloc(g->nrNod * sizeof(nodeT*));
	for (int i = 0; i < g->nrNod; i++) {
		noduri[i] = makeSet(i + 1);
	}

	g->muchii[0] = (muchie*)malloc(sizeof(muchie));
	g->muchii[0]->weight = 1;
	g->muchii[0]->x = noduri[0];
	g->muchii[0]->y = noduri[1];

	g->muchii[1] = (muchie*)malloc(sizeof(muchie));
	g->muchii[1]->weight = 4;
	g->muchii[1]->x = noduri[0];
	g->muchii[1]->y = noduri[2];

	g->muchii[2] = (muchie*)malloc(sizeof(muchie));
	g->muchii[2]->weight = 1;
	g->muchii[2]->x = noduri[0];
	g->muchii[2]->y = noduri[3];

	g->muchii[3] = (muchie*)malloc(sizeof(muchie));
	g->muchii[3]->weight = 1;
	g->muchii[3]->x = noduri[1];
	g->muchii[3]->y = noduri[3];

	g->muchii[4] = (muchie*)malloc(sizeof(muchie));
	g->muchii[4]->weight = 2;
	g->muchii[4]->x = noduri[2];
	g->muchii[4]->y = noduri[3];

	int nrK = 0;
	muchie** kruskalT = kruskal(g, nrK, op, op);
	for (int i = 0; i < nrK; i++) {
		printf("%d %d %d\n", kruskalT[i]->x->key, kruskalT[i]->y->key, kruskalT[i]->weight);
	}*/

	int nrNod = 6;
	int nrMuchii = 12;
	graf* g = generateGraf(nrNod, nrMuchii);
	for (int i = 0; i < g->nrMuchii; i++) {
		printf("%d %d %d\n", g->muchii[i]->x->key, g->muchii[i]->y->key, g->muchii[i]->weight);
	}
	printf("\n");
	int nrK = 0;
	muchie** kruskalT = kruskal(g, nrK, op, op);
	for (int i = 0; i < nrK; i++) {
		printf("%d %d %d\n", kruskalT[i]->x->key, kruskalT[i]->y->key, kruskalT[i]->weight);
	}
}

void averageCase() {
	for (int n = 100; n <= 10000; n += 100) {
		Operation comp = tema9.createOperation("comp", n);
		Operation atr = tema9.createOperation("atr", n);

		graf* g = generateGraf(n, n * 4);
		int nrK = 0;
		muchie** kruskalT = kruskal(g, nrK, comp, atr);
	}

	tema9.addSeries("total", "comp", "atr");
	tema9.createGroup("kruskal", "total", "comp", "atr");
	tema9.reset();
}

graf* generateGraf(int nrNod, int nrMuchii) {
	graf* g = (graf*)malloc(sizeof(graf));
	g->nrNod = nrNod;
	g->nrMuchii = nrMuchii;
	g->muchii = (muchie**)malloc(g->nrMuchii * sizeof(muchie*));

	nodeT** noduri = (nodeT**)malloc(g->nrNod * sizeof(nodeT*));
	for (int i = 0; i < g->nrNod; i++) {
		noduri[i] = makeSet(i + 1);
	}

	int k = 0;
	for (int i = 1; i < g->nrNod; i++) {
		g->muchii[k] = (muchie*)malloc(sizeof(muchie));
		g->muchii[k]->weight = rand() % nrMuchii + 1;
		g->muchii[k]->x = noduri[0];
		g->muchii[k++]->y = noduri[i];
	}

	for (int i = k; i < g->nrMuchii; i++) {
		g->muchii[i] = (muchie*)malloc(sizeof(muchie));
		g->muchii[i]->weight = rand() % nrMuchii + 1;
		g->muchii[i]->x = noduri[rand() % nrNod];
		g->muchii[i]->y = noduri[rand() % nrNod];
	}

	return g;
}

muchie** kruskal(graf* g, int& nrK, Operation &comp, Operation &atr) {
	muchie** kruskalT = (muchie**)malloc(g->nrMuchii * sizeof(muchie*));

	quickSort(g->muchii, 0, g->nrMuchii - 1, comp, atr);

	for (int i = 0; i < g->nrMuchii; i++) {
		comp.count();
		if (findSet(g->muchii[i]->x, comp, atr) != findSet(g->muchii[i]->y, comp, atr)) {
			//printf("%d %d %d\n", g->muchii[i]->x->key, g->muchii[i]->y->key, g->muchii[i]->weight);
			atr.count();
			kruskalT[nrK++] = g->muchii[i];
			unionT(g->muchii[i]->x, g->muchii[i]->y, comp, atr);
		}
	}
	kruskalT = (muchie**)realloc(kruskalT, nrK * sizeof(muchie*));

	return kruskalT;
}

void unionT(nodeT* x, nodeT* y, Operation &comp, Operation &atr) {
	link(findSet(x, comp, atr), findSet(y, comp, atr), comp, atr);
}

void link(nodeT* x, nodeT* y, Operation &comp, Operation &atr) {
	comp.count();
	if (x->rank > y->rank) {
		atr.count();
		y->parent = x;
	}
	else {
		atr.count();
		x->parent = y;
		comp.count();
		if (x->rank == y->rank) {
			atr.count();
			y->rank += 1;
		}
	}
}

nodeT* findSet(nodeT* x, Operation &comp, Operation &atr) {
	comp.count();
	if (x != x->parent) {
		atr.count();
		x->parent = findSet(x->parent, comp, atr);
	}
	return x->parent;
}

nodeT* makeSet(int key) {
	nodeT* aux = (nodeT*)malloc(sizeof(nodeT));
	aux->key = key;
	aux->rank = 0;
	aux->parent = aux;
	return aux;
}

int partition(muchie** muchii, int low, int high, Operation& comp, Operation& atr) {
	atr.count();
	muchie* pivot = muchii[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		comp.count();
		if (muchii[j]->weight < pivot->weight) {
			atr.count(3);
			swap(muchii[++i], muchii[j]);
		}
	}
	if (i + 1 != high) {
		atr.count(3);
		swap(muchii[i + 1], muchii[high]);
	}
	return i + 1;
}

void quickSort(muchie** muchii, int low, int high, Operation& comp, Operation& atr) {
	if (low < high) {
		int p = partition(muchii, low, high, comp, atr);
		quickSort(muchii, low, p - 1, comp, atr);
		quickSort(muchii, p + 1, high, comp, atr);
	}
}

