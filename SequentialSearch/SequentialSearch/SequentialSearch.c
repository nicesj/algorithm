#include <stdio.h>

int search(int data[], int size, int v)
{
	int i;

	for (i = 0; i < size; i++) {
		if (data[i] == -1) continue;
		else if (data[i] == v) {
			if (i > 0) {
				int tmp;
				int j;

				tmp = data[i];
				for (j = i; j > 0; j--) {
					data[j] = data[j - 1];
				}
				data[0] = tmp;
			}
			return 0;
		}
	}

	return -1;
}

int insert(int data[], int *size, int v)
{
	int i;
	for (i = 0; i < *size; i++) {
		if (data[i] == -1) {
			data[i] = v;
			return i;
		}
	}

	data[i] = v;
	(*size)++;
	return i;
}

int delete(int data[], int *size, int v)
{
	int i;
	for (i = 0; i < *size; i++) {
		if (data[i] == v) {
			data[i] = -1;
			return i;
		}
	}

	return -1;
}