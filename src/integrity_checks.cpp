#include "globvars.hpp"

/* DATA INTEGREITY CHECKING UTILTITIES */

// To check whether a user already exists
int isUser(string code, int cl) {
	string file = b + (!cl ? s : (cl == 1 ? f : a)) + p + code + ext;
	fstream x(file, ios::in);
	if (!x) {
		x.close();
		return 0;
	}
	else {
		x.close();
		return 1;
	}
}

// To check whether a course already exists
int isCourse(string code) {
	string cfile = b + d + code + ext;
	fstream x(cfile, ios::in);
	if (!x) {
		x.close();
		return 0;
	} else {
		x.close();
		return 1;
	}
}

// To verify a password
int pass(string in, string code, int cl) {
	string pfile = b + (!cl ? s : (cl == 1 ? f : a)) + p + code + ext;
	string pw;
	fstream p(pfile, ios::in|ios::out);
	p >> pw;
	p.close();
	if (in == pw) return 1;
	else return 0;
}

// To check whether a faculty is already assigned to that course
int isAssigned(string fac_id, string c_id) {
	string cfile = b + d + c_id + ext;
	fstream c(cfile, ios::in);
	int n;
	string s;
	c >> n;
	for (int i = 0; i < n; i++) {
		c >> s;
		if (s == fac_id) {
			c.close();
			return 1;
		}
	}
	c.close();
	return 0;
}

// To check whether a student is enrolled in a course
int isEnrolled(string st_id, string c_id) {
	string stfile = b + s + c + st_id + ext;
	string x, y;
	fstream s(stfile, ios::in);
	while (s >> x >> y) {
		if (c_id == x) {
			s.close();
			return 1;
		}
	}
	s.close();
	return 0;
}

// To check if the password entered is legal
int isLegalPwd(string s) {
	int n = s.size();
	if (n < 8) return 0;
	for (int i = 0; i < n; i++) if (s[i] < 33 && s[i] > 126) return 0;
	return 1;
}

// To check if the username or coursename (cl == -1) entered is legal
int isLegalID(string s, int cl) {
	vector<string> dspln = {"AI", "BM", "BT", "CE", "CS", "EE", "ES", "ME", "MA"};
	if (cl == -1) {
		if (s.size() != 6) return 0;
		if (find(dspln.begin(), dspln.end(), s.substr(0, 2)) == dspln.end()) return 0;
		if (!(s[2] >= '1' && s[2] <= '5')) return 0;
		if (!isdigit(s[3]) || !isdigit(s[4])) return 0;
		if (!(s[5] >= '0' && s[5] <= '6')) return 0;
		return 1;
	} else if (cl == 0) {
		if (s.size() != 14) return 0;
		if (find(dspln.begin(), dspln.end(), s.substr(0, 2)) == dspln.end()) return 0;
		if (!isdigit(s[2]) || !isdigit(s[3]))  return 0;
		if (s.substr(4, 5) != "BTECH") return 0;
		for (int i = 9; i < 14; i++) if (!isdigit(s[i])) return 0;
		return 1;
	} else if (cl == 1) {
		if (s.size() != 9) return 0;
		if (find(dspln.begin(), dspln.end(), s.substr(0, 2)) == dspln.end()) return 0;
		if (!isdigit(s[2]) || !isdigit(s[3])) return 0;
		if (s[4] != '_' || s[5] != 'F') return 0;
		for (int i = 6; i < 9; i++) if (!isdigit(s[i])) return 0;
		return 1;
	} else if (cl == 2) {
		if (s.size() != 9) return 0;
		if (s.substr(0, 2) != "AD") return 0;
		if (!isdigit(s[2]) || !isdigit(s[3])) return 0;
		if (s[4] != '_') return 0;
		for (int i = 5; i < 9; i++) if (!isdigit(s[i])) return 0;
		return 1;
	}
	return 0;
}

// To check if the grade entered is legal
int isGrade(string s) {
	int n = s.size();
	if (n == 1) {
		if (s[0] >= 'A' && s[0] <= 'F' && s[0] != 'E') return 1;
		else return 0;
	} else if (n == 2) {
		if (s[0] == 'A' && (s[1] == '-' || s[1] == '+')) return 1;
		else if ((s[0] == 'B' || s[0] == 'C') && s[1] == '-') return 1;
		else return 0;
	} else return 0;
}

// Utility to check whether there are admin accounts
int noAdmins() {
	fstream adf(ad, ios::in);
	if (!adf) return 1;
	if (adf.peek() == adf.eof()) {
		adf.close();
		return 1;
	} else {
		adf.close();
		return 0;
	}
}

// To check whether the course is full
int isFull(string code) {
	fstream f(c_txt, ios::in);
	string s;
	int a, b;
	while (f >> s) {
		if (code == s) {
			f >> a >> b;
			if (a < b) return 0;
			else return 1;
		} else {
			getline(f, s);
			f.ignore();
		}
	}
	return 0;
}
