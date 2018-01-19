#include <stdio.h>
#include <stdlib.h>

/***
Expected output
37  36  35  34  33  32  31
38  17  16  15  14  13  30
39  18   5   4   3  12  29
40  19   6   1   2  11  28
41  20   7   8   9  10  27
42  21  22  23  24  25  26
43  44  45  46  47  48  49
***/
const int UP=1;
const int DOWN=2;
const int LEFT=3;
const int RIGHT=4;

void BuildMatrix (const unsigned int n, unsigned int*  m[])
{
	int k = n*n;	// Start from max and keep going until 1

	int r_min=0, r_max=n-1, c_min=0, c_max=n-1; // min/max row & colums

	//for even numbers start at right bottom corner
	//and for odd numbers start at top left corner
	int o=n%2;
	int direction = (o) ? LEFT : RIGHT;

	while (k > 0) {
		if (direction == LEFT) {
			for (int i=c_max; i>=c_min; i--) m[r_max][i] = k--;
			direction=UP;
		}

		if (direction == UP) {
			for (int i=r_max-1; i>=r_min+1; i--) m[i][c_min] = k--;
			direction=RIGHT;
			if (!o) {
				c_min++;
				c_max--;
				r_min++;
				r_max--;
			}
		}

		if (direction == RIGHT) {
			for (int i=c_min; i<=c_max; i++) m[r_min][i] = k--;
			direction=DOWN;
		}

		if (direction == DOWN) {
			for (int i=r_min+1; i<=r_max-1; i++) m[i][c_max] = k--;
			direction=LEFT;
			if (o) {
				c_min++;
				c_max--;
				r_min++;
				r_max--;
			}
		}
	}

	if (o) m[r_min-1][c_min-1] = 1;
}

void PrintMatrix (const unsigned int n, unsigned int* m[])
{
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			printf ("%2d ", m[i][j]);
		}
		printf ("\n");
	}
}

int main (int argc, char* argv[])
{
	if (2 != argc) {
		printf ("Usage: %s <%s>\n", argv[0], " <N=size of spiral matrix>");
	} else {
		const unsigned int n = atoi (argv[1]);
		printf ("Building the matrix of size %d\n", n);

		unsigned int*  m[n];
		for (int i=0; i<n; i++) {
			m[i] = new unsigned int [n];
		}

		BuildMatrix (n, m);
		PrintMatrix (n, m);

		for (int i=0; i<n; i++) {
			delete [] m[i];
		}
	}

	return 0;
}
