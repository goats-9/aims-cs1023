#include "input_handlers.hpp"

/* INPUT HANDLERS */

// To dump contents of a file
void dump(string path) {
	fstream f(path, ios::in);
	string s;
	while (getline(f, s)) {
		cout << s << "\n";
		if (f.eof()) {
			f.close();
			break;
		}
	}
}

// To return a string (using getchar)
// Second argument determines if the first argument
// is a message or a path to a file dump.
// x == 0 --> Message
// else --> File path
string get_str(string prompt, int x) {
	int lck = 0;	// facilitate flushing
	string s = "";
	if (x) dump(prompt);
	else cout << prompt;
	char ch;
	while ((ch = getchar()) != '\n') {
		if (!lck) {
			if (ch < 33 || ch > 126) {
				s = "";
				lck = 1;
			} else s += ch;
		}
	}
	if (s == "") cout << "No input or bad input.\n" << prompt;
	return s;
}

// To return an integer (using getchar)
int get_int(string prompt, int x) {
	long long n = 0;
	int lck = 0;
	if (x) dump(prompt);
	else cout << prompt;
	char ch;
	while ((ch = getchar()) != '\n') {
		if (!isdigit(ch)) lck = 1, n = -1;
		if (!lck) n = 10*n + (ch - '0');
	}
	if (n == -1) cout << "No input or bad input.\n";
	return n;
}
