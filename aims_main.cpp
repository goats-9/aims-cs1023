#include "fileutils.hpp"
#include "integrity_checks.hpp"
#include "levels.hpp"
#include "input_handlers.hpp"
#define err(A, M) if (!A) {fprintf(stderr, M "\n"); continue;}

// For dump text files
string pd = "lib/prompts/", wel = "welcome.txt", adm = "admin.txt", clr = "cl.txt", cst = "course_stat.txt", ins = "faculty.txt", stu = "student.txt";

int main() {
	while (noAdmins()) {
		cout << "No Admin accounts detected!\nPlease create an admin account below.\n";
		string u_init = get_str("Enter admin username: ", 0);
		err(isLegalID(u_init, 2), "Illegal username entered.");
		string p_init = get_str("Enter admin password: ", 0);
		err(isLegalPwd(p_init), "Illegal password entered.");
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
				string p = get_str("Enter new password: ", 0);
				err(isLegalPwd(p), "Entered password is invalid.");
				S.passwd(p);
			} else if (op == 1) S.viewAllCourses();
			else if (op == 2) S.viewRegCourses();
			else if (op == 3) {
				string c_reg = get_str("Enter course code: ", 0);
				err(isCourse(c_reg), "Course does not exist.");
				err(!isEnrolled(u, c_reg), "You are already enrolled in this course.");
				err((getStatus(c_reg) == 1), "Course not available for registration.");
				err(!isFull(c_reg), "All slots occupied.");
				S.regCourse(c_reg);
			} else if (op == 4) {
				string c_rm = get_str("Enter course code: ", 0);
				err(isCourse(c_rm), "Course does not exist.");
				err(isEnrolled(u, c_rm), "You are not enrolled in this course.");
				S.deregCourse(c_rm);
			}
		}
	} else if (l == 1) {
		Faculty F(u, p, 1);
		while (op != 4) {
			op = get_int(pd + ins, 1);
			if (op < 0 || op > 4) cout << "Undefined operation. ";
			else if (op == 0) {
				string p = get_str("Enter new password (more than 10 characters, no spaces): ", 0);
				err(isLegalPwd(p), "Entered password is invalid.");
				F.passwd(p);
			} else if (op == 1) F.viewCourses();
			else if (op == 2) {
				string c_id = get_str("Enter course code: ", 0);
				err(isCourse(c_id), "Entered course code is invalid.");
				err(isAssigned(u, c_id), "You are not an instructor of this course.");
				string st_id = get_str("Enter student code: ", 0);
				err(isUser(st_id, 0), "Invalid student code.");
				err(isEnrolled(st_id, c_id), "Student is not enrolled in this course.");
				string g = get_str("Enter grade to award: ", 0);
				err(isGrade(g), "Entered grade is invalid.");
				F.allotGrade(c_id, st_id, g);
			} else if (op == 3) {
				string c_id = get_str("Enter course code: ", 0);
				err(isCourse(c_id), "Course does not exist.");
				err(isAssigned(u, c_id), "You are not an instructor of this course.");
				F.submitGrades(c_id);
			}
		}
	} else {
		Admin A(u, p, 2);
		while (op != 12) {
			op = get_int(pd + adm, 1);
			if (op < 0 || op > 12) cout << "Undefined operation. ";
			else if (op == 0) {
				string p = get_str("Enter new password: ", 0);
				err(isLegalPwd(p), "Entered password is invalid.");
				A.passwd(p);
			} else if (op == 8) {
				string f_id = get_str("Enter faculty code: ", 0);
				err(isUser(f_id, 1), "Faculty does not exist.");
				string c_id = get_str("Enter course code: ", 0);
				err(isCourse(c_id), "Course does not exist.");
				err(!isAssigned(f_id, c_id), "Faculty is already assigned to this course.");
				A.assignFaculty(f_id, c_id);
			} else if (op == 9) {
				string f_id, c_id;
				f_id = get_str("Enter faculty code: ", 0);
				err(isUser(f_id, 1), "Faculty does not exist.");
				c_id = get_str("Enter course code: ", 0);
				err(isCourse(c_id), "Course does not exist.");
				err(isAssigned(f_id, c_id), "Faculty is not assigned to this course.");
				A.removeFaculty(f_id, c_id);
			} else if (op == 4) {
				string cc = get_str("Enter course code: ", 0);
				err(!isCourse(cc), "Course already exists.");
				err(isLegalID(cc, -1), "Illegal course ID entered.");
				int a = get_int("Enter total course strength: ", 0);
				err((a > 0), "Entered total strength is invalid.");
				int b = get_int(pd + cst, 1);
				err((b >= 0 && b <= 3), "Entered status is invalid.");
				int c = get_int("Enter semester: ", 0);
				err((c >= 1 && c <= 10), "Entered semester is invalid.");
				int d = get_int("Enter starting segment: ", 0);
				err((d >= 0 && d <= 5), "Entered starting segment is invaild.");
				int e = get_int("Enter ending segment: ", 0);
				err((e >= 1 && e <= 6 && e > d), "Entered ending segment is invaild.");
				string fac = get_str("Enter instructor code: ", 0);
				err(isUser(fac, 1), "Faculty does not exist.");
				Course cr(cc, a, b, c, d, e);
				A.addCourse(cr, fac);
			} else if (op == 5) {
				string cc = get_str("Enter course code: ", 0);
				err(isCourse(cc), "Course does not exist.");
				int ns = get_int(pd + cst, 1);
				err((ns >= 0 && ns <= 3), "Entered status is invalid.");
				A.updateCourseStatus(cc, ns);
			} else if (op == 6) dump(c_txt);
			else if (op == 7) {
				string cc = get_str("Enter course code: ", 0);
				err(isCourse(cc), "Course does not exist.");
				A.removeCourse(cc);
			} else if (op == 2) {
				int cl = get_int(pd + clr, 1);
				dump(!cl ? st : (cl == 1 ? fa : ad));
			} else if (op == 1) {
				int cl = get_int(pd + clr, 1);
				err((cl >= 0 && cl <= 2), "Entered clearence level is invalid.");
				string uid = get_str("Enter ID of new user: ", 0);
				err(!isUser(uid, cl), "User already exists.");
				err(isLegalID(uid, cl), "Entered user ID is illegal.");
				A.addUser(uid, gen(), cl);
			} else if (op == 3) {
				int cl = get_int(pd + clr, 1);
				err((cl >= 0 && cl <= 2), "Entered clearence level is invalid.");
				string del_id = get_str("Enter ID of the user to delete: ", 0);
				err(isUser(del_id, cl), "User does not exist.");
				err((u != del_id), "You cannot delete your own account.");
				A.removeUser(del_id, cl);
			} else if (op == 10) {
				string s = get_str("Enter ID of student: ", 0);
				err(isUser(s, 0), "Student does not exist.");
				string c = get_str("Enter course code: ", 0);
				cout << c << endl;
				err(isCourse(c), "Course does not exist.");
				err(!isEnrolled(s, c), "Student is already enrolled in this course.");
				err((getStatus(c) == 1), "Course registration not enabled.");
				err(!isFull(c), "All slots filled.");
				A.addStudent(s, c);
			} else if (op == 11) {
				string s = get_str("Enter ID of student: ", 0);
				err(isUser(s, 0), "Student does not exist.");
				string c = get_str("Enter course code: ", 0);
				err(isCourse(c), "Course does not exist.");
				err(isEnrolled(s, c), "Student is not enrolled in this course.");
				err((getStatus(c) == 1 || getStatus(c) == 2), "Cannot deregister student.");
				A.removeStudent(s, c);
			}
		}
	}		
	return 0;
}
