#include <stdio.h>
#include "Common.h"

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int get_bits(int value, int offset, int nr_of_bits)
{
	return (value >> offset) & ~(~0 << nr_of_bits);
}