#include <stdlib.h>
#include <string.h>
#include "bfs.h"
#include <queue>
#include <random>
using namespace std;

int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4

    int k = 0;

    if (p.row - 1 >= 0 && p.col >= 0 &&  grid->mat[p.row - 1][p.col] != 1) {
        neighb[k].row = p.row - 1;
        neighb[k++].col = p.col;
    }

    if (p.row >= 0 && p.col - 1 >= 0 && grid->mat[p.row][p.col - 1] != 1) {
        neighb[k].row = p.row;
        neighb[k++].col = p.col - 1;
    }

    if (p.row >= 0 && p.col + 1 >= 0 && grid->mat[p.row][p.col + 1] != 1) {
        neighb[k].row = p.row;
        neighb[k++].col = p.col + 1;
    }
    
    if (p.row + 1 >= 0 && p.col >= 0 && grid->mat[p.row + 1][p.col] != 1) {
        neighb[k].row = p.row + 1;
        neighb[k++].col = p.col;
    }

    return k;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void bfs(Graph *graph, Node *s, Operation *op)
{
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();

    if (op != NULL) {
        op->count(4);
    }

    s->dist = 0;
    s->parent = NULL;
    s->color = 1;
    
    queue<Node*> queue;

    queue.push(s);

    while (!queue.empty()) {

        Node* aux = queue.front();
        queue.pop();

        if (op != NULL) {
            op->count(2);
        }

        for (int i = 0; i < aux->adjSize; i++) {

            if (aux->adj[i]->color == 0) {

                aux->adj[i]->dist = aux->dist + 1;
                aux->adj[i]->parent = aux;
                aux->adj[i]->color = 1;

                queue.push(aux->adj[i]);

                if (op != NULL) {
                    op->count(4);
                }
            }
            if (op != NULL) {
                op->count();
            }
        }

        aux->color = 2;

        if (op != NULL) {
            op->count();
        }
    }
}

void pretty_print(int *p, int n, Point *repr, int k, int height) {

    for (int i = 0; i < height; i++) {
        printf("    ");
    }
    printf("(%d, %d)\n", repr[k].row, repr[k].col);
    for (int i = 0; i < n; i++) {
        if (p[i] == k) {
            pretty_print(p, n, repr, i, height + 1);
        }
    }
}

void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if(!err){
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs

        int k;
        for (k = 0; k < graph->nrNodes; k++) {
            if (p[k] == -1) {
                break;
            }
        }

        pretty_print(p, n, repr, k, 0);
    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000
    return -1;
}


void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for(n=1000; n<=4500; n+=100){
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){

            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));

            graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
            for (int j = 0; j < graph.nrNodes; j++) {
                graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
            }
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected

        int muchie[201][201] = { 0 };
        for (int i = 0; i < graph.nrNodes; i++) {
            muchie[0][i] = 1;
            graph.v[0]->adj[graph.v[0]->adjSize++] = graph.v[i];
            graph.v[i]->adj[graph.v[i]->adjSize++] = graph.v[0];
        }
        for (int i = graph.nrNodes; i <= n; i++) {              
            int k1 = rand() % (graph.nrNodes - 1) + 1;
            int k2 = rand() % (graph.nrNodes - 1) + 1;
            while (k1 == k2) {
                k2 = rand() % (graph.nrNodes - 1) + 1;
            }
            while (muchie[k1][k2] == 1) {
                k1 = rand() % (graph.nrNodes - 1) + 1;
                k2 = rand() % (graph.nrNodes - 1) + 1;
            }
            graph.v[k1]->adj[graph.v[k1]->adjSize++] = graph.v[k2];
            graph.v[k2]->adj[graph.v[k2]->adjSize++] = graph.v[k1];
        }

        bfs(&graph, graph.v[0], &op);
        //free_graph(&graph);
    }

    // vary the number of vertices
    for(n=100; n<=200; n+=10){
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));

            graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
            for (int j = 0; j < graph.nrNodes; j++) {
                graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
            }
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected

        int muchie[201][201] = { 0 };
        for (int i = 0; i < graph.nrNodes; i++) {
            muchie[0][i] = 1;
            graph.v[0]->adj[graph.v[0]->adjSize++] = graph.v[i];
            graph.v[i]->adj[graph.v[i]->adjSize++] = graph.v[0];
        }
        for (int i = graph.nrNodes; i <= 4500; i++) {
            int k1 = rand() % (graph.nrNodes - 1) + 1;
            int k2 = rand() % (graph.nrNodes - 1) + 1;
            while (k1 == k2) {
                k2 = rand() % (graph.nrNodes - 1) + 1;
            }
            while (muchie[k1][k2] == 1) {
                k1 = rand() % (graph.nrNodes - 1) + 1;
                k2 = rand() % (graph.nrNodes - 1) + 1;
            }
            graph.v[k1]->adj[graph.v[k1]->adjSize++] = graph.v[k2];
            graph.v[k2]->adj[graph.v[k2]->adjSize++] = graph.v[k1];
        }

        bfs(&graph, graph.v[0], &op);
        //free_graph(&graph);
    }

    p.showReport();
}
