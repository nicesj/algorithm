#include <stdio.h>
#include "RadixExchangeSort.h"

int main(int argc, char *argv[])
{
	int data[] = { 1, 2, 5, 1, 5, 6, 4, 8, 9, 1, 4, 7, 3, 8, 1, 5, 0 };

	radix_sort(data, sizeof(data) / sizeof(data[0]), 7);

	int i;
	for (i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
	getchar();

	return 0;
}