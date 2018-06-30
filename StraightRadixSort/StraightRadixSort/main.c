#include <stdio.h>
#include "StraightRadixSort.h"

int main(int argc, char *argv[])
{
	int data[][12] = {
		{ 1, 5, 1, 6, 3, 7, 8, 2, 8, 0, 9, 4 },
	{ 0, }
	};

	straight_radix_sort(data[0], data[1], sizeof(data[0]) / sizeof(data[0][0]));

	int i;
	for (i = 0; i < sizeof(data[0]) / sizeof(data[0][0]); i++) {
		printf("%d ", data[0][i]);
	}
	printf("\n");
	getchar();

	return 0;
}