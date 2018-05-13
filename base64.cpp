#include <iostream>
#include <string>
using namespace std;


class Base64
{
private:
	string allchars;

	inline bool isBase64Char (unsigned char c) { return (isalnum(c) || (c == '+') || (c == '/')); }
public:
	Base64 () : allchars ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") { }

	string Encode (const string&);
	string Decode (const string&);
};


string Base64::Encode (const string& s)
{
        string out;

        int len = s.length ();

        if (len == 0) return out;

	string s3 ("123");
	string s4 ("1234");

        for (int i=0; i<len; i+=3) {
                s3 = s.substr (i, 3);

		int l = s3.length ();
		int k = l;
		while (l !=  3) s3[l++] = '\0';

                s4[0] = s3[0] >> 2;
                s4[1] = ((s3[0] & 0x03) << 4) + ((s3[1] & 0xf0) >> 4);
                s4[2] = ((s3[1] & 0x0f) << 2) + ((s3[2] & 0xc0) >> 6);
                s4[3] = s3[2] & 0x3f;

		for (int n=0; n<4; n++) s4[n] = allchars[(int) s4[n]];

		out += s4;
		while (k++ < 3) out += '=';
        }

	return out;
}

string Base64::Decode (const string& s)
{
	string out;

	int len = s.length ();

	if (len == 0) return out;

	string s3 ("123");
	string s4 ("1234");

        for (int i=0; i<len; i+=4) {
                s4 = s.substr (i, 4);

		int l = s4.length ();
		int k = l;
		while (l !=  4) s4[l++] = 0;

		for (int n=0; n<4; n++) {
			if (isBase64Char(s4[n])) s4[n] = allchars.find(s4[n]);
			else return out;
		}

		s3[0] = (s4[0] << 2) + ((s4[1] & 0x30) >> 4);
		s3[1] = ((s4[1] & 0xf) << 4) + ((s4[2] & 0x3c) >> 2);
		s3[2] = ((s4[2] & 0x3) << 6) + s4[3];

		out += s3;
	}

	return out;
}


int main (int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <STRING>" << endl;
		return 1;
	}

	char* msg = argv[1];

	cout << "Base 64 Encoding string <" << msg << ">" << endl;

	Base64 B;

	string encoded = B.Encode (msg);
	string decoded = B.Decode (encoded);
	cout << "Base 64 Encoded Message: " << encoded.c_str () << endl;
	cout << "Base 64 Decode Message: " << decoded.c_str () << endl;

	return 0;
}
