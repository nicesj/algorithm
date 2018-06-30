#include <stdio.h>
#include "MergeSort.h"

int main(int argc, char *argv[])
{
	int data[][10] = {
		{ 1, 4, 2, 5, 9, 0, 8, 7, 6, 3 },
	{ 0, }
	};

	merge_sort(data[0], data[1], sizeof(data[0]) / sizeof(data[0][0]));

	int i;
	for (i = 0; i < sizeof(data[0]) / sizeof(data[0][0]); i++) {
		printf("%d ", data[0][i]);
	}
	printf("\n");
	getchar();

	return 0;
}