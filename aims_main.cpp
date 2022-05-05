#include "fileutils.hpp"
#include "integrity_checks.hpp"
#include "levels.hpp"
#include "input_handlers.hpp"

// For dump text files
string pd = "lib/prompts/", wel = "welcome.txt", adm = "admin.txt", clr = "cl.txt", cst = "course_stat.txt", ins = "faculty.txt", stu = "student.txt";

int main() {
	while (noAdmins()) {
		cout << "No Admin accounts detected!\nPlease create an admin account below.\n";
		string u_init = get_str("Enter admin username.\nAdmin usernames are of the form AD<Last two digits of year of joining><3-digit ID> (e.g. AD12002).\n", 0);
		err_main(isLegalID(u_init, 2), "Illegal username entered.");
		string p_init = get_str("Enter admin password (must be at least 8 printable characters with ASCII values between 33 and 126, both inclusive)\n", 0);
		err_main(isLegalPwd(p_init), "Illegal password entered.");
		Admin ad_init(u_init, p_init, 2);
		ad_init.addUser(u_init, p_init, 2);
	}
	dump(pd + wel);
	int l = -1;
	l = get_int(pd + clr, 1);
	while (l < 0 || l > 2) {
		cout << "Invalid Clearance. ";
		l = get_int(pd + clr, 1);
	}
	string u = get_str("Username: ", 0);
	string p = get_str("Password: ", 0);
	while (!isUser(u, l) || !pass(p, u, l)) {
		cout << "Username or password is incorrect!\n";
		u = get_str("Username: ", 0);
		p = get_str("Password: ", 0);
	}
	cout << "\nWelcome " << u << "!\n";
	int op = -1;	// To enter the while loops
	if (l == 0) {
		Student S(u, p, 0);
		while (op != 5) {
			op = get_int(pd + stu, 1);
			if (op < 0 || op > 5) cout << "Undefined operation. ";
			if (op == 0) {
				string p = get_str("Enter new password (must be at least 8 printable characters with ASCII values between 33 and 126, both inclusive)\n", 0);
				err_main(isLegalPwd(p), "Entered password is invalid.");
				S.passwd(p);
			} else if (op == 1) S.viewAllCourses();
			else if (op == 2) S.viewRegCourses();
			else if (op == 3) {
				string c_reg = get_str("Enter course code: ", 0);
				err_main(isCourse(c_reg), "Course does not exist.");
				err_main(!isEnrolled(u, c_reg), "You are already enrolled in this course.");
				err_main((getStatus(c_reg) == 1), "Course not available for registration.");
				err_main(!isFull(c_reg), "All slots occupied.");
				S.regCourse(c_reg);
			} else if (op == 4) {
				string c_rm = get_str("Enter course code: ", 0);
				err_main(isCourse(c_rm), "Course does not exist.");
				err_main(isEnrolled(u, c_rm), "You are not enrolled in this course.");
				S.deregCourse(c_rm);
			}
		}
	} else if (l == 1) {
		Faculty F(u, p, 1);
		while (op != 4) {
			op = get_int(pd + ins, 1);
			if (op < 0 || op > 4) cout << "Undefined operation. ";
			else if (op == 0) {
				string p = get_str("Enter new password (must be at least 8 printable characters with ASCII values between 33 and 126, both inclusive)\n", 0);
				err_main(isLegalPwd(p), "Entered password is invalid.");
				F.passwd(p);
			} else if (op == 1) F.viewCourses();
			else if (op == 2) {
				string c_id = get_str("Enter course code: ", 0);
				err_main(isCourse(c_id), "Entered course code is invalid.");
				err_main(isAssigned(u, c_id), "You are not an instructor of this course.");
				string st_id = get_str("Enter student code: ", 0);
				err_main(isUser(st_id, 0), "Invalid student code.");
				err_main(isEnrolled(st_id, c_id), "Student is not enrolled in this course.");
				string g = get_str("Enter grade to award: ", 0);
				err_main(isGrade(g), "Entered grade is invalid.");
				F.allotGrade(c_id, st_id, g);
			} else if (op == 3) {
				string c_id = get_str("Enter course code: ", 0);
				err_main(isCourse(c_id), "Course does not exist.");
				err_main(isAssigned(u, c_id), "You are not an instructor of this course.");
				F.submitGrades(c_id);
			}
		}
	} else {
		Admin A(u, p, 2);
		while (op != 12) {
			op = get_int(pd + adm, 1);
			if (op < 0 || op > 12) cout << "Undefined operation. ";
			else if (op == 0) {
				string p = get_str("Enter new password (must be at least 8 printable characters with ASCII values between 33 and 126, both inclusive)\n", 0);
				err_main(isLegalPwd(p), "Entered password is invalid.");
				A.passwd(p);
			} else if (op == 8) {
				string f_id = get_str("Enter faculty code: ", 0);
				err_main(isUser(f_id, 1), "Faculty does not exist.");
				string c_id = get_str("Enter course code: ", 0);
				err_main(isCourse(c_id), "Course does not exist.");
				err_main(!isAssigned(f_id, c_id), "Faculty is already assigned to this course.");
				A.assignFaculty(f_id, c_id);
			} else if (op == 9) {
				string f_id, c_id;
				f_id = get_str("Enter faculty code: ", 0);
				err_main(isUser(f_id, 1), "Faculty does not exist.");
				c_id = get_str("Enter course code: ", 0);
				err_main(isCourse(c_id), "Course does not exist.");
				err_main(isAssigned(f_id, c_id), "Faculty is not assigned to this course.");
				A.removeFaculty(f_id, c_id);
			} else if (op == 4) {
				string cc = get_str("Enter course code. Course codes must be a string of 6 characters, of the form <Branch Abbreviation>ABBC, where A denotes the year (from 1 to 5, for UG) when the course is offered, BB denotes a unique 2-digit code for that course, and C is a digit between 0 and 6 (both inclusive) depending on the type of course.\n", 0);
				err_main(!isCourse(cc), "Course already exists.");
				err_main(isLegalID(cc, -1), "Illegal course ID entered.");
				int a = get_int("Enter total course strength: ", 0);
				err_main((a > 0), "Entered total strength is invalid.");
				int b = get_int(pd + cst, 1);
				err_main((b >= 0 && b <= 3), "Entered status is invalid.");
				int c = get_int("Enter semester: ", 0);
				err_main((c >= 1 && c <= 10), "Entered semester is invalid.");
				int d = get_int("Enter starting segment: ", 0);
				err_main((d >= 0 && d <= 5), "Entered starting segment is invaild.");
				int e = get_int("Enter ending segment: ", 0);
				err_main((e >= 1 && e <= 6 && e > d), "Entered ending segment is invaild.");
				string fac = get_str("Enter instructor code: ", 0);
				err_main(isUser(fac, 1), "Faculty does not exist.");
				Course cr(cc, a, b, c, d, e);
				A.addCourse(cr, fac);
			} else if (op == 5) {
				string cc = get_str("Enter course code: ", 0);
				err_main(isCourse(cc), "Course does not exist.");
				int ns = get_int(pd + cst, 1);
				err_main((ns >= 0 && ns <= 3), "Entered status is invalid.");
				A.updateCourseStatus(cc, ns);
			} else if (op == 6) dump(c_txt);
			else if (op == 7) {
				string cc = get_str("Enter course code: ", 0);
				err_main(isCourse(cc), "Course does not exist.");
				A.removeCourse(cc);
			} else if (op == 2) {
				int cl = get_int(pd + clr, 1);
				dump(!cl ? st : (cl == 1 ? fa : ad));
			} else if (op == 1) {
				int cl = get_int(pd + clr, 1);
				err_main((cl >= 0 && cl <= 2), "Entered clearence level is invalid.");
				if (cl == 0) cout << "Student IDs are of the form <Two-letter branch abbreviation in capitals><Last two digits of year of joining>BTECH<5-digit ID> (e.g. CS21BTECH11018).\n";
				else if (cl == 1) cout << "Faculty IDs are of the form <Two-letter branch abbreviation in capitals><Last two digits of year of joining>F<3-digit ID> (e.g. CS12F002).\n";
				else cout << "Admin IDs are of the form AD<Last two digits of year of joining><3-digit ID> (e.g. AD12002).\n";
				string uid = get_str("Enter ID of new user: ", 0);
				err_main(!isUser(uid, cl), "User already exists.");
				err_main(isLegalID(uid, cl), "Entered user ID is illegal.");
				A.addUser(uid, gen(), cl);
			} else if (op == 3) {
				int cl = get_int(pd + clr, 1);
				err_main((cl >= 0 && cl <= 2), "Entered clearence level is invalid.");
				string del_id = get_str("Enter ID of the user to delete: ", 0);
				err_main(isUser(del_id, cl), "User does not exist.");
				err_main((u != del_id), "You cannot delete your own account.");
				A.removeUser(del_id, cl);
			} else if (op == 10) {
				string s = get_str("Enter ID of student: ", 0);
				err_main(isUser(s, 0), "Student does not exist.");
				string c = get_str("Enter course code: ", 0);
				err_main(isCourse(c), "Course does not exist.");
				err_main(!isEnrolled(s, c), "Student is already enrolled in this course.");
				err_main((getStatus(c) == 1), "Course registration not enabled.");
				err_main(!isFull(c), "All slots filled.");
				A.addStudent(s, c);
				cout << "Added " << s << " to course " << c << " successfully.\n";
			} else if (op == 11) {
				string s = get_str("Enter ID of student: ", 0);
				err_main(isUser(s, 0), "Student does not exist.");
				string c = get_str("Enter course code: ", 0);
				err_main(isCourse(c), "Course does not exist.");
				err_main(isEnrolled(s, c), "Student is not enrolled in this course.");
				err_main((getStatus(c) == 1 || getStatus(c) == 2), "Cannot deregister student.");
				A.removeStudent(s, c);
				cout << "Removed " << s << " from course " << c << " successfully.\n";
			}
		}
	}		
	return 0;
}
