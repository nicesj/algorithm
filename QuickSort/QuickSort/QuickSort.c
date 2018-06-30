#include <stdio.h>
#include "QuickSort.h"
#include "Common.h"

void quick_sort_r(int *data, int size)
{
	if (size <= 1) return;

	int tmp = size / 2;

	if (data[0] > data[tmp]) {
		swap(data + 0, data + tmp);
	}

	if (data[tmp] > data[size - 1]) {
		swap(data + tmp, data + size - 1);
	}

	if (data[0] > data[tmp]) {
		swap(data + 0, data + tmp);
	}

	swap(data + tmp, data + size - 1);

	tmp = size - 1;

	int i = -1;
	int j = size - 1;
	int v = data[tmp];

	while (i < j) {
		while (data[++i] < v);
		while (data[--j] > v);
		if (i < j) swap(data + i, data + j);
	}

	swap(data + i, data + tmp);

	quick_sort_r(data, i);
	quick_sort_r(data + i + 1, size - i - 1);
}