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


int Course::print_entry() {
	fstream cf(c_txt, ios::app);
	cf.exceptions(ifstream::badbit);
	err_open(cf, c_txt);
	cf << code << " " << cur_str << " " << strength << " " << status << " " << sem  << " " << st_seg << " " << end_seg << "\n";
	cf.close();
	return 0;
}

User::User(string uniq, string pass, int cl) {
	id = uniq, secret = pass;
	lvl = cl;
}

string User::getID() { return id; }

int User::passwd(string s) {
	string fpath = b + (!lvl ? s : (lvl == 1 ? f : a)) + p + getID() + ext;
	fstream file(fpath, ios::out|ios::trunc);
	err_open(file, fpath);
	file << s << "\n";
	secret = s;
	file.close();
	return 0;
}

int Student::viewAllCourses() {
	fstream file(c_txt, ios::in);
	string s;
	int x1, x2, x3, x4, x5, x6;
	err_open(file, c_txt);
	cout << "COURSE     NO_REG    NO_AVAL    STATUS    SEMESTER    SEGMENT\n------     ------    -------    ------    --------    -------\n";
	while (file >> s >> x1 >> x2 >> x3 >> x4 >> x5 >> x6) {
		cout << s << string(6, ' ') << string(3 - nDigits(x1), '0') << x1 << string(8, ' ') << string(3 - nDigits(x2), '0') << x2 <<string(8, ' ') << x3 << string(10, ' ') << x4 << string(10, ' ') << x5 << "-" << x6 <<  "\n";
	}
	
	return 0;
}

int Student::viewRegCourses() {
	string fpath = b + s + c + getID() + ext;
	fstream file(fpath, ios::in);
	string a;
	err_open(file, fpath);
	while (getline(file, a)) {
		cout << a << "\n";
		if (file.eof()) {
			file.close();
			break;
		}
	}
	file.close();
	return 0;
}

int Student::regCourse(string code) {
	string x = getID();
	string fpath = b + s + c + x + ext;
	fstream file(fpath, ios::app);
	err_open(file, fpath);
	file << code << " NA\n";
	file.close();
	string cpath = b + d + code + ext;
	fstream cfile(cpath, ios::app);
	err_open(cfile, cpath);
	cfile << x << " NA\n";
	cfile.close();
	err_ret((editStrength(code, 1) == 0), "Failed to edit course strength.");
	return 0;
}

int Student::deregCourse(string code) {
	string x = getID();
	string fpath = b + s + c + x + ext;
	string cpath = b + d + code + ext;
	err_ret((delCourse(fpath, code) == 0), "Failed to delete course from course records.");
	err_ret((delStudent(cpath, x) == 0), "Failed to delete course from student records.");
	err_ret((editStrength(code, -1) == 0), "Failed to edit course strength.");
	return 0;
}

int Faculty::viewCourses() {
	string x = getID();
	string fpath = b + f + c + x + ext;
	fstream file(fpath, ios::in);
	string s;
	err_open(cfile, cpath);
	while (getline(file, s)) {
		cout << s << "\n";
		if (file.eof()) {
			file.close();
			break;
		}
	}
	return 0;
}

int Faculty::allotGrade(string c_id, string st_id, string grade) {
	string fpath1 = b + s + c + st_id + ext;
	string fpath2 = b + d + c_id + ext;
	err_ret((updGrade_st(fpath1, c_id, grade) == 0), "Failed to update grade of student in student records.");
	err_ret((updGrade_cr(fpath2, st_id, grade) = 0), "Failed to update grade of student in course records.");
	return 0;
}

int Faculty::submitGrades(string code) {
	string fpath1 = b + d + code + ext;
	string fpath2 = b + a + c + code + ext;
	rename(fpath1.c_str(), fpath2.c_str());
	err_ret((updStatus(code, 3) == 0), "Failed to update course status after grade submission.");
	return 0;
}

int Admin::assignFaculty(string fac_id, string c_id) {
	string fpath1 = b + d + c_id + ext;
	string fpath2 = b + f + c + fac_id + ext;
	fstream x(fpath2, ios::app);
	err_open(x, fpath2);
	x << c_id << "\n";
	x.close();
	err_ret((addFac(fpath1, fac_id) == 0), "Failed to add faculty in course records.");
	return 0;
}

int Admin::removeFaculty(string fac_id, string c_id) {
	string fpath1 = b + d + c_id + ext;
	string fpath2 = b + f + c + fac_id + ext;
	err_ret((rmFac(fpath1, fac_id) == 0), "Failed to remove faculty from course records.");
	err_ret((rmCourse(fpath2, c_id) == 0), "Failed to remove course from faculty records.");
	return 0;
}

int Admin::addCourse(Course cr, string fac_id) {
	err_ret((cr.print_entry() == 0), "Failed to add course entry to course records.");
	string cfpath = b + d + cr.getCode() + ext;
	fstream cfile(cfpath, ios::app);
	err_open(cfile, cfpath);
	cfile << "1\n" << fac_id << "\n";
	cfile.close();
	string facpath = b + f + c + fac_id + ext;
	fstream fac(facpath, ios::app);
	err_open(fac, facpath);
	fac << cr.getCode() << "\n";
	fac.close();
	return 0;
}

int Admin::updateCourseStatus(string code, int stat) { 
	err_ret((updStatus(code, stat) == 0), "Failed to update course status.");
	return 0;
}

int Admin::removeCourse(string c_id) {
	err_ret((rmCourse(c_id) == 0), "Failed to remove course from records completely.");
	return 0;
}

int Admin::addUser(string id, string pw, int cl) { 
	string fpath = b + (!cl ? s : (cl == 1 ? f : a)) + p + id + ext;
	string mpath = !cl ? st : (cl == 1 ? fa : ad);
	fstream file(fpath, ios::out|ios::trunc);
	err_open(file, fpath);
	file << pw << "\n";
	file.close();
	fstream mfile(mpath, ios::app);
	err_open(mfile, fmpath);
	mfile << id << "\n";
	mfile.close();
	return 0;
}

int Admin::removeUser(string uniq, int cl) {
	string passfile = b + (!cl ? s : (cl == 1 ? f : a)) + p + uniq + ext;
	remove(passfile.c_str());
	if (cl == 1) err_ret((rmFac(uniq) == 0), "Failed to remove faculty from records completely.");
	else if (cl == 0) {
		string cpath = b + s + c + uniq + ext;
		remove(cpath.c_str());
	}
	err_ret((delUsr(uniq, cl) == 0), "Failed to delete user from records completely.");
	return 0;
}

int Admin::addStudent(string st_id, string c_id) {
	string afile = b + d + c_id + ext;
	fstream file(afile, ios::out|ios::app);
	err_open(file, afile);
	file << st_id << " NA\n";
	file.close();
	string sfile = b + s + c + st_id + ext;
	fstream sf(sfile, ios::out|ios::app);
	err_open(sf, sfile);
	sf << c_id << " NA\n";
	sf.close();
	err_ret((editStrength(c_id, 1) == 0), "Failed to edit course strength.");
	return 0;
}

int Admin::removeStudent(string st_id, string c_id) {
	string cpath = b + d + c_id + ext;
	string spath = b + s + c + st_id + ext;
	err_ret((delStudent(cpath, st_id) == 0), "Failed to delete student from course records.");
	err_ret((delCourse(spath, c_id) == 0), "Failed to delete course from course records.");
	err_ret((editStrength(c_id, -1) == 0), "Failed to edit course strength.");
	return 0;
}
