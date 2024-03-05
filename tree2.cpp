
#include <iostream>

using namespace std;

typedef struct node {
    int key;
    int count;
    node** children;
}node;

typedef struct node2 {
    int key;
    node2* left;
    node2* right;
}node2;

node* r1_to_r2(node** nodes, int* vect, int vectLength);
node2* r2_to_r3(node* root, node2* leftBrother);

void print_r1(int* vect, int vectLength, int key, int height);
void print_r2(node* root, int height);
void print_r3(node2* root2, int height);

void demo();

int main()
{
    demo();
}

void demo() {
    //             0  1  2  3  4  5   6  7  8
    int vect[] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
    int vectLength = 9;

    node** nodes = (node**)malloc(vectLength * sizeof(node*));
    node* root = r1_to_r2(nodes, vect, vectLength);

    node2* root2 = r2_to_r3(root, NULL);

    //print_r1(vect, vectLength, root->key, 0);
    //print_r2(root, 0);
    //print_r3(root2, 0);
}

void print_r1(int* vect, int vectLength, int key, int height) {

    for (int i = 0; i < height; i++) {
        printf("  ");
    }
    printf("%d\n", key);
    for (int i = 0; i < vectLength; i++) {
        if (vect[i] == key) {
            print_r1(vect, vectLength, i + 1, height + 1);
        }
    }
}

void print_r2(node* root, int height) {

    for (int i = 0; i < height; i++) {
        printf("  ");
    }
    printf("%d\n", root->key);
    for (int i = 0; i < root->count; i++) {
        print_r2(root->children[i], height + 1);
    }
}

void print_r3(node2* root2, int height) {

    if (root2 == NULL) {
        return;
    }

    for (int i = 0; i < height; i++) {
        printf("  ");
    }

    printf("%d\n", root2->key);

    print_r3(root2->left, height + 1);
    print_r3(root2->right, height);
}

node* r1_to_r2(node** nodes, int* vect, int vectLength) {

    node* root = NULL;

    for (int i = 0; i < vectLength; i++) {
        nodes[i] = (node*)malloc(sizeof(node));
        nodes[i]->key = i + 1;
        nodes[i]->count = 0;
        //printf("%d ", nodes[i]->key);
    }

    for (int i = 0; i < vectLength; i++) {
        if (vect[i] != -1) {
            (nodes[vect[i] - 1]->count)++;
        }
        else {
            root = nodes[i];
        }
    }

    for (int i = 0; i < vectLength; i++) {
        if (nodes[i]->count > 0) {
            nodes[i]->children = (node**)malloc((nodes[i]->count) * sizeof(node*));
            for (int j = 0; j < nodes[i]->count; j++) {
                nodes[i]->children[j] = 0;
            }
            nodes[i]->count = 0;
        }
    }

    for (int i = 0; i < vectLength; i++) {
        if (vect[i] != -1) {
            node* child = nodes[i];
            node* parent = nodes[vect[i] - 1];
            parent->children[(parent->count)++] = child;
        }
    }

    return root;
}

node2* r2_to_r3(node* root, node2* leftBrother) {

    node2* root2 = (node2*)malloc(1 * sizeof(node2));
    root2->key = root->key;
    root2->left = root2->right = NULL;

    if (leftBrother != NULL) {
        leftBrother->right = root2;
    }

    node2* c = NULL;

    for (int i = 0; i < root->count; i++) {
        c = r2_to_r3(root->children[i], c);
        if (i == 0) {
            root2->left = c;
        }
    }
    return root2;
}