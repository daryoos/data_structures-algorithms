#include <iostream>
#include <fstream>

using namespace std;

typedef struct nod {
    int key;
    struct nod* next;
}nod;

typedef struct {
    int n;
    nod** t;
    int* p; //parinti
    int* color;
}graf;

enum{WHITE, GREY, BLACK};

ifstream in("graf.txt");


void push(nod* &first, int key);
int pop(nod* &stack);
void dfsVisit(graf &g, int key);
void dfs(graf &g);
void init(graf &g);

int main()
{
    if (!in) {
        return 1;
    }
    graf g;
    init(g);

    in.close();

    for (int i = 0; i < g.n; i++) {
        printf("%d: ", i);
        nod* t = g.t[i];

        while (t) {
            printf("%d ", t->key);
            t = t->next;
        }
        printf("\n");
    }

    printf("\n");
    dfs(g);
    printf("\nparinti: \n");
    for (int i = 0; i < g.n; i++) {
        printf("%d ", g.p[i]);
    }
}

void push(nod* &first, int key) {
    nod* aux = (nod*)malloc(sizeof(nod));
    aux->key = key;
    if (first) {
        aux->next = first;
        first = aux;
    }
    else {
        aux->next = NULL;
        first = aux;
    }
}

int pop(nod*& stack) {
    int n = -1;
    if (stack) {
        nod* first = stack;
        n = first->key;
        stack = stack->next;
        free(first);
    }
    return n;
}

void dfsVisit(graf &g, int key) {
    nod* stack;
    stack = NULL;
    push(stack, key);

    while (stack) {
        int v = pop(stack);
        if (g.color[v] == WHITE) {
            g.color[v] = GREY;
            printf("%d ", v);
            nod* t = g.t[v];
            while (t) {
                if (g.color[t->key] == WHITE) {
                    push(stack, t->key);
                    g.p[t->key] = v;
                }
                t = t->next;
            }
        }
    }
    printf("\n");
}

void dfs(graf &g) {
    for (int i = 0; i < g.n; i++) {
        if (g.color[i] == WHITE) {
            dfsVisit(g, i);
        }
    }
}

void init(graf &g) {
    in >> g.n;

    g.t = (nod**)malloc((g.n) * sizeof(nod*));
    g.p = (int*)malloc((g.n) * sizeof(int));
    g.color = (int*)malloc((g.n) * sizeof(int));

    for (int i = 0; i < g.n; i++) {
        g.p[i] = -1;
        g.color[i] = WHITE;
        g.t[i] = NULL;
    }

    int v;
    int w;
    while (in >> v >> w) {
        push(g.t[v], w);
        push(g.t[w], v);
    }
}

