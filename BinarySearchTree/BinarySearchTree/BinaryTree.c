#include <stdio.h>

int insert(int tree[], int size, int v)
{
	int i = 0;
	int debug_count = 0;

	while (i < size) {
		debug_count++;
		if (tree[i] == 0) {
			tree[i] = v;
			break;
		}
		else if (tree[i] == v) {
			break;
		}
		else if (tree[i] < v) {
			i = (i + 1) * 2;
		}
		else if (tree[i] > v) {
			i = (i + 1) * 2 - 1;
		}
	}

	printf("To insert %d, run the loop %d times\n", v, debug_count);

	return (i < size && tree[i] == v) ? i : -1;
}

static inline int lift_node(int tree[], int p, int c)
{
	int r;
	int l;
	int rc;
	int lc;

	r = (p + 1) * 2;
	l = r - 1;

	rc = (c + 1) * 2;
	lc = rc - 1;

	tree[r] = tree[rc];
	tree[l] = tree[lc];

	if (tree[r] != 0) lift_node(tree, r, rc);
	if (tree[l] != 0) lift_node(tree, l, lc);

	return 0;
}

int delete(int tree[], int size, int v)
{
	int i = 0;
	int t;
	int r;

	i = search(tree, size, v);
	if (i == -1) return -1;

	t = (i + 1) * 2;

	if (tree[t] == 0) {
		if (tree[t - 1] == 0) {
			tree[i] = 0;
		}
		else {
			t--;
			tree[i] = tree[t];
			lift_node(tree, i, t);
		}
	}
	else {
		while (t < size) {
			if (tree[(t + 1) * 2 - 1] == 0) {
				tree[i] = tree[t];

				r = (t + 1) * 2;

				if (tree[r] != 0) {
					tree[t] = tree[r];

					lift_node(tree, t, r);
				}
				break;
			}

			t = (t + 1) * 2 - 1;
		}
	}

	return i;
}

int search(int tree[], int size, int v)
{
	int i = 0;
	int debug_count = 0;

	while (tree[i] != 0 && i < size) {
		debug_count++;
		if (tree[i] == v) {
			break;
		}
		else if (tree[i] < v) {
			i = (i + 1) * 2;
		}
		else if (tree[i] > v) {
			i = (i + 1) * 2 - 1;
		}
	}

	printf("To find %d, run the loop %d times\n", v, debug_count);

	return (tree[i] == 0) ? -1 : i;
}

int depth(int tree[], int size)
{
	int i;
	int depth = 0;
	for (i = size - 1; i > 0; i--) {
		if (tree[i] != 0) {
			i++;
			while ((i >>= 1) != 0) depth++;
			break;
		}
	}
	return depth + 1;
}