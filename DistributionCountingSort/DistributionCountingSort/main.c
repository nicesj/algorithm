#include <stdio.h>
#include "DistributionCounting.h"

int main(int argc, char *argv[])
{
	int data[][20] = {
		{ 1, 3, 2, 1, 5, 1, 2, 4, 4, 3, 1, 5, 4, 2, 2, 1, 4, 2, 5, 1 },
		{ 0, },
		{ 0, },
	};

	distribution_counting(data[0], data[1], data[2], sizeof(data[0]) / sizeof(data[0][0]));

	int i;
	for (i = 0; i < sizeof(data[0]) / sizeof(data[0][0]); i++) {
		printf("%d ", data[0][i]);
	}
	printf("\n");
	getchar();
	return 0;
}