#include <stdio.h>
#include <vector>
#include <string>
using namespace std;


void initfilenames (vector<string>& fn)
{
	fn.push_back("1.txt");
	fn.push_back("2.txt");
	fn.push_back("3.txt");
	fn.push_back("4.txt");
	fn.push_back("5.txt");
}

int readfromfile(FILE* f, int* d)
{
	size_t r = fscanf (f, "%d", d);
	if (r == 1) {
		printf ("Read <%d> from file\n", *d);
		return 0;
	} else {
		if (feof(f)) {
			printf ("Reached end of file\n");
			return -1;
		} else {
			printf ("Some other error reading the file\n");
			return -2;
		}
	}

	return -3;
}

int  minimum(vector<int>& data)
{
	int minIndex = 0;
	for (int i=1; i<data.size(); i++) {
		if (data[minIndex] > data[i]) {
			minIndex = i;
		} 
	}

	return minIndex;
}

int main (int argc, char* argv[])
{
	printf ("Merging files 1.txt - 5.txt\n");

	int files2read = 0;

	vector<string> fn;
	initfilenames (fn);

	vector<FILE*> fp;
	vector<int> data;	
	for (vector<string>::iterator it=fn.begin(); it != fn.end(); it++) {
		printf ("opening file <%s>\n", it->c_str());
		FILE* f = fopen (it->c_str(), "r");
		if (0 == f) {
			return -1;
		}
		int d;
		int r = readfromfile (f, &d);
		if (0 == r) {
			data.push_back (d);
			fp.push_back (f);
			files2read++;
		} else {
			fclose (f);
		}
	}

	FILE* ff = fopen ("mergedoutput.txt", "w");
	if (0 == ff) {
		return -1;
	}
	while (files2read > 0) {
		int min = minimum(data);

		fprintf(ff, "%d\n", data[min]);

		int d;
		int r = readfromfile (fp[min], &d);
		if (0 == r) {
			data[min] = d;
		} else {
			fclose (fp[min]);
			fp.erase (fp.begin()+min);
			data.erase (data.begin()+min);
			files2read--;
		}
	}

	fclose (ff);

	return 0;
}
