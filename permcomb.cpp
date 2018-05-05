#include <iostream>
#include <map>
#include <string>
using namespace std;


class TelephonePad
{
private:
	string result;

	map<int, string> telephonepad;
	void init ();

	void PrintComb (int c, const string& input);

public:
	TelephonePad() { init (); }

	void PrintComb (const string&);
};

void TelephonePad::init ()
{
	telephonepad[0] = "";
	telephonepad[1] = "";
	telephonepad[2] = "abc";
	telephonepad[3] = "def";
	telephonepad[4] = "ghi";
	telephonepad[5] = "jkl";
	telephonepad[6] = "mno";
	telephonepad[7] = "pqrs";
	telephonepad[8] = "tuv";
	telephonepad[9] = "wxyz";
}

void TelephonePad::PrintComb (int c, const string& input)
{
	if (c == input.length ()) {
		cout << "COMBINATION: " << result.c_str () << endl;
	} else if ((0 == input[c] - '0') || ('1' == input[c] - '0')) {
		return ;
	} else {

		for (int i=0; i<telephonepad[input[c]-'0'].length(); i++) {
			result[c] = telephonepad[input[c]-'0'][i];

			PrintComb(c+1, input);
		}
	}
}

void TelephonePad::PrintComb (const string& input)
{
	if (input.empty ()) return;
	cout << "Printing combinations for " << input << endl;

	PrintComb (0, input);
}


int main (int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " keys" << endl;
		return -1;
	}

	TelephonePad tp;

	tp.PrintComb (argv[1]);

	return 0;
}
