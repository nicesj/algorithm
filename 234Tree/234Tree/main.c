#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#include "234Tree.h"
static void build_test_set(int *set, int count_of_set, int size_of_set)
{
	int i;
	int j;
	int k;

	for (j = 0; j < count_of_set; j++) {
		for (i = 0; i < size_of_set; i++) {
			set[j * size_of_set + i] = rand() % 1000;
			for (k = 0; k < i; k++) {
				if (set[j * size_of_set + k] == set[j * size_of_set + i]) {
					i--;
					break;
				}
			}
		}

		for (k = 0; k < j; k++) {
			for (i = 0; i < size_of_set; i++) {
				if (set[k * size_of_set + i] != set[j * size_of_set + i]) break;
			}
			if (i == size_of_set) {
				printf("Try to find a test set again %d/%d\n", j, size_of_set);
				j--; // Try again
				break;
			}
		}
	}
}

static inline void store_data(const char *filename, int *data, int size)
{
	FILE *fp;
	fopen_s(&fp, filename, "w+t");
	if (fp) {
		fwrite(data, 1, size, fp);
		fclose(fp);
	}
}

static inline void load_data(const char *filename, int *data, int size)
{
	FILE *fp;
	fopen_s(&fp, filename, "rt");
	if (fp) {
		fread(data, 1, size, fp);
		fclose(fp);
	}
}

int main(int argc, char *argv[])
{
	struct tree_node *root = NULL;

	// 16 * 16 + 2 * 16 + 14
	// 256 + 32 + 12 = 288 + 12 = 300
	// 26
	int test_set[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 35, 37, 75, 77, 250, 300, 15, 34, 38, 55, 74, 78, 95, 225, 310 };
	int i;

	for (i = 0; i < sizeof(test_set) / sizeof(test_set[0]); i++) {
		printf("=> Insert %d\n", test_set[i]);
		//scanf_s("%d", test_set + i);
		tree_insert(&root, test_set[i]);
		if (tree_validate(root) < 0)
			printf("Invalid tree\n");
		tree_dump(root);
	}

	struct tree_node *node;
	node = tree_search(root, 0x0A);

	for (i = 0; i < sizeof(test_set) / sizeof(test_set[0]); i++) {
		printf("=> Delete %X\n", test_set[i]);
		tree_remove(&root, test_set[i]);
		tree_dump(root);
		if (tree_validate(root) < 0)
			printf(">>>>> Exception. Tree structure is invalid.\n");
		else printf("OKAY - Valid tree\n");
	}

	int tc;
	int del_tc;
	int insert_set[100][1000];
	int delete_set[100][1000];
	int k;
	int j;

	srand((unsigned int)time(NULL));

	int loaded = 0;
	struct stat st;
	if (stat("insert.data", &st) == 0) {
		if ((st.st_mode & S_IFREG) == S_IFREG) {
			load_data("insert.data", (int *)insert_set, sizeof(insert_set));
			loaded = 1;
		}
	}

	if (loaded == 0) {
		build_test_set((int *)insert_set, sizeof(insert_set) / sizeof(insert_set[0]), sizeof(insert_set[0]) / sizeof(insert_set[0][0]));
	}

	loaded = 0;
	if (stat("delete.data", &st) == 0) {
		if ((st.st_mode & S_IFREG) == S_IFREG) {
			load_data("delete.data", (int *)delete_set, sizeof(delete_set));
			loaded = 1;
		}
	}

	for (tc = 0; tc < sizeof(insert_set) / sizeof(insert_set[0]); tc++) {
		for (del_tc = 0; del_tc < sizeof(delete_set) / sizeof(delete_set[0]); del_tc++) {
			for (i = 0; i < sizeof(insert_set[0]) / sizeof(insert_set[0][0]); i++) {
				printf("Insert %X\r", insert_set[tc][i]);
				tree_insert(&root, insert_set[tc][i]);
				if (tree_validate(root) < 0) {
					tree_dump(root);
					printf("Invalid tree\n");
					store_data("insert.data", (int *)insert_set, sizeof(insert_set));
					getchar();
					return -1;
				}

				for (k = 0; k <= i; k++) {
					if (tree_search(root, insert_set[tc][k]) == NULL) {
						tree_dump(root);
						printf("Inserted value %X is not found\n", insert_set[tc][k]);
						store_data("insert.data", (int *)insert_set, sizeof(insert_set));
						getchar();
						return -1;
					}
				}
			}
			printf("\n%d test cases are passed\n", i);

			if (loaded == 0) {
				do {
					for (i = 0; i < sizeof(delete_set[0]) / sizeof(delete_set[0][0]); i++) {
						k = rand() % (sizeof(delete_set[0]) / sizeof(delete_set[0][0]));
						delete_set[del_tc][i] = insert_set[tc][k];

						for (j = 0; j < i; j++) {
							if (delete_set[del_tc][j] == insert_set[tc][k]) {
								i--;
								break;
							}
						}
					}

					for (i = 0; i < del_tc; i++) {
						for (j = 0; j < sizeof(delete_set[0]) / sizeof(delete_set[0][0]); j++) {
							if (delete_set[i][j] != delete_set[del_tc][j]) break;
						}

						if (j == (sizeof(delete_set[0]) / sizeof(delete_set[0][0]))) break;
					}
				} while (i != del_tc);
			}

			for (i = 0; i < sizeof(delete_set[0]) / sizeof(delete_set[0][0]); i++) {
				printf("Delete %X\r", delete_set[del_tc][i]);
				tree_remove(&root, delete_set[del_tc][i]);
				if (tree_validate(root) < 0) {
					tree_dump(root);
					printf("Invalid tree\n");

					store_data("insert.data", (int *)insert_set, sizeof(insert_set));
					store_data("delete.data", (int *)delete_set, sizeof(delete_set));
					getchar();
					return -1;
				}

				for (k = 0; k <= i; k++) {
					if (tree_search(root, delete_set[del_tc][k]) != NULL) {
						tree_dump(root);
						printf("Deleted value %X is found\n", delete_set[del_tc][k]);
						store_data("insert.data", (int *)insert_set, sizeof(insert_set));
						store_data("delete.data", (int *)delete_set, sizeof(delete_set));
						getchar();
						return -1;
					}
				}

				for (k = i + 1; k < sizeof(delete_set[0]) / sizeof(delete_set[0][0]); k++) {
					if (tree_search(root, delete_set[del_tc][k]) == NULL) {
						tree_dump(root);
						printf("Inserted value %X is not found after deletion\n", delete_set[del_tc][k]);
						store_data("insert.data", (int *)insert_set, sizeof(insert_set));
						store_data("delete.data", (int *)delete_set, sizeof(delete_set));
						getchar();
						return -1;
					}
				}
			}

			printf("\n%d test cases are passed\n", i);
		}
	}

	getchar();
	return 0;
}