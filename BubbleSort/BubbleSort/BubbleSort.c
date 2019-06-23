#include <stdio.h>
#include "BubbleSort.h"
#include "Common.h"

void bubble_sort(int data[], int size)
{
	int i;
	int j;
	int temp;

	for (i = 0; i < size; i++) {
		for (j = i+1; j < size; j++) {
			if (data[i] < data[j]) {
				//swap(data + i, data + j);
				temp=data[i];
				data[i]=data[j];
				data[j]=temp;
			}
		}
	}
}
