#include <stdio.h>
#include <map>
using namespace std;


class ExcelMap
{
public:
	int map (char* c);
};

int ExcelMap::map (char* c)
{
	int i = 0;

	int k = 1;

	for (int j=strlen(c)-1; j >= 0;  j--) {

		int v = c[j] - 'A' +1;
		i += k*v;
		k *= 26;
	}

	return i;
}

void UpperCase (char* str)
{
	while (*str != '\0') { *str = toupper (*str); str++;}
}

int main (int argc, char* argv[])
{
	if (argc != 2) {
		printf ("Usage: %s <COLUMN NAME>\n", argv[0]);
		return 1;
	}

	printf ("Excel column to map <%s>\n", argv[1]);

	char* str = new char[1+strlen(argv[1])];
	memset (str, 1, 1+strlen(argv[1]));
	strcpy (str, argv[1]);

	UpperCase (str);

	printf ("Excel column to map <%s>\n", str);

	ExcelMap em;

	int n = em.map(str);

	printf ("Excel column <%s> maps to <%d>\n", argv[1], n);

	delete [] str;
}


#if 0
AA = 27 = 26 + 1
AZ = 52 = 26 + 26
BA =  53 = 52 + 1
#endif
