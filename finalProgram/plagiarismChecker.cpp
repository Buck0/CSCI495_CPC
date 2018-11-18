// CODE PLAGIARISM CHECKER VERSION 1.0

// Inclusion of the appropriate headers
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
#include <windows.h>

// Using the standard namespace to save time and to not have to type std:: before almost everything
using namespace std;

// This vector of strings will hold the filepaths for each database entry
// 	This vector needs to be a global variable so that every function has access to it
vector<string> databaseItems;

// Prototyping the functions that will be called by the User Interface
// This function will be the interface to add a file to the database
void addToDatabaseUI();

// This function will actually perform the action of adding the file to the database
bool addToDatabase(const int type, string fileInfo, string newFileName);

// This function will compare two code files or excerpts
void fileToFile();

// This function will compare
void compareToDatabase();

// This function reads in code files or excerpts
void readInFileOrText(vector<string> &code, vector<string> &properties);

// The main function that will house the user interface and will call every other function
int main(int argc, char *argv[]) {

/*
  // ***NOTE*** The following section is for use in a Linux environment with a shell script
  // 	The section ends at the comment: "End of the Linux environment code"
  // This vector will house each filepath for each database entry
	vector<string> databaseItems;

  // This loop assigns each filepath to an element in the vector
	for(unsigned int i = 1; argv[i] != NULL; i++){
		databaseItems.push_back(argv[i]);
	}
// This is here solely for testing to ensure the database was passed in correctly
	for(unsigned int i = 0; i < databaseItems.size(); i++){
		cout << databaseItems[i];
		cout << " ";
	}

	cout << endl;
// End of the Linux environment code
*/

// The following file contains the database information as per a batch file for a Windows environment
// Using the batch file allows the cpcTemp.txt location to not have to be entered manually
	ifstream fileIn;

// This string will take in the filepath from the text file
	string fileName = "";

// This command opens the file
	fileIn.open("cpcTemp.txt");

// This if else statement ensures that the file is opened as expected and gets the first filepath by line if so
	if(fileIn){
		getline(fileIn, fileName);
	}
// Theoretically, this else should never have to be called but it exists incase some unforseen error happens
	else{
		cout << "FATAL ERROR: cpcTemp.txt file not found, cannot find database, exiting program." << endl;
		return 0;
	}

// This while loop will assign each filepath to a spot in the vector and will end when there are no more filepaths
	while(fileIn){

// This adds the filepath to the vector
		databaseItems.push_back(fileName);

// This takes in a new filepath by each line if there is one or sets fileIn to false which will exit the while loop
		getline(fileIn, fileName);
	}

// This closes the file properly
	fileIn.close();
/*
// This code is here as a preliminary test to see if reading from the database works at all
// 	this test code continues until the comment: "End of database read-test code"
// Also of note, this test code does not necessarily reflect how the finaly code will function
// 	and was based upon how the preliminary test database was made
	ifstream fileIn2;

	string testStr = "";

// Since Windows puts the directories as entries by themselves, calling a specific place is not recommended
// 	since the first few entries will only be the directories in the database folder. However, when
// 	looking at the entire database comparison, having the directories listed will not pose any issues.
// In fact, having the directories listed first actually helps tremendously in that we can append each
// 	new database filename to the first subdirectory of the database which will likely be for the current year
// The number in "[]" can be changed based on different tests but should not be changed to exceed databaseItems.size()
	fileIn2.open(databaseItems[1].c_str());

//	cout << "\n\nopen" << endl;
//	cout << "\n\n\n" << endl;
	if(fileIn2){
		fileIn2 >> testStr;
	}
	while(fileIn2){
		cout << testStr << " ";
		fileIn2 >> testStr;
	}
	cout << "\n\nclose\n";
	cout << "\n\n" << endl;

	fileIn2.close();
// End of database read-test code
*/

/*
	// This is here solely for testing to ensure the database was passed in correctly
		cout << "\n\n\n" << endl;
		for(unsigned int i = 0; i < databaseItems.size(); i++){
			cout << databaseItems[i];
			cout << " ";
		}

		cout << "\n\n" << endl;
*/

  // The following variables are used to take in the user's prompt for what code to execute
	int userIn = 0;
	string userStr = "";
	char userChar = 'a';

  // This variable is used to loop the user interface to allow continuous use
	bool cont = true;

  // This loop lets the user select their desired function and will loop until the user desires to close the program
	do{

    // This tells the user what each prompt will do and asks the user for their input
	cout << "Please select what you would like to do." << '\n';
	cout << "Enter 1 to compare two code files or excerpts" << '\n';
	cout << "Enter 2 to add a code file to the database" << '\n';
	cout << "Enter 3 to compare a code file to the entire database\n";
	cout << "Enter 4 to leave and close the program: ";

    // Taking in a string ensures that anything the user inputs will be technically valid while also allowing
    //    for error checking against the desired input
	cin >> userStr;

	if (userStr.length() > 1) { userStr = "0"; }

    // Setting the first character as the user's true input since an int should not be compared to a string
	userChar = userStr[0];

    // This turns that character into an int value so that a simple switch case can be used for comparison
    // Subtracting the char value '0' (an int value of 48) will make the char value '1' (an int value of 49)
    //    be an int value of 1, itself, and likewise for any number characters
	userIn = static_cast<int>(userChar - '0');

    // The switch statement evaluates the user's input and determines what the user wants to do; if the user
    //    did not input something that is recognized, an error will display and the user will be prompted to try again
	switch(userIn){

      // This case sets the control for the loop to false so that the program can close
		case 4:
			cont = false;
			break;

      // This case will run the file/text to file/text comparison
		case 1:
      // The function below is a placeholder for the actual function that will be called to execute this portion
      //    of the program
			fileToFile();
			break;

      // This case will run the database addition
		case 2:
			addToDatabaseUI();
			break;

      // This case will run the file/text to database comparison
		case 3:
			compareToDatabase();
			break;

      // The default case prints an error message and prompts the user to input something of the correct format
		default:
			cout << "You did not enter something this system can recognize. Please try again.\n\n" << endl;
	}

    // While the control is true, the user interface will keep asking the user what they would like to do
	}while(cont);

  // This prints a friendly exit message to let the user know the program is closed
	cout << "The program is now closing.\n" << endl;

  // The program is now closed
  return 0;
}

// This is the function that will be the UI to add a file to the database and will call addToDatabase
// Additionally, it may recurse on itself if the addition did not properly complete so that the user can try again
void addToDatabaseUI(){

// These variables will be for the user's input for the overall functions of this submenu
	string in = "";
	char charIn = 'a';
	int intIn = 2;

// This variable is for checking the file to make sure it exists
	ifstream fileCheck;

// This variable serves as the holding place for a text input of the student's code
	string studCode = "";
// This variable is a control for the text input for a text addition to the database
// It will be set to false once the user enters the control string "x9x"
	bool isCin = true;

// These variables will respectively hold the new file name and either the code to put
// 	into the new file or the name of the file that needs to be copied to the database
	string fileName = "";
	string codeIn = "";

// This bool control variable will change to false when the user input is good
	bool contr = true;

// This do while loop will make sure that the user inputs either 0 or 1 so that the correct
// 	operation can be done
	do {

// This asks the user which operation they would like to do
		cout << "\nWould you like to enter a text selection or a .txt or .java file as the student's code to add?\n";
		cout << "Enter \"main_menu\" to return to the main menu of the program.\n";
		cout << "Enter \'0\' for a text selection or \'1\' for a file: ";

// This retrieves the user's input
		cin >> in;

// This will return the user to the main menu if they request to go back
		if (in.compare("main_menu") == 0) {
			cout << "\nThe program is now returning to the main menu.\n" << endl;
			return;
		}
// If the user puts something too long it will automatically make the input invalid
		if (in.length() > 1) { in = "2"; }

// This assigns the user's input to the first character that was input since a string should
// 	not be compared to an integer
		charIn = in[0];

// This changes the character into its corresponding integer value
		intIn = static_cast<int>(charIn - '0');

// This switch statement checks which operation the user wants to perform
		switch (intIn) {
// If the user chose '0' then the program asks for the code in text form and gets that in the codeIn variable
// 	The control variable is set to false so the loop will exit
			case 0:
// This tells the user to input the students code and how to input that code
// Additionally, it tells the user what the string is that will cause the input loop to exit
			cout << "\nPlease paste the student's code to be added now\n";
			cout << "Please paste the entire code or enter it one line at a time\n";
			cout << "Please enter \"x9x\" on a new line after the end of the code to signify that you are done\n";
			cout << "Enter \"main_menu\" before anything else to return to the main menu" << endl;

// This clears any previous input from the cin stream so that getline can be used effectively
			cin.ignore(256, '\n');

// This is the code that actually gets the user's input
			getline(cin, codeIn);

// This will return the user to the main menu if they request to go back
			if (codeIn.compare("main_menu") == 0) {
// This tells the user that the program is going back to the main menu
				cout << "\nThe program is now returning to the main menu.\n" << endl;
// This returns to the main menu
				return;
			}

// This adds the user's input to the holding variable and assumes that the user isn't wanting to add an empty file
			studCode += codeIn;

// This while loop will get each line the user inputs and will exit once the controll string is input
			while(isCin){

// This gets the next line that the user inputs
				getline(cin, codeIn);

// If the user inputs the control then the control variable is set to false so the loop exits
				if(codeIn.compare("x9x") == 0){
// This sets the control to false so the loop will exit
					isCin = false;
				}
// If the input is not the control then it adds the input to the holding variable along with a new line
				else{
					studCode += '\n';
					studCode += codeIn;
				}
			}
// Once the loop exits, the codeIn variable is set to the contents of the holding variable
// This is so that only on call for addToDatabase is needed since codeIn is passed to that function
			codeIn = studCode;

// The following was for testing purposes and is not necessary for the program to function
//			cout << "\n\nThe input was: \n" << codeIn << "\nExtra slash n and end code\n\n";
// This sets the control for the overall menu loop to false
			contr = false;
			break;

// If the user enters '1' then it will ask for the filename of the code and will get that in the codeIn variable
// 	Also the control is set to false so the loop will exit
// Please, please, please make sure that the files are encoded in either ANSI or ASCII
// If the file is encoded in Unicode, it will look very wierd in the new file
// Thankfully the default for notepad and most things is ANSI so this should theoretically not be much of an issue
			case 1:
// This asks the user to enter the filename for the file to be copied
			cout << "\nPlease enter the name of the file to be copied into the database now\n";
			cout << "Enter \"main_menu\" to return to the main menu" << endl;
// This allows the use of getline since it will other wise try to take in a return character
			cin.ignore(256, '\n');
// This gets the user's inputs
			getline(cin, codeIn);
// This will return the user to the main menu if they request to go back
			if (codeIn.compare("main_menu") == 0) {
// This tells the user that the program is going back to the main menu
				cout << "\nThe program is now returning to the main menu.\n" << endl;
// This returns to the main menu
				return;
			}
// This is a simple check to make sure the file exists
			fileCheck.open(codeIn.c_str());
// If fileCheck is true then the file exists and the program can continue
			if(fileCheck){
// This sets the overall menu loop control to false
				contr = false;
// This properly closes the file since it will not be read from until later
				fileCheck.close();
// This breaks the switch case
				break;
			}
// If the file could not be opened then the program outputs an error and allows the user to try again
			else{
// The file still needs to be closed even if it technically does not exist
				fileCheck.close();
// This outputs the error message to the screen
				cout << "\nThe file that you entered does not exist; please try again." << endl;
// This breaks the switch case
				break;
			}
// This breaks the switch case just in case the break statements above actually break the if else statement
			break;

// If the user entered something else then the program asks the user to try again
			default:
// Outputting the error message to the screen for the user to see
			cout << "\nYou entered something the program does not recognize; please try again." << endl;
		}
// This is the while part of the do while loop and will exit when contr is false
	} while(contr);

// This bool will help with filename verification making sure that the file does not already exist
	bool flag = true;

// This will hold the full path of the filename so that validity can be checked
	string fullPath = "";

// This loop will continue as long as the user keeps entering files that already exist
// The loop will exit when an appropriate filename is given
	do{

// After getting either the code or the file name, the program asks the user to enter the name for the new file
// 	The name for the file is asked to be in a specific format so that it will be easy to know some of the file's
// 	attributes and contents, the number of retries for the course is to prevent accidental overwritting of previous
// 	 coursework in the case that the student retakes the course
		cout << "\nPlease enter the name for the new file.\n";
		cout << "Enter the filename in the following format:\n";
		cout << "StudentID_AssignmentNumber_NumberOfTimesRetryingTheCourse\n";
		cout << "Example: \"123456_19_0\"\n";
		cout << "Alternatively, enter \"main_menu\" to return to the main menu" << endl;

// This retieves the file name
		getline(cin, fileName);

// This will return to the main menu if the user asks to
		if(fileName.compare("main_menu") == 0){
// The program tells the user that the program is going back to the main menu
			cout << "\nThe program is now returning to the main menu.\n" << endl;
// This returns to the main menu
			return;
		}

// This makes sure that the potential new file has the correct path to be checked for validity
		fullPath = databaseItems[0];
		fullPath += '\\';
		fullPath += fileName;
		fullPath += ".java";

// This checks to see if the file can be opened
		ifstream f;

		f.open(fullPath.c_str());
// If it can then the program asks the user to choose another name for the file
		if (f.good()) {
			cout << "\nThis file already exists in the database. Please choose another name.\n" << endl;
// This makes sure that the flag stays true so that the loop does not end
			flag = true;
		}
// If the file was not found then it has an appropriate name for a new file
		else{
// The flag will be set to false so that the loop will exit
			flag = false;
		}
		// Always properly close files whether or not they exist
			f.close();
	} while(flag);

	// If the database addition returns true then the file was successfully added and a confirmation message is given
		if(addToDatabase(intIn, codeIn, fileName)){
	// Confirmation message so the user knows the file was added successfully
			cout << "\nThe file was successfully added to the database\n" << endl;
	// This exits this function and returns to the main UI
			return;
		}
	// If the addition returns false then a message asking the user to retry is given and the addition UI is recursively called
		else{
	// This outputs the error messsage to the screen
			cout << "\nThe file was not added, please try again\n" << endl;
	// This makes the funstion call itself so that the user can try the addition again
			addToDatabaseUI();
	// This returns from the addToDatabaseUI function to the main UI
			return;
		}
// The program should not get to this line but it is not good to have a function without a general return statement
	return;
}

// This is the function that will actually perform the addition to the database
// 	The function will return true if the file was successfully added and false if not
// 	It accepts an int and two string values as parameters, the int tells which type of addition
// 	to perform, the first string contains the filename of the new file, and the final string
// 	contains either the content to put into the new file or the name of the file to copy
bool addToDatabase(const int type, string fileInfo, string newFileName){

// Please, please, please make sure that the files are encoded in either ANSI or ASCII
// Thankfully the default for notepad is ANSI so this should theoretically not be much of an issue

// These variables will hold the file contents for the old and new files and the name of the new file
	string contents = "";
	string newContents = "";
	string newName = "";

// If the type is 1 then the addition is for an existing file
	if(type == 1){
// This opens the input filestream
		ifstream fileIn, fileExists;
// This actually opens the file
		fileIn.open(fileInfo.c_str());

// This double checks to make sure the file can be opened and should never be false since it is checked in the UI portion
		if(fileIn){
// This gets the first contents of the file if it exists
			contents = fileIn.get();
		}
// If the file does not exist then it displays an error and returns to addToDatabaseUI for the user to try again
		else{
// This outputs the error message
			cout << "\nThe filename given did not match any files; please try again.\n" << endl;
// This properly closes the file even if it does not exist
			fileIn.close();
// This makes the program return false since no addition was performed
			return false;
		}

// This opens the output filestream so the new file can be written
		ofstream newOut;
// This adds the path of the first folder to the new filename
		newName = databaseItems[0];
// This adds the backslash to the filename since it will otherwise be omitted
		newName += '\\';
// This adds the new filename to the full path so that it can be created correctly
		newName += newFileName;
// This adds the correct file extension to the new file, the default being a java source code file
		newName += ".java";
		
		// Check if the file already exists so we don't overwrite it!
		fileExists.open(newName);
		
		if (fileExists) {
			fileExists.close();
			cout << "\nThis file already exists in the database. Please try again"
			<< " and enter a different name for the new file.\n" << endl;
			return false;
		}

// This outputs the path of the new file so that the user will know where it is located
		cout << "\nThe path for the new file is: \"" << newName << "\"\n" << endl;

// This line actually creates the new file for the database
		newOut.open(newName.c_str());
// This loop will continue until there is nothing left in the input file
		while(fileIn){
// This adds the contents of the input file to the newContents variable
// The newContents variable is used to dump the entire text into the output file at once
			newContents += contents;
// This gets the next intem in the input file or set fileIn to false if the file is empty
			contents = fileIn.get();
		}

// This puts the contents of the input file into the output file
		newOut << newContents;
// This properly closes the input file
		fileIn.close();
// This properly closes the output file
		newOut.close();
// Since the database now has a new entry, the new item is added to the internal list of database items
		databaseItems.push_back(newName);
// The addition is now complete and the program can return true
		return true;
	}
// If the type is not 1 and is 0 then a text addition will be performed
	else if(type == 0){
		ifstream fileExists;
// This prepares the output file stream
		ofstream newOut;
// This adds the path of the first folder to the new filename
		newName = databaseItems[0];
// This adds the backslash to the filename since it will otherwise be omitted
		newName += '\\';
// This adds the new filename to the full path so that it can be created correctly
		newName += newFileName;
// This adds the correct file extension to the new file, the default being a java source code file
		newName += ".java";
		
		// Check if the file already exists so we don't overwrite it!
		fileExists.open(newName);
		
		if (fileExists) {
			fileExists.close();
			cout << "\nThis file already exists in the database. Please try again"
			<< " and enter a different name for the new file.\n" << endl;
			return false;
		}
		
// This displays the new filepath so that the user can see it
		cout << "\nThe path for the new file is: \"" << newName << "\"\n" << endl;
// This actually opens the new output file
		newOut.open(newName.c_str());
// This dumps the text that the user input in the addToDatabaseUI into the new file
		newOut << fileInfo;
// This properly closes the new file
		newOut.close();
// This adds the new file to the internal list of database items
		databaseItems.push_back(newName);
// The program has successfully added the text to a new file and added that file to the database and can return true
		return true;
	}
// The program should never reach this return but it is here because it is bad practice to omit a general return statement
// If the program makes it to this line then something has gone wrong internally
// Therefore, the program will return false so that the user can try again
	return false;
}

void fileToFile() {
	vector<string> code1, code2, properties1, properties2;

	// Stores the first code in the vector code1 and properties in the vector properties1.
	cout << "\nWould you like to enter a text selection or a .txt or .java file as the first code to add?\n";
	cout << "Enter \'0\' for a text selection or \'1\' for a file: ";

	readInFileOrText(code1, properties1);

	// Stores the second code in the vector code2 and properties in the vector properties2.
	cout << "\nWould you like to enter a text selection or a .txt or .java file as the second code to add?\n";
	cout << "Enter \'0\' for a text selection or \'1\' for a file: ";

	readInFileOrText(code2, properties2);

	double matchCount = 0;

	if (code1.size() >= code2.size()) {
		cout << "\n\nCode Excerpt 1:\n" << endl;

		for (unsigned int i = 1; i <= properties1.size(); i++) { cout << properties1[i-1] << endl; }
		cout << endl;

		for (unsigned int i = 1; i <= code1.size(); i++) {
			cout << "(" << i << ") " << code1[i-1] << endl;
		}

		cout << "\n\nCode Excerpt 2:\n" << endl;

		for (unsigned int i = 1; i <= properties2.size(); i++) { cout << properties2[i-1] << endl; }
		cout << endl;

		for (unsigned int i = 1; i <= code2.size(); i++) {
			string c = " ";
			for (unsigned int j = 1; j <= code1.size(); j++) {
				if (code2[i-1].compare(code1[j-1]) == 0 && !code2[i-1].empty()) {
					stringstream ss;
					ss << j;
					c = ss.str();
					matchCount++;
					break;
				}
			}
			cout << "(" << c << ") " << code2[i-1] << endl;
		}

		cout << "\n\nPercentage match: " << (100*matchCount/code2.size()) << "%\n" << endl;
	} else {
		cout << "\n\nCode Excerpt 1:\n" << endl;

		for (unsigned int i = 1; i <= properties2.size(); i++) { cout << properties2[i-1] << endl; }
		cout << endl;

		for (unsigned int i = 1; i <= code2.size(); i++) {
			cout << "(" << i << ") " << code2[i-1] << endl;
		}

		cout << "\n\nCode Excerpt 2:\n" << endl;

		for (unsigned int i = 1; i <= properties1.size(); i++) { cout << properties1[i-1] << endl; }
		cout << endl;

		for (unsigned int i = 1; i <= code1.size(); i++) {
			string c = " ";
			for (unsigned int j = 1; j <= code2.size(); j++) {
				if (code1[i-1].compare(code2[j-1]) == 0 && !code1[i-1].empty()) {
					stringstream ss;
					ss << j;
					c = ss.str();
					matchCount++;
					break;
				}
			}
			cout << "(" << c << ") " << code1[i-1] << endl;
		}

		cout << "\n\nPercentage match: " << (100*matchCount/code1.size()) << "%\n\n" << endl;
	}
	
	// Add both code files / excerpts to the database.
	bool flag = false;
	string fileName, entireCode;

	for (unsigned int i = 0; i < code1.size(); i++) {
		entireCode += code1[i] + '\n';
	}

	while (!flag) {
		cout << "The first code you entered will now be added to the database.\n";
		cout << "Please enter the name for the new file.\n";
		cout << "Enter the filename in the following format:\n";
		cout << "StudentID_AssignmentNumber_NumberOfTimesRetryingTheCourse\n";
		cout << "Example: \"123456_19_0\"\n" << endl;

		getline(cin, fileName);

		flag = addToDatabase(0, entireCode, fileName);
	}

	cout << "\nThe file was successfully added to the database.\n\n" << endl;
	
	flag = false;
	entireCode = "";

	for (unsigned int i = 0; i < code2.size(); i++) {
		entireCode += code2[i] + '\n';
	}

	while (!flag) {
		cout << "The second code you entered will now be added to the database.\n";
		cout << "Please enter the name for the new file.\n";
		cout << "Enter the filename in the following format:\n";
		cout << "StudentID_AssignmentNumber_NumberOfTimesRetryingTheCourse\n";
		cout << "Example: \"123456_19_0\"\n" << endl;

		getline(cin, fileName);

		flag = addToDatabase(0, entireCode, fileName);
	}

	cout << "\nThe file was successfully added to the database.\n\n" << endl;
}

void compareToDatabase() {
	vector<string> code1, code2, properties1;
	string codeIn;

	// Stores the first code in the vector code1 and properties in the vector properties1.
	cout << "\nWould you like to enter a text selection or a .txt or .java file as the code to compare?\n";
	cout << "Enter \'0\' for a text selection or \'1\' for a file: ";

	readInFileOrText(code1, properties1);

	double highestMatchPercent = 0.0;
	string highestMatchName;

	for (unsigned int f = 0; f < databaseItems.size(); f++) {
		if (databaseItems[f].substr(databaseItems[f].length() - 5, 5).compare(".java") != 0
			&& databaseItems[f].substr(databaseItems[f].length() - 4, 4).compare(".txt") != 0) { continue; }

		ifstream fileCheck;
		fileCheck.open(databaseItems[f]);

		if(!fileCheck) {
			fileCheck.close();
			continue;
		}

		getline(fileCheck, codeIn);

		while(fileCheck) {
			if (!codeIn.empty()) { code2.push_back(codeIn); }
			getline(fileCheck, codeIn);
		}

		fileCheck.close();

		double matchCount = 0.0, matchPercent = 0.0;

		for (unsigned int i = 1; i <= code1.size(); i++) {
			for (unsigned int j = 1; j <= code2.size(); j++) {
				if (code1[i-1].compare(code2[j-1]) == 0 && !code1[i-1].empty()) {
					matchCount++;
					break;
				}
			}
		}

		matchPercent = 100*matchCount/code1.size();

		if (matchPercent > highestMatchPercent) {
			highestMatchPercent = matchPercent;
			highestMatchName = databaseItems[f];
		}
	}

	if (highestMatchPercent > 0.0) {
		cout << "\nThe highest matched file's name:\n\n" << highestMatchName << "\n\nPercentage match: " << highestMatchPercent << "%\n\n" << endl;
	} else {
		cout << "\nThis file did not match any of the files in the database to any degree.\n\n" << endl;
	}

	if (highestMatchPercent < 100.0) {
		bool flag = false;
		string fileName, entireCode;

		for (unsigned int i = 0; i < code1.size(); i++) {
			entireCode += code1[i] + '\n';
		}

		while (!flag) {
			cout << "The code you entered will now be added to the database.\n";
			cout << "Please enter the name for the new file.\n";
			cout << "Enter the filename in the following format:\n";
			cout << "StudentID_AssignmentNumber_NumberOfTimesRetryingTheCourse\n";
			cout << "Example: \"123456_19_0\"\n" << endl;

			getline(cin, fileName);

			flag = addToDatabase(0, entireCode, fileName);
		}

		cout << "\nThe file was successfully added to the database.\n" << endl;
	}
}

void readInFileOrText(vector<string> &code, vector<string> &properties) {
	bool contr = true;

	do {
		string in, fileName, codeIn;
		ifstream fileCheck;
		bool isCin = true;

		cin >> in;

		// Make sure not to accept the input unless it is one character.
		if (in.compare("0") == 0) {
			cout << "\nPlease paste the first code to be added now\n";
			cout << "Please paste the entire code or enter it one line at a time\n";
			cout << "Please enter \"x9x\" on a new line after the end of the code to signify that you are done" << endl;

			cin.ignore(256, '\n');

			getline(cin, codeIn);

			while(isCin){
				if (!codeIn.empty()) { code.push_back(codeIn); }
				getline(cin, codeIn);
				if(codeIn.compare("x9x") == 0){ isCin = false; }
			}

			contr = false;
		} else if (in.compare("1") == 0) {
			cout << "\nPlease enter the name of the file to compare:" << endl;
			cin.ignore(256, '\n');
			getline(cin, codeIn);
			fileCheck.open(codeIn.c_str());
			
			while (!fileCheck) {
				fileCheck.close();
				cout << "\nThe file that you entered does not exist; please try again." << endl;
				
				cin.ignore(256, '\n');
				getline(cin, codeIn);
				fileCheck.open(codeIn.c_str());
			}

			properties.push_back("File Name: " + codeIn);

			// Below is my attempt at getting the created and last modified times.
			// The FileTimeToSystemTime function crashed the program and I have yet to figure out why.

			/*
			WIN32_FILE_ATTRIBUTE_DATA fileAttrs;
			bool result = GetFileAttributesEx(codeIn.c_str(), GetFileExInfoStandard, &fileAttrs);

			if (result) {
				LPSYSTEMTIME st = NULL, st2 = NULL;

				// Get creation time and add it to properties
				FileTimeToSystemTime(&fileAttrs.ftCreationTime, st);
				SystemTimeToTzSpecificLocalTime(NULL, st, st2);

				if (st2) {
					string temp = string("Date Created: ") + to_string(st2->wMonth) + "/" + to_string(st2->wDay) + "/" + to_string(st2->wYear) + " " + to_string(st2->wHour) + ":" + to_string(st2->wMinute);
					properties.push_back(temp);
				}

				// Get modification time and add it to properties
				FileTimeToSystemTime(&fileAttrs.ftLastWriteTime, st);
				SystemTimeToTzSpecificLocalTime(NULL, st, st2);
				if (st2) {
					string temp = string("Date Created: ") + to_string(st2->wMonth) + "/" + to_string(st2->wDay) + "/" + to_string(st2->wYear) + " " + to_string(st2->wHour) + ":" + to_string(st2->wMinute);
					properties.push_back(temp);
				}
			}
			*/

			getline(fileCheck, codeIn);

			while(fileCheck) {
				if (!codeIn.empty()) { code.push_back(codeIn); }
				getline(fileCheck, codeIn);
			}

			fileCheck.close();
			contr = false;
		} else { cout << "\nYou entered something the program does not recognize; please try again." << endl; }
	} while(contr);
}
