#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverseword (char* start, char* end)
{
	while (end > start) {
		char t = *start;
		*start = *end;
		*end = t;

		start++;
		end--;
	}
}

char* findwordstart (char* str)
{
	while (str) {
		if (isalpha(*str)) return str;
		str++;
	}

	return 0;
}

char* findwordend (char* str)
{
	while (str) {
		if (!isalpha(*str)) return str-1;
		str++;
	}

	return 0;
}

void reversewords (char* str)
{
	int i = 0;

	while (i < strlen (str)) {
		char* start = findwordstart (str);

		if (start) {
			char* end = findwordend (start);

			if (end) {
				reverseword (start, end);

				i = end - str;
				str = end +1;
			} else {
				break;
			}
		} else {
			break;
		}
	}
}

int main (int argc, char* argv[])
{
	if (argc != 2) {
		printf ("Usage: %s \"<STRING>\"\n", argv[0]);
		return 1;
	}

	char* str = argv[1];

	printf ("STRING  TO  REVERSE  WORDS <%s>\n", str);

	reversewords (str);

	printf ("STRING AFTER REVERSE WORDS <%s>\n", str);

	return 0;
}
