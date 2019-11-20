# Student: Matthew Buchanan
# Program: Code Plagiarism Checker
# Created: 11-18-2018
# Last Modified: 11-18-2018
# Course: CSCI 495
# Grade: B
## Design comments:
This program was created by Matthew Buchanan and Eli Brodskii.
The program was a semester-long group project in CSCI 495.
This program is a plagiarism checker that checks lines of code for plagiarism from text input or a file entry.
Each entire line of code is checked against lines of code from either text input or from a database of code.
The program will tell the user what percentage of the code was plagiarized and tell which line was matched.
The code is designed for use in a Windows environment.
The different folders were ways to keep track of the changes without using branches and as quick references to the old code, as well as
	an easy way of getting the Alpha and Beta versions of the code ready for testing and the final version for deployment.
The final version of the code can be found in the "finalProgram" folder and the code should be able to run on any Windows machine that has
	a 64-bit OS with the current C++ redistibutables found in normal Windows Updates (also an x86 architecture is likely required).
	The program is confirmed to not work on Windows 8.1 32-bit OS.
The program can be run simply by running the cpcBatch.cmd file in the "workingProgram" directory. This file makes the neccessary file needed 
	for the program to run which contains the absolute filepaths to the database entries. This was a particularly troublesome issue and 
	the cpcTemp.txt file was the best way concieved in the timeframe for the program to be able to read from the database. The batch file
	parses for the "database" directory and then puts each subdirectory and file into a line on the cpcTemp.txt file. Afterwards, it opens
	the program. The program then reads the filepaths for the database from this file.

# CSCI495_CPC
Code Plagiarism Checker for Systems Analysis

This program is designed to check for plagiarism in the code of students, particularly java code.
Theoretically, the checker should also work against any type of file that would specifically have lines copied from elsewhere such as html or cpp.
However, an English paper would not be a suitable candidate for this program to test.
It is supposed to compare the lines of a student's code to another piece of code or to a local database of previous code.
Its has no GUI so the UI is the terminal.
There is no java code in the implementation of the program, only a single batch file and then cpp code.
All of the java code registered on the code distibution are just fake entries for the database so that the database can have at least one entry per subfolder.
