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
	string s = "";
	if (x) dump(prompt);
	else {
		cout << prompt;
		fflush(stdout);
	}
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch == ' ') return "";
		s += ch;
	}
	fflush(stdout);
	return s;
}

// To return an integer (using cin)
int get_int(string prompt, int x) {
	int n;
	if (x) dump(prompt);
	else cout << prompt;
	while (1) {
		if (cin >> n) {
			cin.ignore();
			fflush(stdout);
			return n;
		} else {
			cout << "Invalid integer input! ";
			dump(prompt);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			fflush(stdout);
		}
	}
}
