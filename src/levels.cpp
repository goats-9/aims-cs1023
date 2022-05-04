#include "levels.hpp"
#include "fileutils.hpp"
#include "globvars.hpp"
#include "integrity_checks.hpp"
#include "input_handlers.hpp"

Course::Course(string cid, int n, int stat, int sm, int st, int end) {
	code = cid;
	st_seg = st, end_seg = end, sem = sm, strength = n, status = stat, cur_str = 0;
}

string Course::getCode() { return code; }

// For entry formatting
int nDigits(int n) {
	int ctr = 0;
	while (n != 0) {
		++ctr;
		n /= 10;
	}
	return max(ctr, 1);
}


void Course::print_entry() {
	fstream fs(c_txt, ios::app);
	fs << code << " " << cur_str << " " << strength << " " << status << " " << sem  << " " << st_seg << " " << end_seg << "\n";
	fs.close();
}

User::User(string uniq, string pass, int cl) {
	id = uniq, secret = pass;
	lvl = cl;
}

string User::getID() { return id; }

void User::passwd(string s) {
	string fpath = b + (!lvl ? s : (lvl == 1 ? f : a)) + p + getID() + ext;
	fstream file(fpath, ios::out|ios::trunc);
	file << s << "\n";
	secret = s;
}

void Student::viewAllCourses() {
	fstream file(c_txt, ios::in);
	string s;
	int x1, x2, x3, x4, x5, x6;
	cout << "COURSE     NO_REG    NO_AVAL    STATUS    SEMESTER    SEGMENT\n------     ------    -------    ------    --------    -------\n";
	while (file >> s >> x1 >> x2 >> x3 >> x4 >> x5 >> x6) {
		cout << s << string(6, ' ') << string(3 - nDigits(x1), '0') << x1 << string(8, ' ') << string(3 - nDigits(x2), '0') << x2 <<string(8, ' ') << x3 << string(10, ' ') << x4 << string(10, ' ') << x5 << "-" << x6 <<  "\n";
	}
}

void Student::viewRegCourses() {
	string fpath = b + s + c + getID() + ext;
	fstream file(fpath, ios::in);
	string a;
	while (getline(file, a)) {
		cout << a << "\n";
		if (file.eof()) {
			file.close();
			break;
		}
	}
	file.close();
}

int Student::regCourse(string code) {
	string x = getID();
	string fpath = b + s + c + x + ext;
	fstream file(fpath, ios::app);
	file << code << " NA\n";
	file.close();
	string cpath = b + d + code + ext;
	fstream cfile(cpath, ios::app);
	cfile << x << " NA\n";
	cfile.close();
	editStrength(code, 1);
	return 0;
}

int Student::deregCourse(string code) {
	string x = getID();
	string fpath = b + s + c + x + ext;
	string cpath = b + d + code + ext;
	delCourse(fpath, code);
	delStudent(cpath, x);
	editStrength(code, -1);
	return 0;
}

void Faculty::viewCourses() {
	string x = getID();
	string fpath = b + f + c + x + ext;
	fstream file(fpath, ios::in);
	string s;
	while (getline(file, s)) {
		cout << s << "\n";
		if (file.eof()) {
			file.close();
			break;
		}
	}
}

int Faculty::allotGrade(string c_id, string st_id, string grade) {
	string fpath1 = b + s + c + st_id + ext;
	string fpath2 = b + d + c_id + ext;
	updGrade_st(fpath1, c_id, grade);
	updGrade_cr(fpath2, st_id, grade);
	return 0;
}

int Faculty::submitGrades(string code) {
	string fpath1 = b + d + code + ext;
	string fpath2 = b + a + c + code + ext;
	rename(fpath1.c_str(), fpath2.c_str());
	updStatus(code, 3);
	return 0;
}

int Admin::assignFaculty(string fac_id, string c_id) {
	string fpath1 = b + d + c_id + ext;
	string fpath2 = b + f + c + fac_id + ext;
	fstream x(fpath2, ios::app);
	x << c_id << "\n";
	x.close();
	addFac(fpath1, fac_id);
	return 0;
}

int Admin::removeFaculty(string fac_id, string c_id) {
	string fpath1 = b + d + c_id + ext;
	string fpath2 = b + f + c + fac_id + ext;
	rmFac(fpath1, fac_id);
	rmCourse(fpath2, c_id);
	return 0;
}

int Admin::addCourse(Course cr, string fac_id) {
	cr.print_entry();
	string cfpath = b + d + cr.getCode() + ext;
	fstream cfile(cfpath, ios::app);
	cfile << "1\n" << fac_id << "\n";
	cfile.close();
	string facpath = b + f + c + fac_id + ext;
	fstream fac(facpath, ios::app);
	fac << cr.getCode() << "\n";
	fac.close();
	return 0;
}

int Admin::updateCourseStatus(string code, int stat) { 
	updStatus(code, stat);
	return 0;
}

int Admin::removeCourse(string c_id) {
	rmCourse(c_id);
	return 0;
}

int Admin::addUser(string id, string pw, int cl) { 
	string fpath = b + (!cl ? s : (cl == 1 ? f : a)) + p + id + ext;
	string mpath = !cl ? st : (cl == 1 ? fa : ad);
	fstream file;
	file.open(fpath, ios::out|ios::trunc);
	file << pw << "\n";
	file.close();
	fstream mfile(mpath, ios::app);
	mfile << id << "\n";
	mfile.close();
	return 0;
}

int Admin::removeUser(string uniq, int cl) {
	string passfile = b + (!cl ? s : (cl == 1 ? f : a)) + p + uniq + ext;
	remove(passfile.c_str());
	if (cl == 1) {
		rmFac(uniq);
	} else if (cl == 0) {
		string cpath = b + s + c + uniq + ext;
		remove(cpath.c_str());
	}
	delUsr(uniq, cl);
	return 0;
}

int Admin::addStudent(string st_id, string c_id) {
	string afile = b + d + c_id + ext;
	fstream file(afile, ios::out|ios::app);
	file << st_id << " NA\n";
	file.close();
	string sfile = b + s + c + st_id + ext;
	fstream sf(sfile, ios::out|ios::app);
	sf << c_id << " NA\n";
	sf.close();
	editStrength(c_id, 1);
	return 0;
}

int Admin::removeStudent(string st_id, string c_id) {
	string cpath = b + d + c_id + ext;
	string spath = b + s + c + st_id + ext;
	delStudent(cpath, st_id);
	delCourse(spath, c_id);
	editStrength(c_id, -1);
	return 0;
}
