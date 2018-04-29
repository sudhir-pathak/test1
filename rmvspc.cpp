#include <iostream>
using namespace std;

void removetrailingspaces (char* str)
{
	char* c = str+strlen (str)-1;


	while (c > str && *c == ' ')  c--;


	*(c+1) = '\0';
}

void removespaces (char* str)
{
	char* s = str;
	char* c = str;
	char* e = s;
	int i = 0;
	while (i < strlen (str)) {
		while (*s == ' ') { i++; s++;}
		e = s;
		while (*e != ' ') { i++; e++;}

		if (c != s) { strncpy (c, s, e-s); memset (c+(e-s), ' ', s-c); }

		c = c+(e-s) +1;
	}

	removetrailingspaces (str);
}

int main (int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " \"<STRING>\" " << endl;
		return 1;
	}

	char* str = new char[1+strlen(argv[1])];
	memset (str, 0, 1+strlen(argv[1]));
	strcpy (str, argv[1]);

	cout << "Input string: <" << str << "> of length " << strlen(str) << "." << endl;

	removespaces (str);

	cout << "Updated string: <" << str << "> of length " << strlen(str) << "." << endl;

	delete [] str;
}


