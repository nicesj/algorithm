#include <stdio.h>
#include "Common.h"
#include "SelectionSort.h"

void selection_sort(int data[], int size)
{
	int i;
	int j;

	for (i = 0; i < size; i++) {
		for (j = i + 1; j < size; j++) {
			if (data[j] < data[i]) {
				swap(data + j, data + i);
			}
		}
	}
}