// Header File Safeguard
#ifndef _GLOBVARS_H_
#define _GLOBVARS_H_
#endif
// For backtraces
#define err_ret(A, M) fprintf(stderr, "[ERROR] %s:%d: " M "\n", __FILE__, __LINE__) 
#define err(A, M) if (!A) {fprintf(stderr, "[ERROR] " M "\n"); continue;}

#include <bits/stdc++.h>
using namespace std;

/* DECLARE GLOBAL VARIABLES */
extern string ext, a, b, c, d, f, p, s, ext, ad, st, fa, pl, c_txt;
