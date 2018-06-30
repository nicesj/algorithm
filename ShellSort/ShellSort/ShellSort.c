#include <stdio.h>

void shell_sort(int data[], int size)
{
	int h;

	// Robert Sedgewick
	for (h = 1; h < size; h = 3 * h + 1);

	int i;
	int j;
	int k;

	// (h - 1) / 3 = h / 3 - 1 / 3 = h / 3
	for (h /= 3; h > 0; h /= 3) {
		for (k = 0; k < h; k++) {
			for (i = k; i < size; i += h) {
				for (j = k; j < i; j += h) {
					if (data[i] < data[j]) {
						int tmp;
						int v;
						tmp = data[j];
						data[j] = data[i];
						while (j < i) {
							j += h;
							v = data[j];
							data[j] = tmp;
							tmp = v;
						}
					}
				}
			}
		}
	}
}