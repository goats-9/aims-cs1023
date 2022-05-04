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
	fflush(stdout);
}

// To return a string (using getline)
// Second argument determines if the first argument
// is a message or a path to a file dump.
// x == 0 --> Message
// else --> File path
string get_str(string prompt, int x) {
	int lck = 0;	// facilitate flushing
	string s = "";
	if (x) dump(prompt);
	else {
		cout << prompt;
	}
	char ch;
	while (s == "") {
		while ((ch = getchar()) != '\n') {
			if (ch < 33 || ch > 126) {
				s = "";
				lck = 1;
			}
			if (!lck) s += ch;
		}
		if (s == "") cout << "No input or bad input.\n" << prompt;
	}
	return s;
}

// To return an integer (using cin)
int get_int(string prompt, int x) {
	int n;
	if (x) dump(prompt);
	else cout << prompt;
	while (1) {
		if (cin >> n) {
			return n;
		} else {
			cout << "Invalid integer input! ";
			dump(prompt);
			cin.clear();
		}
	}
}
