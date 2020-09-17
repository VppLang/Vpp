@echo off
echo Compiling...
g++ -c src/*.cpp -std=c++17  -g -Wall -I include
g++ *.o -o bin/debug/main
echo Compiled!
echo Running...
bin\debug\main
echo Ran!
pause 10