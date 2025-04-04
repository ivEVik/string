@echo off
if not exist "./bin" mkdir "./bin"

g++ ./src/main.cpp ./src/customstring.cpp -I ./src/ -o ./bin/string.exe -O3 -Wall -Wextra -Wsuggest-override -pedantic -std=c++11

xcopy /q /y data\test.txt bin
xcopy /q /y data\test.bat bin

pause
@echo on
