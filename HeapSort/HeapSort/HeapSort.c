#include <stdio.h>
#include "Common.h"

static inline void upheap(int tree[], int node)
{
	int parent = (node - 1) >> 1;
	// int sibling = (node & 0x01) ? node + 1 : node - 1;
	while (parent >= 0 && (tree[parent] >= 0 && tree[parent] > tree[node]) == 0) {
		swap(tree + parent, tree + node);
		node = parent;
		parent = (node - 1) >> 1;
	}
}

static inline void downheap(int tree[])
{
	int parent = 0;
	int child = (parent + 1) << 1;
	int sibling = child - 1;

	while (1) {
		if (tree[child] > tree[sibling]) {
			if ((tree[parent] >= 0 && tree[parent] > tree[child]) == 0) {
				swap(tree + parent, tree + child);

				parent = child;
				child = (parent + 1) << 1;
				sibling = child - 1;
			}
			else break;
		}
		else {
			if ((tree[parent] >= 0 && tree[parent] > tree[sibling]) == 0) {
				swap(tree + parent, tree + sibling);

				parent = sibling;
				child = (parent + 1) << 1;
				sibling = child - 1;
			}
			else break;
		}
	}
}

void heap_sort(int data[], int size)
{
	int tree[1024] = { -1, };
	int i;
	int j;

	for (i = 0; i < sizeof(tree) / sizeof(tree[0]); i++) {
		tree[i] = -1;
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < sizeof(tree) / sizeof(tree[0]); j++) {
			if (tree[j] == -1) break;
		}

		tree[j] = data[i];

		if (j >= 1) upheap(tree, j);
	}

	int tree_size = size;

	for (i = 0; i < size; i++) {
		data[i] = tree[0];

		tree_size--;
		tree[0] = tree[tree_size];
		tree[tree_size] = -1;

		if (tree_size > 0) downheap(tree);
	}
}