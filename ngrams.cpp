#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef map<string,int> NGRAM_FREQUENCY;

NGRAM_FREQUENCY ngrams (const string& input, const int len)
{
	NGRAM_FREQUENCY out;

	for (int i=0; i<=input.length()-len; i++) {
		string s = input.substr (i, len);
		out[s] += 1;
	}

	return out;
}
int main (int argc, char* argv[])
{
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " \"<string>\" <length>" << endl;
		return 1;
	}

	string input = argv[1];

	int length = atoi (argv[2]);

	if (length <= 0) return 2;

	cout << "Calculating ngrams for: " << input.c_str ()  << " of length " << length << endl;

	NGRAM_FREQUENCY output;
	output = ngrams (input, length);

	for (NGRAM_FREQUENCY::iterator it = output.begin (); it != output.end (); it++) {
		cout << "NGRAM == " << it->first.c_str () << " has frequency " << it->second << endl;
	}
	return 0;
}
