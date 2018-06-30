#include <stdio.h>
#include "SelectionSort.h"

int main(int argc, char *argv[])
{
	int data[][11] = {
		{ 9, 4, 3, 5, 8, 7, 1, 0, 4, 2, 6 },
	};

	selection_sort(data[0], sizeof(data[0]) / sizeof(int));

	int i;
	int j;

	for (j = 0; j < sizeof(data) / sizeof(data[0]); j++) {
		for (i = 0; i < sizeof(data[j]) / sizeof(int); i++) {
			printf("%d ", data[j][i]);
		}
		printf("\n");
	}

	getchar();
	return 0;
}
