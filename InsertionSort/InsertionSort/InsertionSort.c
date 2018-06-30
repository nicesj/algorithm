#include <stdio.h>
#include "InsertionSort.h"

void insertion_sort(int data[], int size)
{
	int i;
	int j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < i; j++) {
			if (data[i] < data[j]) {
				int tmp;
				int v;
				tmp = data[j];
				data[j] = data[i];
				while (j++ < i) {
					v = data[j];
					data[j] = tmp;
					tmp = v;
				}
			}
		}
	}
}