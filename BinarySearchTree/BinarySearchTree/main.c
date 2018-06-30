#include <stdio.h>
#include "BinaryTree.h"

int main(int argc, char *argv[])
{
	int data[] = { 30, 70, 20, 50, 10, 60, 40, 90, 80, 1000 };
	int tree[2 << 6] = { 0, };

	int i;

	for (i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
		insert(tree, sizeof(tree) / sizeof(tree[0]), data[i]);
	}

	delete(tree, sizeof(tree) / sizeof(tree[0]), 70);
	insert(tree, sizeof(tree) / sizeof(tree[0]), 70); // 26
	delete(tree, sizeof(tree) / sizeof(tree[0]), 80);
	insert(tree, sizeof(tree) / sizeof(tree[0]), 80); // 54
	insert(tree, sizeof(tree) / sizeof(tree[0]), 35); // 23
	insert(tree, sizeof(tree) / sizeof(tree[0]), 45); // 24
	delete(tree, sizeof(tree) / sizeof(tree[0]), 80); // 54 deleted
	insert(tree, sizeof(tree) / sizeof(tree[0]), 5); // 7
	insert(tree, sizeof(tree) / sizeof(tree[0]), 3); // 15
	insert(tree, sizeof(tree) / sizeof(tree[0]), 1); // 31
	insert(tree, sizeof(tree) / sizeof(tree[0]), 15); // 8
	insert(tree, sizeof(tree) / sizeof(tree[0]), 13); // 17
	insert(tree, sizeof(tree) / sizeof(tree[0]), 17); // 18

	printf("Depth : %d\n", depth(tree, sizeof(tree) / sizeof(tree[0])));
	delete(tree, sizeof(tree) / sizeof(tree[0]), 20);
	printf("depth: %d\n", depth(tree, sizeof(tree) / sizeof(tree[0])));

	return 0;
}