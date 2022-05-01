// Header File Safeguard
#ifndef _LEVELS_H_
#define _LEVELS_H_
#endif

#include <bits/stdc++.h>
#include "input_handlers.hpp"
using namespace std;

// Creating a class for courses offered
class Course {
	int strength, cur_str, sem, st_seg, end_seg;
	int status;		// 0 if unavailable, 1 if floated and registeration active, 2 if registeration ended, 3 if grades submitted
	string code;
public:
	Course(string, int, int, int, int, int);
	string getCode();
	void print_entry();
};

// Any user has a username and password
// They can change their password and username
class User {
	string id, secret;
	int lvl;	// 0 for Student, 1 for Faculty, 2 for Admin
public:
	User(string, string, int);
	string getID();
	void passwd(string);
};

class Student:public User {
public:
	using User::User;
	void viewAllCourses();
	void viewRegCourses();
	int regCourse(string);
	int deregCourse(string);
};

class Faculty:public User {
public:
	using User::User;
	void viewCourses();
	int allotGrade(string, string, string);
	int submitGrades(string);
};

class Admin:public User {
public:
	using User::User;
	int assignFaculty(string, string);
	int removeFaculty(string, string);
	int addCourse(Course, string);
	int updateCourseStatus(string, int);
	int removeCourse(string);
	int addUser(string, string, int);
	int removeUser(string, int);
	int addStudent(string, string);
	int removeStudent(string, string);
};
