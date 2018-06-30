#include <stdio.h>
#include "SequentialSearch.h"

int main(int argc, char *argv[])
{
	int data[] = { 3, 5, 1, 2, 7, 9, 6, 4, 0, 8 };
	int size = 10;
	int idx;

	idx = search(data, size, 3);
	printf("found at %d\n", idx);

	idx = delete(data, &size, 3);
	printf("deleted %d: %d\n", idx, data[idx]);

	idx = insert(data, &size, 100);
	printf("inserted at %d: %d\n", idx, data[idx]);

	idx = search(data, size, 100);
	printf("found at %d: %d\n", idx, data[idx]);

	getchar();
	return 0;
}