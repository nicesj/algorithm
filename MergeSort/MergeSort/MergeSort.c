#include <stdio.h>
#include "MergeSort.h"
#include "Common.h"

void merge_sort(int data[], int tmp[], int size)
{
	int i;
	int j;
	int si;
	int k;
	int slot_size;
	int last_slot;
	int *d;
	int *t;
	int *x;

	d = data;
	t = tmp;

	for (slot_size = 1; slot_size < size; slot_size <<= 1) {
		j = 0;
		k = 0;
		si = 0;
		last_slot = slot_size;
		while (si < size) {
			for (i = 0; i < (slot_size << 1) && si < size; i++) {
				if (j < last_slot && k < last_slot) {
					if (slot_size + k < size && d[j] > d[slot_size + k]) {
						t[si] = d[slot_size + k];
						k++;
					}
					else {
						t[si] = d[j];
						j++;
					}
				}
				else if (j < last_slot) {
					t[si] = d[j];
					j++;
				}
				else {
					t[si] = d[slot_size + k];
					k++;
				}
				si++;
			}
			j += slot_size;
			k += slot_size;
			last_slot += (slot_size << 1);
		}
		x = d;
		d = t;
		t = x;
	}
}