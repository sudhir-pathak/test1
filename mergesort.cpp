#include <stdio.h>



void merge (int* arr, int mid, int len)
{
printf ("merging the string of length <%d>\n", len);
	int* x = new int[len];

	for (int i=0, j=mid, k=0; k<len; k++) {
		if (j==len) {
			x[k] = arr[i];
			i++;
		} else if (i == mid) {
			x[k] = arr[j];
			j++;
		} else if (arr[j] < arr[i]) {
			x[k] = arr[j];
			j++;
		} else {
			x[k] = arr[i];
			i++;
		}
	}

	for (int i=0; i<len; i++) arr[i] = x[i];

	delete [] x;
}



void mergeSort (int* arr, int len)
{
	if (len > 1) {
		int mid = len/2;

		mergeSort (arr, mid);
		mergeSort (arr+mid, len-mid);

		merge (arr, mid, len);
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

	mergeSort (a, len);

	const char* t2="after";
	printArr (a, len, t2);
}
