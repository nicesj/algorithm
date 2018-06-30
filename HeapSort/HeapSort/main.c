#include <stdio.h>
#include "HeapSort.h"

int main(int argc, char *argv[])
{
	int data[] = { 4, 7, 1, 3, 9, 5, 8, 2, 6, 0 };
	heap_sort(data, sizeof(data) / sizeof(data[0]));
	int i;
	for (i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
	getchar();
	return 0;
}