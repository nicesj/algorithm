#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "AVLTree.h"

// Weird case
//                       11
//           4                        14
//     2            8          13             15
//  0           6      10
//                7
// subtree 11 rotation required (right)
// subtree 4 rotation required (left)
// subtree 8 rotation required (right)
// subtree 6 rotation required (left)
/*
Remove 6 (avl-62714835.png)
6
2				7
1		4				8
3   5
*/

int main(int argc, char *argv[])
{
	int k;
	int sample_set[16];
	int i;
	int j;
	int value;
	int sample_set_size = sizeof(sample_set) / sizeof(sample_set[0]);
	struct tree_node *root = NULL;

	srand((unsigned int)time(NULL));

	for (k = 0; k < 1000; k++) {
		for (i = 0; i < sample_set_size; i++) {
			do {
				value = rand() % sample_set_size;
				for (j = 0; j < i; j++) {
					if (sample_set[j] == value) break;
				}
			} while (j < i);

			sample_set[i] = value;
		}

		printf("Root node: %X\n", sample_set[0]);
		for (i = 0; i < sample_set_size; i++) {
			printf("Insert %X\n", sample_set[i]);
			tree_insert(&root, sample_set[i]);
		}

		for (i = 0; i < sample_set_size; i++) {
			do {
				value = rand() % sample_set_size;
				for (j = 0; j < i; j++) {
					if (sample_set[j] == value) break;
				}
			} while (j < i);

			sample_set[i] = value;
		}
		for (i = 0; i < sample_set_size; i++) {
			printf("Remove %X\n", sample_set[i]);
			tree_remove(&root, sample_set[i]);
		}
	}

	getchar();
	return 0;
}