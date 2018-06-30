#include <stdio.h>
#include "BubbleSort.h"
#include "Common.h"

void bubble_sort(int data[], int size)
{
	int i;
	int j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (data[i] < data[j]) {
				swap(data + i, data + j);
			}
		}
	}
}