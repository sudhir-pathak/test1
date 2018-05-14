#include <stdio.h>

void swap (int* src, int* dst)
{
	int t = *src;
	*src = *dst;
	*dst = t;
}

void swap1 (int* src, int* dst)
{
	*src += *dst;
	*dst = *src - *dst;
	*src = *src - *dst;
}

void merge (int low, int pivot, int high, int* arr)
{
	int start = low;
	int mid = pivot+1;

	while ((start <= pivot) && (mid <= high)) {

		if (arr[start] > arr[mid]) {
			swap (arr+start, arr+mid);
			mid++;
		} else {
			start++;
		}
	}
}

void mergeSort (int low, int high, int* arr)
{
	if (low < high) {

		int pivot = low + ((high-low)/2);
		mergeSort (low, pivot, arr);
		mergeSort (pivot+1, high, arr);

		merge (low, pivot, high, arr);
	}
}

void printArr (int* a, int len, const char* t)
{
	printf ("Array %s sorting: ", t);
	for (int i=0; i<len; i++) {
		printf ("%d ", a[i]);
	}
	puts (".");
}

int main (int argc, char* argv[])
{
	int a[] = {12, 2, 7, 3, 1};
	int len = sizeof (a)/sizeof (int);

	const char* t1="before";
	printArr (a, len, t1);

	mergeSort (0, len-1, a);

	const char* t2="after";
	printArr (a, len, t2);
}
