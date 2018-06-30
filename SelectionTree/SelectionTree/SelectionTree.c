#include <stdio.h>

static inline int get_value(int runs[][10], int idx[], int x)
{
	if (x >= 5 || x < 0) return 0x7FFFFFFF;
	if (idx[x] > 9) return 0x7FFFFFFF;

	return runs[x][idx[x]];
}

int climb_tree(int runs[][10], int idx[], int tree[], int size)
{
	int i;

	size--;
	for (i = size / 2; i < size; i++) {
		tree[i] = i - size / 2;
	}

	while (size > 1) {
		for (i = size / 2; i < size; i += 2) {
			tree[i / 2] = get_value(runs, idx, tree[i]) < get_value(runs, idx, tree[i + 1]) ? tree[i] : tree[i + 1];
		}
		size = size / 2;
	}

	idx[tree[0]]++;
	return tree[0];
}

int climb_specific(int runs[][10], int idx[], int tree[], int size, int x)
{
	int sibling;

	while (x > 0) {
		sibling = ~(x ^ ~0x01);     // ~(0011 ^ 1110) = ~1101 = 0010
		tree[x / 2] = get_value(runs, idx, tree[x]) < get_value(runs, idx, tree[sibling]) ? tree[x] : tree[sibling];
		x /= 2;
	}

	idx[tree[0]]++;
	return tree[0];
}