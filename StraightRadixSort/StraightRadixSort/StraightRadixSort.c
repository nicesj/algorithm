#include <stdio.h>
#include "Common.h"
#include "StraightRadixSort.h"

void straight_radix_sort(int data[], int tmp[], int size)
{
	int count[2]; // Binary value: 0 or 1
	int i; // iterator
	int b; // bit offset
	int countOfBit;

	countOfBit = sizeof(data[0]) << 3;
	// Start the sorting from the LSB
	for (b = 0; b < countOfBit; b++) {

		count[0] = 0;
		count[1] = 0;

		for (i = 0; i < size; i++) count[get_bits(data[i], b, 1)]++;

		// accumulating the counts
		count[1] = count[0] + count[1];

		for (i = size - 1; i >= 0; i--) {
			tmp[--count[get_bits(data[i], b, 1)]] = data[i];
		}

		for (i = 0; i < size; i++) {
			data[i] = tmp[i];
		}
	}
}