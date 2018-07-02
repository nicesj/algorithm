#include <stdio.h>
#include "BinarySearch.h"

int main(int argc, char *argv[])
{
	int data[] = { 0, 1, 2, 3, 4, 5, 7, 9, 10, 12, 1000 };

	int i;
	int idx;
	int j;

	for (j = i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
		idx = search(data, sizeof(data) / sizeof(data[0]), data[i]);
		if (idx != i) {
			printf("Mismatched: %d <> %d\n", idx, i);
			j++;
		}
	}

	printf("Not found: %d\n", search(data, sizeof(data) / sizeof(data[0]), -1));
	printf("Not found: %d\n", search(data, sizeof(data) / sizeof(data[0]), 2000));

	printf("Not found: %d\n", search(data, sizeof(data) / sizeof(data[0]), 500));

	if (j == 0) printf("Successfully worked\n");

	getchar();
	return 0;
}