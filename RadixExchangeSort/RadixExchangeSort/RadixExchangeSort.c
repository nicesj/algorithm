#include <stdio.h>
#include "Common.h"
#include "RadixExchangeSort.h"

void radix_sort(int data[], int size, int b)
{
	int i = 0;
	int j = size - 1;

	if (b < 0 || size <= 0) return;

	while (i < j) {
		while (get_bits(data[i], b, 1) == 0 && i < j) i++;
		while (get_bits(data[j], b, 1) == 1 && i < j) j--;
		if (i < j) swap(data + i, data + j);
	}

	if (get_bits(data[size - 1], b, 1) == 0) j++;

	radix_sort(data, j, b - 1);
	radix_sort(data + j, size - j, b - 1);
}