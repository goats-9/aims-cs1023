sh clean.sh
mkdir lib/students
mkdir lib/admin
mkdir lib/faculty
g++ -o aims aims_main.cpp -I include src/*.cpp -Wall -g -O2 -std=c++11