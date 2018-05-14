#include <stdio.h>

void swap (int* src, int* dst)
{
	*src += *dst;
	*dst = *src - *dst;
	*src = *src - *dst;
}

void quickSort (int* arr, int len)
{
	if (len > 1) {
		int pivot = arr[len/2];

		int i=0, j=len-1;
		while (i<j) {

			while (arr[i] < pivot && i < len) i++;
			while (pivot < arr[j] && j > 0) j--;

			if (i < j) swap (arr+i, arr+j);
		}

		quickSort (arr, i);
		quickSort (arr+i, len-i);
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
	int a[] = {12, 2, 7, 0, 3, 1};
	int len = sizeof (a)/sizeof (int);

	const char* t1="before";
	printArr (a, len, t1);

	quickSort (a, len);

	const char* t2="after";
	printArr (a, len, t2);
}
