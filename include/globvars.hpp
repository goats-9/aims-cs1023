// Header File Safeguard
#ifndef _GLOBVARS_H_
#define _GLOBVARS_H_
#endif
// For backtraces
#define err_open(A, fname) if (!A.is_open()) {A.close(); fprintf(stderr, "[ERROR] %s:%d: Failed to open %s.\n", __FILE__, __LINE__, fname.c_str()); goto error;}   // File not opened
#define err_main(A, M, ...) if (!A) {fprintf(stderr, "[ERROR] %s:%d" M "\n", __FILE__, __LINE__, __VA_ARGS__); continue;}     // Main program does not terminate

#include <bits/stdc++.h>
using namespace std;

/* DECLARE GLOBAL VARIABLES */
extern string ext, a, b, c, d, f, p, s, ext, ad, st, fa, pl, c_txt;
