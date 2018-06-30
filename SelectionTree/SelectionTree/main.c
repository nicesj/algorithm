#include <stdio.h>
#include "SelectionTree.h"

int main(int argc, char *argv[])
{
	int runs[][10] = {
		{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
		{ 19, 29, 39, 49, 59, 69, 79, 89, 99, 109 },
		{ 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 },
		{ 18, 28, 38, 48, 58, 68, 78, 88, 98, 108 },
		{ 13, 23, 33, 43, 53, 63, 73, 83, 93, 103 }
	};
	int idx[5] = { 0, };
	int i;

	int selection_tree[16];
	int n = sizeof(selection_tree) / sizeof(selection_tree[0]);
	int selected_idx;

	for (i = 0; i < n; i++) selection_tree[i] = -1;

	selected_idx = climb_tree(runs, idx, selection_tree, n);

	do {
		printf("%d ", runs[selected_idx][idx[selected_idx] - 1]);

		for (i = 0; i < 5; i++) if (idx[i] < 10) break;

		selected_idx = climb_specific(runs, idx, selection_tree, n, ((n - 1) / 2) + selected_idx);
	} while (i < 5);
	printf("%s", "\n");
	getchar();

	return 0;
}