#include <stdio.h>

int search(int data[], int size, int v)
{
	int begin;
	int end;
	int mid;
	int debug_count = 0;

	begin = 0;
	end = size;

	while (begin < end) {
		mid = (begin + end) >> 1;
		debug_count++;
		if (data[mid] == v) {
			break;
		}
		else if (data[mid] < v) {
			begin = mid + 1;
		}
		else {
			end = mid;
		}
	}

	printf("To find %d, runs %d times loop\n", v, debug_count);

	return begin < end ? mid : -1;
}

int insert(int data[], int *size, int v)
{
	int i;

	for (i = 0; i < *size; i++) {
		if (v < data[i]) {
			int j;
			(*size)++;
			for (j = *size; j > i; j--) {
				data[j] = data[j - 1];
			}
			data[i] = v;
			return i;
		}
	}

	*size = i;
	data[i] = v;
	return i;
}

int delete(int data[], int *size, int v)
{
	int i;
	int idx;

	idx = search(data, *size, v);
	if (idx < 0) return -1;

	(*size)--;
	for (i = idx; i < *size; i++) {
		data[i] = data[i + 1];
	}

	data[i] = v;
	(*size)++;
	return i;
}