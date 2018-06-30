#include <stdio.h>
#include "DistributionCounting.h"

void distribution_counting(int data[], int tmp[], int count[], int size)
{
	int i;
	int max;

	max = -1;
	for (i = 0; i < size; i++) {
		if (max < data[i]) {
			max = data[i];
			if (max >= size) {
				printf("Value is out of range");
				return;
			}
		}

		count[data[i]]++;
	}

	for (i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}

	// For the stability, pick a value from the end of an array.
	for (i = size - 1; i >= 0; i--) {
		tmp[--count[data[i]]] = data[i];
	}

	for (i = 0; i < size; i++) {
		data[i] = tmp[i];
	}
}