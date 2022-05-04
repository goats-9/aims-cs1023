// Safeguard Header File
#ifndef _INPUT_HANDLERS_HPP_
#define _INPUT_HANDLERS_HPP_
#endif
#define err(A, M) if (!A) {fprintf(stderr, M "\n"); continue;}
#include <bits/stdc++.h>
using namespace std;

void dump(string);
string get_str(string, int);
int get_int(string, int);
