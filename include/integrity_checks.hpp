// Header File Safeguard
#ifndef _INTEGRITY_CHECKS_H_
#define _INTEGRITY_CHECKS_H_
#endif

#include "globvars.hpp"

int pass(string, string, int);
int isUser(string, int);
int isAssigned(string, string);
int isEnrolled(string, string);
int isCourse(string);
int isLegalPwd(string);
int isLegalID(string, int);
int isGrade(string);
int noAdmins();
int isFull(string);
