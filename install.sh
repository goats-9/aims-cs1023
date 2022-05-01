sh clean.sh
mkdir lib/students lib/admin lib/faculty lib/coursedata
g++ -o aims aims_main.cpp -I include src/*.cpp -Wall -g -O2 -std=c++11
