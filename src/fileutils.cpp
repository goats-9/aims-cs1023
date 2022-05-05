#include "fileutils.hpp"
#include <bits/stdc++.h>
using namespace std;

/* FILESYSTEM MANIPULATION UTILITIES */

// To remove the course from the text file in lib/students/courses/
int delCourse(string file, string code) {
	fstream x, y;
	x.open(file, ios::in);
	err_open(x, file);
	y.open(pl, ios::out);
	err_open(y, pl);
	string s1, s2;
	while (x >> s1 >> s2) if (s1 != code) y << s1 << " " << s2 <<  "\n";
	x.close();
	y.close();
	err_ret((remove(file.c_str()) == 0), "Failed to delete file %s.", file.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), file.c_str());
	return 0;
error:
	if (x.is_open()) x.close();
	if (y.is_open()) y.close();
	return -1;
}

// To remove the student from the text file in lib/coursedata
int delStudent(string file, string st_id) {
	fstream x, y;
	x.open(file, ios::in);
	y.open(pl, ios::out);
	string s1, s2;
	int n;
	x >> n;
	y << n << "\n";
	for (int i = 0; i < n; i++) {
		x >> s1;
		y << s1 << "\n";
	}
	while (x >> s1 >> s2) if (s1 != st_id) y << s1 << " " << s2 << "\n";
	x.close();
	y.close();
	err_ret((remove(file.c_str()) == 0), "Failed to delete file %s.", file.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), file.c_str());
error:
	if (x.is_open()) x.close();
	if (y.is_open()) y.close();
	return -1;
}

// To change the current course strength
int editStrength(string id, int delta) {
	string c_id, line;
	fstream f1(c_txt, ios::in);
	err_open(f1, c_txt);
	fstream f2(pl, ios::out|ios::app);
	err_open(f2, pl);
	int n;
	while (f1 >> c_id) {
		if (c_id == id) {
			f1 >> n;
			getline(f1, line);
			f2 << c_id << " " << n + delta << line << "\n";
		} else {
			getline(f1, line);
			f2 << c_id << line << "\n";
		}
	}
	f1.close();
	f2.close();
	err_ret((remove(c_txt.c_str() == 0), "Failed to delete file %s.", c_txt.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), c_txt.c_str());
	return 0;
error:
	if (f1.is_open()) f1.close();
	if (f2.is_open()) f2.close();
	return -1;
}

// To update the grade of the student in lib/students/courses/
void updGrade_st(string file, string c_id, string grade) {
	fstream x(file, ios::in);
	err_open(x, file);
	fstream y(pl, ios::out);
	err_open(y, pl);
	string a, b;
	while (x >> a >> b) {
		if (a == c_id) y << a << " " << grade << "\n";
		else y << a << " " << b << "\n";
	}
	x.close();
	y.close();
	err_ret((remove(file.c_str()) == 0), "Failed to delete file %s.", file.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), file.c_str());
}

// To update the grade of the student in lib/coursedata
int updGrade_cr(string file, string st_id, string grade) {
	fstream x(file, ios::in);
	err_open(x, file);
	fstream y(pl, ios::out|ios::app);
	err_open(y, pl);
	int n;
	string a, b;
	x >> n;
	y << n << "\n";
	for (int i = 0; i < n; i++) {
		x >> a;
		y << a << "\n";
	}
	while (x >> a >> b) {
		if (a == st_id) y << a << " " << grade << "\n";
		else y << a << " " << b << "\n";
	}
	x.close();
	y.close();
	err_ret((remove(file.c_str()) == 0), "Failed to delete file %s.", file.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), file.c_str());
}
	
// To update the status of a course in lib/coursedata/courses.txt
int updStatus(string code, int stat) {
	fstream x(c_txt, ios::in);
	err_open(x, c_txt);
	fstream y(pl, ios::out|ios::app);
	err_open(y, pl);
	string s;
	int p, q, r;
	while (x >> s) {
		y << s;
		if (code == s) {
			x >> p >> q >> r;
			y << " " << p << " " << q << " " << stat;
			getline(x, s);
			y << s << "\n";
		} else {
			getline(x, s);
			y << s << "\n";
		}
	}
	x.close();
	y.close();
	err_ret((remove(c_txt.c_str()) == 0), "Failed to delete file %s.", c_txt.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), c_txt.c_str());
}

// To add faculty for this course in lib/coursedata
int addFac(string path, string fac_id) {
	fstream x, y;
	x.open(path, ios::in);
	err_open(x, path);
	y.open(pl, ios::out|ios::app);
	err_open(y, pl);
	string s;
	int n;
	x >> n;
	y << n + 1 << "\n";
	for (int i = 0; i < n; i++) {
		x >> s;
		y << s << "\n";
	}
	y << fac_id << "\n";
	x.ignore();
	while (getline(x, s)) {
		y << s << "\n";
		if (x.eof()) {
			x.close();
			break;
		}
	}
	y.close();
	err_ret((remove(path.c_str()) == 0), "Failed to delete file %s.", path.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), path.c_str());
	return 0;
error:
	if (x.is_open()) x.close();
	if (y.is_open()) y.close();
	return -1;
}

// To remove faculty for this course in lib/coursedata
int rmFac(string path, string fac_id) {
	fstream x, y;
	x.open(path, ios::in);
	err_open(x, path);
	y.open(pl, ios::out);
	err_open(y, pl);
	string s1, s2;
	int n;
	x >> n;
	y << n - 1 << "\n";
	for (int i = 0; i < n; i++) {
		x >> s1;
		if (s1 != fac_id) y << s1 << "\n";
	}
	while(x >> s1 >> s2) y << s1 << " " << s2 << "\n";
	x.close();
	y.close();
	err_ret((remove(path.c_str() == 0), "Failed to delete file %s.", path.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), path.c_str());
error:
	if (x.is_open()) x.close();
	if (y.is_open()) y.close();
	return -1;
}

// Overload previous utility to remove the faculty from all courses they are a part of
int rmFac(string id) {
	string cpath = b + f + c + id + ext;
	string c_id;
	fstream x(cpath, ios::in);
	err_open(x, cpath);
	while (x >> c_id) {
		string fpath = b + d + c_id + ext;
		rmFac(fpath, id);
	}
	x.close();
	err_ret((remove(cpath.c_str()) == 0), "Failed to delete file %s.", cpath.c_str());
	return 0;
error:
	if (x.is_open()) x.close();
	return -1;
}

// To remove a course from the file in lib/faculty/courses and lib/student/courses
int rmCourse(string path, string c_id) {
	fstream x, y;
	x.open(path, ios::in);
	err_open(x, path);
	y.open(pl, ios::out);
	err_open(y, pl);
	string s, t;
	while(getline(x, s)) {
		if (s.substr(0, 6) != c_id) y << s << "\n";
		if (x.eof()) {
			x.close();
			break;
		}
	}
	y.close();
	err_ret((remove(path.c_str()) == 0), "Failed to delete file %s.", path.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), path.c_str());
error:
	if (x.is_open()) x.close();
	if (y.is_open()) y.close();
	return -1;
}

// Overload previous utility to remove the course from the filesystem completely
int rmCourse(string c_id) {
	string fpath = b + d + c_id + ext;
	fstream x, y, z;
	x.open(fpath, ios::in);
	err_open(x, fpath);
	string s1, s2;
	int n;
	x >> n;
	for (int i = 0; i < n; i++) {
		x >> s1;
		string fac_path = b + f + c + s1 + ext;
		err_ret((rmCourse(fac_path.c_str(), c_id) == 0), "Failed to remove course %s from faculty records.", c_id.c_str());
	}
	while (x >> s1 >> s2) {
		string st_path = b + s + c + s1 + ext;
		err_ret((rmCourse(st_path.c_str(), c_id) == 0), "Failed to remove course %s from student records.", c_id.c_str());
	}
	x.close();
	y.open(c_txt, ios::in);
	err_open(y, c_txt);
	z.open(pl, ios::out);
	err_open(z, pl);
	while (getline(y, s)) {
		if (s.substr(0, 6) != c_id) z << s;
		if (y.eof()) {
			y.close();
			break;
		}
	}
	z.close();
	err_ret((remove(fpath.c_str()) == 0), "Failed to delete file %s.", fpath.c_str());
	err_ret((remove(c_txt.c_str()) == 0), "Failed to delete file %s.", c_txt.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), c_txt.c_str());
	return 0;
error:
	if (x.is_open()) x.close();
	if (y.is_open()) y.close();
	if (z.is_open()) z.close();
	return -1;
}

// To remove a user from the users lists in lib
int delUsr(string uniq, int cl) {
	fstream x, y;
	string f, s;
	if (cl == 2) f = ad;
	else if (cl == 1) f = fa;
	else if (cl == 0) f = st;
	x.open(f, ios::in);
	err_open(x, f);
	y.open(pl, ios::out);
	err_open(y, pl);
	while (x >> s) if (s != uniq) y << s << "\n";
	x.close();
	y.close();
	err_ret((remove(f.c_str()) == 0), "Failed to delete file %s.", f.c_str());
	err_ret((rename(pl.c_str(), file.c_str()) == 0), "Failed to rename file %s to %s.", pl.c_str(), f.c_str());
	return 0;
error:
	if (x.is_open()) x.close();
	if (y.is_open()) y.close();
	return -1;
}

// To check the status of a course given its code
int getStatus(string code) {
	fstream f(c_txt, ios::in);
	err_open(f, c_txt);
	string s;
	int a, b, c;
	while(f >> s) {
		if (s == code) {
			f >> a >> b >> c;
			return c;
		} else getline(f, s);
	}
	return 0;
error:
	if (f.is_open()) f.close();
	return -1;
}

/* MISCELLANEOUS UTILITIES */

// To generate a random password
string gen() {
	uniform_int_distribution<int> len(8, 16);
	uniform_int_distribution<int> pool(33, 126);
	random_device rd;
	int n = len(rd);
	string s = "";
	for (int i = 0; i < n; i++) s += (char) pool(rd);
	return s;
}
