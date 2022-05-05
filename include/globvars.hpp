// Header File Safeguard
#ifndef _GLOBVARS_H_
#define _GLOBVARS_H_
#endif
// For backtraces
#define err_ret(A, M, ...) if (!A) {A.close(), fprintf(stderr, "[ERROR] %s:%d: " M "\n", __FILE__, __LINE__, __VA_ARGS__); return -1;}   // Exit value
#define err_main(A, M, ...) if (!A) {fprintf(stderr, "[ERROR] %s:%d" M "\n", __FILE__, __LINE__, __VA_ARGS__); continue;}     // Main program does not terminate

#include <bits/stdc++.h>
using namespace std;

/* DECLARE GLOBAL VARIABLES */
extern string ext, a, b, c, d, f, p, s, ext, ad, st, fa, pl, c_txt;
