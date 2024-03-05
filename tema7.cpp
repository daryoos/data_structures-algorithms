#include <iostream>
#include <cstdlib>
#include "Profiler.h"

using namespace std;

Profiler tema7("tema7");
Profiler test("test");

typedef struct node {
	int key;
	int size;
	node* left;
	node* right;
	node* parent;
}node;

void averageCase();

void printTree(node* root, int height);
void demo();

node* buildTree(int a, int b);
node* osSelect(node* root, int k, Operation& comp, Operation& atr);
node* minValueNode(node* root, Operation& comp, Operation& atr);
node* osDelete(node* root, int key, Operation& comp, Operation& atr);

int main()
{
	//averageCase();
	demo();
}

void averageCase()
{
	int NR_TEST = 5;

	for (int n = 100; n <= 10000; n += 100)
	{
		Operation scomp = tema7.createOperation("select_comp", n);
		Operation satr = tema7.createOperation("select_atr", n);

		Operation dcomp = tema7.createOperation("delete_comp", n);
		Operation datr = tema7.createOperation("delete_atr", n);

		for (int i = 0; i < NR_TEST; i++)
		{
			node* root = buildTree(1, n);
			int size = n;
			while(size != 0)
			{
				int k = rand() % size;
				size--;
				node* aux = osSelect(root, k, scomp, satr);
				if(aux != NULL)
					root = osDelete(root, aux->key, dcomp, datr);
			}
		}	
	}

	tema7.divideValues("select_comp", NR_TEST);
	tema7.divideValues("select_atr", NR_TEST);
	tema7.divideValues("delete_comp", NR_TEST);
	tema7.divideValues("delete_atr", NR_TEST);
	tema7.addSeries("select_total", "select_comp", "select_atr");
	tema7.addSeries("delete_total", "delete_comp", "delete_atr");
	tema7.createGroup("select", "select_total", "select_comp", "select_atr");
	tema7.createGroup("delete", "delete_total", "delete_comp", "delete_atr");

	tema7.reset();
}



void demo()
{
	int n = 11;

	Operation comp = test.createOperation("demo1", n);
	Operation atr = test.createOperation("demo2", n);

	int k = 3;
	int key = 6;

	node* root = buildTree(1, n);
	printTree(root, 0);

	printf("\n");

	root = osDelete(root, key, comp, atr);
	printTree(root, 0);

	node* aux = osSelect(root, k, comp, atr);
	printf("\n%d\n", aux->key);
}

void printTree(node* root, int height)
{
	if (root == NULL) {
		return;
	}

	for (int i = 0; i < height; i++) {
		printf("  ");
	}

	printf("%d\n", root->key);

	printTree(root->left, height + 1);
	printTree(root->right, height + 1);
}

node* osDelete(node* root, int key, Operation& comp, Operation& atr)
{
	comp.count();
	if (root == NULL) {
		return root;
	}

	comp.count();
	if (key < root->key) {
		atr.count();
		root->left = osDelete(root->left, key, comp, atr);
	}

	else
	{
		comp.count();
		if (key > root->key)
		{
			atr.count();
			root->right = osDelete(root->right, key, comp, atr);
		}
		else {
			comp.count(2);
			if (root->left == NULL and root->right == NULL) {
				return NULL;
			}

			else
			{
				comp.count();
				if (root->left == NULL)
				{
					atr.count();
					node* temp = root->right;
					free(root);
					return temp;
				}
				else
				{
					comp.count();
					if (root->right == NULL)
					{
						atr.count();
						node* temp = root->left;
						free(root);
						return temp;
					}
				}
			}
			node* aux = minValueNode(root->right, comp, atr);

			atr.count(2);
			root->key = aux->key;

			root->right = osDelete(root->right, aux->key, comp, atr);
		}
	}

	return root;
}

node* minValueNode(node* root, Operation& comp, Operation& atr)
{
	atr.count();
	node* aux = root;

	comp.count(2);
	while (aux && aux->left != NULL) {
		atr.count();
		aux = aux->left;
	}

	return aux;
}

node* osSelect(node* root, int k, Operation& comp, Operation& atr)
{
	int r;
	comp.count();
	if (root == NULL)
	{
		return NULL;
	}
	comp.count();
	if (root->left == NULL)
	{
		r = 1;
	}
	else
	{
		atr.count();
		r = root->left->size + 1;
	}
	if (k == r)
	{
		return root;
	}
	else
	{
		if (k < r)
		{
			return osSelect(root->left, k, comp, atr);
		}
		else
		{
			return osSelect(root->right, k - r, comp, atr);
		}
	}
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
		root->size = 1;

		root->left = buildTree(a, root->key - 1);
		root->right = buildTree(root->key + 1, b);

		if (root->left != NULL)
		{
			root->left->parent = root;
			root->size += root->left->size;
		}
		if (root->right != NULL)
		{
			root->right->parent = root;
			root->size += root->right->size;
		}

		return root;
	}
}
