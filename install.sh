sh clean.sh
mkdir lib
mkdir lib/students lib/admin lib/faculty lib/coursedata
mkdir lib/students/courses lib/students/secrets lib/faculty/courses lib/faculty/secrets lib/admin/courses lib/admin/secrets 
g++ -o aims aims_main.cpp -I include src/*.cpp -Wall -g -O2 -std=c++11
