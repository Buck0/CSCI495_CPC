@ECHO OFF
dir /S /B database >cpcTemp.txt

g++ -Wall -g -o plagiarismCheckerAlpha.exe plagiarismCheckerAlpha.cpp

plagiarismCheckerAlpha.exe